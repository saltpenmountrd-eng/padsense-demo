#pragma once
#include <QWidget>
#include <QTimer>

class MachineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MachineWidget(QWidget *parent = nullptr);

    // 0 = 待機, 1 = 第一指就緒, 2 = 運作中
    void setMachineState(int state);

protected:
    void paintEvent(QPaintEvent *) override;

private slots:
    void onAnimate();

private:
    void drawExcavator(QPainter &p, int cx, int groundY);
    void drawArm(QPainter &p, int pivX, int pivY);
    void drawDust(QPainter &p, QPointF bucketTip);

    int    m_state     = 0;
    double m_boomAngle = 40.0;   // degrees from horizontal
    double m_boomDir   = 1.0;
    int    m_dustAlpha = 0;
    QTimer *m_timer;
};
