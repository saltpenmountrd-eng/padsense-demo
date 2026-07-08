#pragma once
#include <QWidget>
#include <QLabel>
#include <QLibrary>
#include <QTimer>
#include <QKeyEvent>
#include "machinewidget.h"

extern Widget *g_Widget;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void ExitTimer() { m_exitTimer->stop(); close(); }
    void PadSenseSlot(quint8 byHead, quint8 byStatus, quint8 byValid,
                      quint16 wXPosition, quint16 wYPosition);

signals:
    void PadSenseSignal(quint8, quint8, quint8, quint16, quint16);

protected:
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    void loadDLL();
    void registerPadSense();
    void updateMachineState();
    void applySlotStyle(QLabel *lbl, int slotState);
    // slotState: 0=waiting, 1=confirmed(heavy)

    QLibrary  m_dll;
    QTimer   *m_exitTimer;
    int       m_iSlope     = 50;
    int       m_iHeavyTime = 500;

    MachineWidget *m_machineWidget;
    QLabel *m_titleLabel;
    QLabel *m_finger1Label;
    QLabel *m_finger2Label;
    QLabel *m_instructionLabel;
    QLabel *m_escLabel;

    // Finger tracking
    int  m_finger1 = -1;   // index of first finger to go heavy
    int  m_finger2 = -1;   // index of second finger to go heavy
    bool m_fingerDown[10]  = {};
    bool m_fingerHeavy[10] = {};
};
