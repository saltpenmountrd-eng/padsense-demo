#include "widget.h"
#include "ui_widget.h"
#include <QScreen>
#include <QGuiApplication>
#include <QStandardItemModel>

#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE (Qt::HANDLE(-1))
#endif

extern Widget *g_Widget;
Qt::HANDLE g_hDevice;

// ===================
// Library API typedef
// ===================
// Find Hid USB PenMount Device API
typedef qint32 (* pFnFindHidDevice)(Qt::HANDLE *phDevice, wchar_t szProduct[20], qint32 *piUSBPortIndex);
// Close Device
typedef qint32 (* pFnCloseDevice)(Qt::HANDLE hDevice);
// Callback function for Pad Sense Notify
typedef qint32 (*PADSENSE_PROC) (quint8 byHead, quint16 wXPosition, quint16 wYPosition, quint8 byStatus, Qt::HANDLE hDevice);
// Register Pad Sense Notify API
typedef qint32 (* pFnRegisterPadSenseNotify)(PADSENSE_PROC CallBack, qint32 iSlope, qint32 iHeavyTime);
// Unregister Touch Notify
typedef qint32 (* pFnUnRegisterTouchNotify)();
// Start Touch Thread for Linux
typedef qint32 (* pFnStartTouchThread)(Qt::HANDLE hDevice);
// Stop Touch Thread for Linux
typedef qint32 (* pFnStopTouchThread)(Qt::HANDLE hDevice);

qint32 PadSenseCallBack(quint8 byHead, quint16, quint16, quint8 byStatus, Qt::HANDLE hDevice)
{
    // Valid handle or not
    quint8 byValid = (hDevice == INVALID_HANDLE_VALUE) ? 0 : 1;
    emit g_Widget->PadSenseSignal(byHead, byStatus, byValid);
    return 1;
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_bModify(false),
    m_iSlope(50),
    m_iHeavyTime(500)
{
    ui->setupUi(this);

    // Initial Timer if load library failed
    m_ExitTimer  = new QTimer(this);
    connect(m_ExitTimer , SIGNAL(timeout()), this, SLOT(ExitTimer()));

    connect(this, SIGNAL(PadSenseSignal(quint8, quint8, quint8)), this, SLOT(PadSenseSlot(quint8, quint8, quint8)));

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ModifyParameters()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(ReFindPMDevice()));

    // Initial Table View
    QStandardItemModel *model1 = new QStandardItemModel(10, 1, this);
    QStringList szLabel;
    szLabel << "State";
    model1->setHorizontalHeaderLabels(szLabel);
    szLabel.clear();
    szLabel << "Finger 1" << "Finger 2" << "Finger 3" << "Finger 4" << "Finger 5" << "Finger 6" << "Finger 7" << "Finger 8" << "Finger 9" << "Finger 10";
    model1->setVerticalHeaderLabels(szLabel);

    ui->tableView->setModel(model1);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->verticalHeader  ()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setSectionsClickable(false);
    ui->tableView->verticalHeader  ()->setSectionsClickable(false);
    ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Load PM_Standard.dll
    m_PMDLL.setFileName(QCoreApplication::applicationDirPath() + "/PM_Standard.dll");
    if (m_PMDLL.load()) {
        // Call Find Hid USB PenMount Device API
        pFnFindHidDevice pFnFHIDDev = (pFnFindHidDevice)m_PMDLL.resolve("FindHidDeviceW");
        if (pFnFHIDDev) {
            wchar_t szProduct[20];
            qint32 iUSBPortIndex;
            pFnFHIDDev(&g_hDevice, szProduct, &iUSBPortIndex);
            if (g_hDevice && g_hDevice != INVALID_HANDLE_VALUE) {
                // Call Register Pad Sense Notify API
                pFnRegisterPadSenseNotify pFnRegPadSenseNotify = (pFnRegisterPadSenseNotify)m_PMDLL.resolve("RegisterPadSenseNotify");
                if (pFnRegPadSenseNotify) {
                    pFnRegPadSenseNotify(PadSenseCallBack, m_iSlope, m_iHeavyTime);
                }

                pFnStartTouchThread pFnStartTT = (pFnStartTouchThread)m_PMDLL.resolve("StartTouchThread");
                if (pFnStartTT) {
                    pFnStartTT(g_hDevice);
                }
            }
        }
    } else {
        m_ExitTimer->start(1000);
    }
}

Widget::~Widget()
{
    if (g_hDevice && g_hDevice != INVALID_HANDLE_VALUE) {
        // Call Unregister Touch Notify API
        pFnUnRegisterTouchNotify pFnUnRegTouchNotify = (pFnUnRegisterTouchNotify)m_PMDLL.resolve("UnRegisterTouchNotify");
        if (pFnUnRegTouchNotify) {
            pFnUnRegTouchNotify();
        }
        pFnStopTouchThread pFnStopTT = (pFnStopTouchThread)m_PMDLL.resolve("StopTouchThread");
        if (pFnStopTT) {
            pFnStopTT(g_hDevice);
        }
        pFnCloseDevice pFnCDev = (pFnCloseDevice)m_PMDLL.resolve("CloseDevice");
        if (pFnCDev) {
            pFnCDev(g_hDevice);
        }
    }
    m_PMDLL.unload();
    delete ui;
}

void Widget::ShowWidget()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect rect = ui->label_4->geometry();
    ui->label_4->setGeometry(QRect(rect.left(), rect.top(), screen->geometry().width() / 2, rect.height()));
    show();
}

void Widget::ModifyParameters()
{
    m_bModify = !m_bModify;
    ui->lineEdit->setEnabled(m_bModify);
    ui->lineEdit_2->setEnabled(m_bModify);
    if (m_bModify) {
        ui->pushButton->setText("Accept");
    } else {
        ui->pushButton->setText("Modify");
        // Get Parameters from Edit and call register API
        m_iSlope = ui->lineEdit->text().toInt();
        m_iHeavyTime = ui->lineEdit_2->text().toInt();
        // Limit slope and heavy time minimum value
        if (m_iSlope < 10) {
            m_iSlope = 10;
            ui->lineEdit->setText("10");
        }

        if (m_iHeavyTime < 100) {
            m_iHeavyTime = 100;
            ui->lineEdit_2->setText("100");
        }

        // Update slope and heavy time
        pFnRegisterPadSenseNotify pFnRegPadSenseNotify = (pFnRegisterPadSenseNotify)m_PMDLL.resolve("RegisterPadSenseNotify");
        if (pFnRegPadSenseNotify) {
            pFnRegPadSenseNotify(PadSenseCallBack, m_iSlope, m_iHeavyTime);
        }
    }
}

void Widget::ReFindPMDevice()
{
    if (g_hDevice && g_hDevice != INVALID_HANDLE_VALUE) {
        // Call Unregister Touch Notify API
        pFnUnRegisterTouchNotify pFnUnRegTouchNotify = (pFnUnRegisterTouchNotify)m_PMDLL.resolve("UnRegisterTouchNotify");
        if (pFnUnRegTouchNotify) {
            pFnUnRegTouchNotify();
        }
        pFnStopTouchThread pFnStopTT = (pFnStopTouchThread)m_PMDLL.resolve("StopTouchThread");
        if (pFnStopTT) {
            pFnStopTT(g_hDevice);
        }
        pFnCloseDevice pFnCDev = (pFnCloseDevice)m_PMDLL.resolve("CloseDevice");
        if (pFnCDev) {
            pFnCDev(g_hDevice);
        }
    }

    pFnFindHidDevice pFnFHIDDev = (pFnFindHidDevice)m_PMDLL.resolve("FindHidDeviceW");
    if (pFnFHIDDev) {
        wchar_t szProduct[20];
        qint32 iUSBPortIndex;
        pFnFHIDDev(&g_hDevice, szProduct, &iUSBPortIndex);
        if (g_hDevice && g_hDevice != INVALID_HANDLE_VALUE) {
            // Call Register Pad Sense Notify API
            pFnRegisterPadSenseNotify pFnRegPadSenseNotify = (pFnRegisterPadSenseNotify)m_PMDLL.resolve("RegisterPadSenseNotify");
            if (pFnRegPadSenseNotify) {
                pFnRegPadSenseNotify(PadSenseCallBack, m_iSlope, m_iHeavyTime);
            }
            pFnStartTouchThread pFnStartTT = (pFnStartTouchThread)m_PMDLL.resolve("StartTouchThread");
            if (pFnStartTT) {
                pFnStartTT(g_hDevice);
            }
        }
    }
}

void Widget::PadSenseSlot(quint8 byHead, quint8 byStatus, quint8 byValid)
{
    if (byValid == 0) {
        // Invalid handle : Call Find Hid USB PenMount Device API
        pFnFindHidDevice pFnFHIDDev = (pFnFindHidDevice)m_PMDLL.resolve("FindHidDeviceW");
        if (pFnFHIDDev) {
            wchar_t szProduct[20];
            qint32 iUSBPortIndex;
            pFnFHIDDev(&g_hDevice, szProduct, &iUSBPortIndex);
        }
    } else {
        // Check Head type (Pen Down or Pen Up)
        quint8 byDownUp = (byHead & 0xF0);
        if (byDownUp == 0x10 || byDownUp == 0x20) {
            // Show status from byStatus and touch index
            const static QString szStatusList[5] = { QString("Up"), QString("Down"), QString("Press"), QString("Rise"), QString("Heavy") };
            QStandardItemModel *model = (QStandardItemModel *)ui->tableView->model();
            quint8 byIndex = (byHead & 0x0F);
            model->setItem(byIndex, 0, new QStandardItem(szStatusList[byStatus]));
        }
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    // ESC key up : exit program
    if (event->key() == Qt::Key_Escape) {
        close();
    }
}
