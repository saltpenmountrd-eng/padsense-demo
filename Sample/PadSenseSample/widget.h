#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QLibrary>
#include <QKeyEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void ShowWidget();

public Q_SLOTS:
    // Exit program if load PM_Standard libray failed.
    void ExitTimer() { m_ExitTimer->stop(); close(); }
    void ModifyParameters();
    void ReFindPMDevice();
    void PadSenseSlot(quint8, quint8, quint8, quint16, quint16);

Q_SIGNALS:
    void PadSenseSignal(quint8, quint8, quint8, quint16, quint16);

protected:
    void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::Widget *ui;
    QLibrary   m_PMDLL;
    QTimer    *m_ExitTimer;
    bool m_bModify;
    int m_iSlope;
    int m_iHeavyTime;
};

#endif // WIDGET_H
