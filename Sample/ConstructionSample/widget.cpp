#include "widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QCoreApplication>

#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE (Qt::HANDLE(-1))
#endif

extern Widget *g_Widget;
Qt::HANDLE g_hDevice = nullptr;

// ── DLL function types ────────────────────────────────────────────────────────
typedef qint32 (*pFnFindHidDevice)(Qt::HANDLE *phDevice, wchar_t szProduct[20], qint32 *piUSBPortIndex);
typedef qint32 (*pFnCloseDevice)(Qt::HANDLE hDevice);
typedef qint32 (*PADSENSE_PROC)(quint8 byHead, quint16 wX, quint16 wY, quint8 byStatus, Qt::HANDLE hDevice);
typedef qint32 (*pFnRegisterPadSenseNotify)(PADSENSE_PROC cb, qint32 iSlope, qint32 iHeavyTime);
typedef qint32 (*pFnUnRegisterTouchNotify)();
typedef qint32 (*pFnStartTouchThread)(Qt::HANDLE hDevice);
typedef qint32 (*pFnStopTouchThread)(Qt::HANDLE hDevice);

qint32 PadSenseCallBack(quint8 byHead, quint16 wX, quint16 wY, quint8 byStatus, Qt::HANDLE hDevice)
{
    quint8 byValid = (hDevice == INVALID_HANDLE_VALUE) ? 0 : 1;
    emit g_Widget->PadSenseSignal(byHead, byStatus, byValid, wX, wY);
    return 1;
}

// ── Widget constructor ────────────────────────────────────────────────────────
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(QString::fromUtf8("工程機具操控系統"));
    setStyleSheet("QWidget { background-color: #f0f0f0; }");

    // ── Title ──────────────────────────────────────────────────────────────
    m_titleLabel = new QLabel(QString::fromUtf8("⚙ 工程機具操控系統"), this);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet(
        "font-size: 22px; font-weight: bold; color: #cc6600;"
        "background: #fff3e0; border-bottom: 2px solid #e8a000;"
        "padding: 10px;");

    // ── Finger status panel (left column) ─────────────────────────────────
    m_finger1Label = new QLabel(this);
    m_finger2Label = new QLabel(this);
    m_finger1Label->setMinimumSize(170, 100);
    m_finger2Label->setMinimumSize(170, 100);
    m_finger1Label->setAlignment(Qt::AlignCenter);
    m_finger2Label->setAlignment(Qt::AlignCenter);
    m_finger1Label->setWordWrap(true);
    m_finger2Label->setWordWrap(true);

    m_simultaneousCheckBox = new QCheckBox(
        QString::fromUtf8("同步雙指模式（取消勾選：第一指→第二指）"), this);
    m_simultaneousCheckBox->setStyleSheet(
        "font-size: 13px; color: #555555; padding: 4px;");

    QLabel *slotTitle = new QLabel(QString::fromUtf8("手指狀態"), this);
    slotTitle->setAlignment(Qt::AlignCenter);
    slotTitle->setStyleSheet(
        "font-size: 14px; font-weight: bold; color: #555555;"
        "border-bottom: 1px solid #cccccc; padding-bottom: 4px;");

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->setContentsMargins(10, 8, 10, 8);
    leftLayout->setSpacing(12);
    leftLayout->addWidget(slotTitle);
    leftLayout->addWidget(m_finger1Label);
    leftLayout->addWidget(m_finger2Label);
    leftLayout->addWidget(m_simultaneousCheckBox);
    leftLayout->addStretch();

    QFrame *leftPanel = new QFrame(this);
    leftPanel->setFixedWidth(190);
    leftPanel->setStyleSheet(
        "QFrame { background: #ffffff; border: 1px solid #cccccc; border-radius: 6px; }");
    leftPanel->setLayout(leftLayout);

    // ── Machine widget (right) ─────────────────────────────────────────────
    m_machineWidget = new MachineWidget(this);
    m_machineWidget->setStyleSheet(
        "border: 1px solid #cccccc; border-radius: 6px; background: transparent;");

    QHBoxLayout *midLayout = new QHBoxLayout;
    midLayout->setSpacing(10);
    midLayout->addWidget(leftPanel);
    midLayout->addWidget(m_machineWidget, 1);

    // ── Instruction label (bottom) ─────────────────────────────────────────
    m_instructionLabel = new QLabel(this);
    m_instructionLabel->setAlignment(Qt::AlignCenter);
    m_instructionLabel->setMinimumHeight(54);
    m_instructionLabel->setWordWrap(true);
    m_instructionLabel->setStyleSheet(
        "font-size: 16px; padding: 8px; background: #ffffff;"
        "border: 1px solid #cccccc; border-radius: 6px;");

    m_escLabel = new QLabel(QString::fromUtf8("按下 ESC 鍵結束程式"), this);
    m_escLabel->setAlignment(Qt::AlignRight);
    m_escLabel->setStyleSheet("font-size: 11px; color: #999999; padding-right: 4px;");

    // ── Main layout ────────────────────────────────────────────────────────
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(12, 12, 12, 8);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(m_titleLabel);
    mainLayout->addLayout(midLayout, 1);
    mainLayout->addWidget(m_instructionLabel);
    mainLayout->addWidget(m_escLabel);

    // ── Timer for DLL load failure ─────────────────────────────────────────
    m_exitTimer = new QTimer(this);
    connect(m_exitTimer, &QTimer::timeout, this, &Widget::ExitTimer);

    // ── Signals / slots ────────────────────────────────────────────────────
    connect(this,
            SIGNAL(PadSenseSignal(quint8, quint8, quint8, quint16, quint16)),
            this,
            SLOT(PadSenseSlot(quint8, quint8, quint8, quint16, quint16)));
    connect(m_simultaneousCheckBox, &QCheckBox::toggled, this, [this]() {
        m_finger1 = -1;
        m_finger2 = -1;
        for (int i = 0; i < 10; ++i) {
            m_fingerDown[i] = false;
            m_fingerHeavy[i] = false;
        }
        updateMachineState();
    });

    // ── Initial UI state ───────────────────────────────────────────────────
    applySlotStyle(m_finger1Label, 0);
    applySlotStyle(m_finger2Label, 0);
    m_instructionLabel->setText(
        QString::fromUtf8("步驟 1／2：請用第一根手指重壓觸控板，達到「重壓確認」狀態"));

    loadDLL();
}

Widget::~Widget()
{
    if (g_hDevice && g_hDevice != INVALID_HANDLE_VALUE) {
        pFnUnRegisterTouchNotify fn1 =
            (pFnUnRegisterTouchNotify)m_dll.resolve("UnRegisterTouchNotify");
        if (fn1) fn1();
        pFnStopTouchThread fn2 =
            (pFnStopTouchThread)m_dll.resolve("StopTouchThread");
        if (fn2) fn2(g_hDevice);
        pFnCloseDevice fn3 =
            (pFnCloseDevice)m_dll.resolve("CloseDevice");
        if (fn3) fn3(g_hDevice);
    }
    m_dll.unload();
}

// ── DLL loading ───────────────────────────────────────────────────────────────
void Widget::loadDLL()
{
#ifdef Q_OS_WIN
    m_dll.setFileName(QCoreApplication::applicationDirPath() + "/PM_Standard.dll");
#else
    m_dll.setFileName(QCoreApplication::applicationDirPath() + "/libPM_Standard");
#endif
    if (!m_dll.load()) {
        m_exitTimer->start(1000);
        return;
    }

    pFnFindHidDevice fnFind =
        (pFnFindHidDevice)m_dll.resolve("FindHidDeviceW");
    if (fnFind) {
        wchar_t szProduct[20]; qint32 port;
        fnFind(&g_hDevice, szProduct, &port);
        if (g_hDevice && g_hDevice != INVALID_HANDLE_VALUE) {
            registerPadSense();
            pFnStartTouchThread fnStart =
                (pFnStartTouchThread)m_dll.resolve("StartTouchThread");
            if (fnStart) fnStart(g_hDevice);
        }
    }
}

void Widget::registerPadSense()
{
    pFnRegisterPadSenseNotify fnReg =
        (pFnRegisterPadSenseNotify)m_dll.resolve("RegisterPadSenseNotify");
    if (fnReg)
        fnReg(PadSenseCallBack, m_iSlope, m_iHeavyTime);
}

// ── PadSense slot ─────────────────────────────────────────────────────────────
void Widget::PadSenseSlot(quint8 byHead, quint8 byStatus, quint8 byValid,
                          quint16 /*wX*/, quint16 /*wY*/)
{
    if (byValid == 0) {
        // Device handle went invalid — re-find
        pFnFindHidDevice fnFind =
            (pFnFindHidDevice)m_dll.resolve("FindHidDeviceW");
        if (fnFind) {
            wchar_t szProduct[20]; qint32 port;
            fnFind(&g_hDevice, szProduct, &port);
        }
        return;
    }

    quint8 downUp = byHead & 0xF0;
    quint8 idx    = byHead & 0x0F;
    if (idx >= 10) return;

    if (downUp == 0x20) {
        // ── Touch up ──────────────────────────────────────────────────────
        m_fingerDown[idx]  = false;
        m_fingerHeavy[idx] = false;
        if (idx == m_finger1) {
            // First finger lifted → full reset; sequence must restart
            if (m_finger2 != -1) m_fingerHeavy[m_finger2] = false;
            m_finger1 = -1;
            m_finger2 = -1;
        } else if (idx == m_finger2) {
            m_finger2 = -1;
        }

    } else if (downUp == 0x10) {
        // ── Touch down / update ───────────────────────────────────────────
        m_fingerDown[idx] = true;

        if (byStatus == 4) {
            m_fingerHeavy[idx] = true;
            if (!m_simultaneousCheckBox->isChecked()) {
                // Assign to slots in order of heavy-press arrival.
                if (m_finger1 == -1) {
                    m_finger1 = idx;
                } else if (m_finger2 == -1 && idx != m_finger1) {
                    m_finger2 = idx;
                }
            }
        }
    }

    if (m_simultaneousCheckBox->isChecked()) {
        // In simultaneous mode, the two slots represent the first two fingers
        // that are currently down and heavy at the same time.
        m_finger1 = -1;
        m_finger2 = -1;
        for (int i = 0; i < 10; ++i) {
            if (!m_fingerDown[i] || !m_fingerHeavy[i]) continue;
            if (m_finger1 == -1) {
                m_finger1 = i;
            } else if (m_finger2 == -1) {
                m_finger2 = i;
                break;
            }
        }
    }

    updateMachineState();
}

// ── State → UI update ─────────────────────────────────────────────────────────
void Widget::updateMachineState()
{
    bool f1 = (m_finger1 != -1);
    bool f2 = (m_finger2 != -1);

    applySlotStyle(m_finger1Label, f1 ? 1 : 0);
    applySlotStyle(m_finger2Label, f2 ? 1 : 0);

    if (f1 && f2) {
        // Both fingers heavy → operating
        m_machineWidget->setMachineState(2);
        m_instructionLabel->setStyleSheet(
            "font-size: 17px; font-weight: bold; padding: 8px;"
            "background: #e8f5e9; border: 2px solid #43a047; border-radius: 6px;"
            "color: #1b5e20;");
        m_instructionLabel->setText(
            QString::fromUtf8("✅ 雙指重壓確認！工程機具啟動運作中！"));
    } else if (f1) {
        // First finger ready, waiting for second
        m_machineWidget->setMachineState(1);
        m_instructionLabel->setStyleSheet(
            "font-size: 16px; padding: 8px;"
            "background: #fff8e1; border: 2px solid #ffa000; border-radius: 6px;"
            "color: #e65100;");
        if (m_simultaneousCheckBox->isChecked()) {
            m_instructionLabel->setText(
                QString::fromUtf8("同步雙指模式：偵測到一指重壓，請保持並讓第二指同時重壓"));
        } else {
            m_instructionLabel->setText(
                QString::fromUtf8("第一指已確認 ✓　步驟 2／2：請用第二根手指重壓觸控板"));
        }
    } else {
        // Idle
        m_machineWidget->setMachineState(0);
        m_instructionLabel->setStyleSheet(
            "font-size: 16px; padding: 8px; background: #ffffff;"
            "border: 1px solid #cccccc; border-radius: 6px; color: #333333;");
        m_instructionLabel->setText(
            m_simultaneousCheckBox->isChecked()
                ? QString::fromUtf8("同步雙指模式：請用兩根手指同時重壓觸控板")
                : QString::fromUtf8("步驟 1／2：請用第一根手指重壓觸控板，達到「重壓確認」狀態"));
    }
}

void Widget::applySlotStyle(QLabel *lbl, int slotState)
{
    bool isSlot1 = (lbl == m_finger1Label);
    QString name = isSlot1 ? QString::fromUtf8("第一指") : QString::fromUtf8("第二指");
    QString num  = isSlot1 ? QString::fromUtf8("①") : QString::fromUtf8("②");

    if (slotState == 1) {
        lbl->setStyleSheet(
            "background: #43a047; color: white; border-radius: 8px;"
            "font-size: 15px; font-weight: bold; padding: 10px;");
        lbl->setText(num + QString::fromUtf8("\n") + name +
                     QString::fromUtf8("\n\n重壓確認 ✓"));
    } else {
        lbl->setStyleSheet(
            "background: #e0e0e0; color: #888888; border-radius: 8px;"
            "font-size: 14px; padding: 10px;");
        lbl->setText(num + QString::fromUtf8("\n") + name +
                     QString::fromUtf8("\n\n等待中..."));
    }
}

// ── Key handler ───────────────────────────────────────────────────────────────
void Widget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        close();
}
