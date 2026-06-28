#include "machinewidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#include <cmath>

static QPointF polar(double cx, double cy, double len, double angleDeg)
{
    double rad = angleDeg * M_PI / 180.0;
    return QPointF(cx + len * std::cos(rad), cy - len * std::sin(rad));
}

MachineWidget::MachineWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(400, 300);
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MachineWidget::onAnimate);
}

void MachineWidget::setMachineState(int state)
{
    m_state = state;
    if (state == 2) {
        m_timer->start(30);
    } else {
        m_timer->stop();
        m_boomAngle = 40.0;
        m_dustAlpha = 0;
        update();
    }
}

void MachineWidget::onAnimate()
{
    m_boomAngle += m_boomDir * 0.7;
    if (m_boomAngle >= 62.0) m_boomDir = -1.0;
    if (m_boomAngle <= 22.0) m_boomDir =  1.0;
    m_dustAlpha = (m_boomDir < 0) ? qMin(m_dustAlpha + 20, 200) : qMax(m_dustAlpha - 10, 0);
    update();
}

void MachineWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    int w = width(), h = height();
    int groundY = h * 68 / 100;
    int cx = w / 2 - 10;

    // Sky gradient
    QLinearGradient sky(0, 0, 0, groundY);
    sky.setColorAt(0.0, QColor(100, 170, 220));
    sky.setColorAt(1.0, QColor(200, 230, 250));
    p.fillRect(0, 0, w, groundY, sky);

    // Ground
    p.fillRect(0, groundY,     w, h - groundY, QColor(90, 58, 28));
    // Grass strip
    p.fillRect(0, groundY,     w, 10,           QColor(50, 120, 50));
    p.fillRect(0, groundY + 10, w, 4,           QColor(70, 140, 60));

    // Draw clouds (static decoration)
    auto drawCloud = [&](int x, int y) {
        p.setBrush(QColor(255, 255, 255, 200));
        p.setPen(Qt::NoPen);
        p.drawEllipse(x,      y,      50, 28);
        p.drawEllipse(x + 22, y - 10, 40, 30);
        p.drawEllipse(x + 46, y,      36, 24);
    };
    drawCloud(40,  30);
    drawCloud(200, 50);
    drawCloud(w - 200, 35);

    drawExcavator(p, cx, groundY);

    // State overlay text
    if (m_state == 2) {
        QFont f;
        f.setPointSize(16);
        f.setBold(true);
        p.setFont(f);
        p.setPen(QColor(220, 60, 60));
        p.drawText(QRect(0, 8, w, 40), Qt::AlignHCenter | Qt::AlignVCenter,
                   QString::fromUtf8("⚙ 施工中..."));
    } else if (m_state == 1) {
        QFont f;
        f.setPointSize(13);
        p.setFont(f);
        p.setPen(QColor(180, 100, 0));
        p.drawText(QRect(0, 8, w, 40), Qt::AlignHCenter | Qt::AlignVCenter,
                   QString::fromUtf8("待機中 — 等待第二指..."));
    } else {
        QFont f;
        f.setPointSize(13);
        p.setFont(f);
        p.setPen(QColor(80, 80, 80));
        p.drawText(QRect(0, 8, w, 40), Qt::AlignHCenter | Qt::AlignVCenter,
                   QString::fromUtf8("機具待命"));
    }
}

void MachineWidget::drawExcavator(QPainter &p, int cx, int groundY)
{
    // ── Tracks ──────────────────────────────────────────────────────
    int tW = 180, tH = 22, tY = groundY - tH + 6;
    int tX = cx - tW / 2;
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(35, 35, 35));
    p.drawRoundedRect(tX, tY, tW, tH, 7, 7);
    // Track links
    p.setPen(QPen(QColor(70, 70, 70), 2));
    for (int i = 1; i < 7; i++)
        p.drawLine(tX + i * 25, tY + 2, tX + i * 25, tY + tH - 2);
    // Drive wheels
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(55, 55, 55));
    p.drawEllipse(tX + 2,       tY - 9, 30, 30);
    p.drawEllipse(tX + tW - 32, tY - 9, 30, 30);
    p.setBrush(QColor(90, 90, 90));
    p.drawEllipse(tX + 9,       tY - 2, 16, 16);
    p.drawEllipse(tX + tW - 25, tY - 2, 16, 16);

    // ── Main body ────────────────────────────────────────────────────
    int bW = 148, bH = 38;
    int bX = cx - bW / 2, bY = tY - bH + 8;
    p.setBrush(QColor(210, 110, 0));
    p.setPen(QPen(QColor(150, 75, 0), 2));
    p.drawRect(bX, bY, bW, bH);
    // Body stripe
    p.setBrush(QColor(240, 200, 0));
    p.setPen(Qt::NoPen);
    p.drawRect(bX + 12, bY + bH / 2 - 4, bW - 24, 8);
    // Counterweight (rear bump)
    p.setBrush(QColor(170, 85, 0));
    p.setPen(QPen(QColor(130, 60, 0), 1));
    p.drawRoundedRect(bX - 14, bY + 6, 18, bH - 12, 4, 4);

    // ── Cabin ────────────────────────────────────────────────────────
    int cabW = 72, cabH = 52;
    int cabX = bX + 8, cabY = bY - cabH;
    p.setBrush(QColor(230, 130, 0));
    p.setPen(QPen(QColor(150, 75, 0), 2));
    p.drawRect(cabX, cabY, cabW, cabH);
    // Cabin roof (slanted toward arm side)
    QPolygonF roof;
    roof << QPointF(cabX + 4,        cabY)
         << QPointF(cabX + cabW - 2, cabY)
         << QPointF(cabX + cabW + 6, cabY - 14)
         << QPointF(cabX + 10,       cabY - 14);
    p.setBrush(QColor(250, 155, 10));
    p.setPen(QPen(QColor(150, 75, 0), 2));
    p.drawPolygon(roof);
    // Window
    p.setBrush(QColor(160, 210, 240, 210));
    p.setPen(QPen(QColor(100, 160, 200), 1));
    p.drawRect(cabX + 8, cabY + 10, cabW - 16, cabH - 24);
    // Window frame divider
    p.setPen(QPen(QColor(100, 160, 200), 1));
    p.drawLine(cabX + cabW / 2, cabY + 10, cabX + cabW / 2, cabY + cabH - 14);

    // ── Arm ──────────────────────────────────────────────────────────
    int pivX = bX + bW - 12, pivY = bY + 10;
    drawArm(p, pivX, pivY);
}

void MachineWidget::drawArm(QPainter &p, int pivX, int pivY)
{
    double boom  = m_boomAngle;
    double stick = boom - 68.0;

    QPointF boomEnd  = polar(pivX, pivY,          88.0, boom);
    QPointF stickEnd = polar(boomEnd.x(), boomEnd.y(), 62.0, stick);

    // Hydraulic cylinder (boom) — thin line between two points
    QPointF cylA = polar(pivX + 8, pivY + 5, 28.0, boom + 28.0);
    QPointF cylB = polar(boomEnd.x() - 4, boomEnd.y() + 2, 14.0, boom - 160.0);
    p.setPen(QPen(QColor(130, 65, 0), 3, Qt::SolidLine, Qt::RoundCap));
    p.drawLine(cylA, cylB);

    // Boom
    p.setPen(QPen(QColor(185, 92, 0), 11, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    p.drawLine(QPointF(pivX, pivY), boomEnd);
    p.setPen(QPen(QColor(220, 130, 20), 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    p.drawLine(QPointF(pivX, pivY), boomEnd);

    // Stick hydraulic cylinder
    QPointF cylC = polar(boomEnd.x(), boomEnd.y(), 18.0, stick + 38.0);
    QPointF cylD = polar(stickEnd.x(), stickEnd.y(), 12.0, stick - 140.0);
    p.setPen(QPen(QColor(130, 65, 0), 3, Qt::SolidLine, Qt::RoundCap));
    p.drawLine(cylC, cylD);

    // Stick
    p.setPen(QPen(QColor(185, 92, 0), 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    p.drawLine(boomEnd, stickEnd);
    p.setPen(QPen(QColor(220, 130, 20), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    p.drawLine(boomEnd, stickEnd);

    // Bucket
    double bucketAngle = stick - 55.0;
    double rad = stick * M_PI / 180.0;
    QPointF perp(-std::sin(rad) * 13.0, -std::cos(rad) * 13.0);
    QPointF bucketTip = polar(stickEnd.x(), stickEnd.y(), 24.0, bucketAngle);

    QPainterPath bucket;
    bucket.moveTo(stickEnd + perp * 0.7);
    bucket.lineTo(stickEnd - perp * 0.7);
    bucket.lineTo(bucketTip - perp * 0.3);
    bucket.lineTo(bucketTip + perp * 0.9);
    bucket.closeSubpath();
    p.setBrush(QColor(110, 55, 0));
    p.setPen(QPen(QColor(70, 35, 0), 2));
    p.drawPath(bucket);

    // Joints
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(80, 40, 0));
    p.drawEllipse(QPointF(pivX, pivY),    7, 7);
    p.drawEllipse(boomEnd,                6, 6);
    p.drawEllipse(stickEnd,               5, 5);

    // Dust/dirt effect at bucket when digging (state 2, arm going down)
    if (m_dustAlpha > 0) {
        drawDust(p, bucketTip);
    }
}

void MachineWidget::drawDust(QPainter &p, QPointF tip)
{
    p.setPen(Qt::NoPen);
    const int offsets[5][2] = {{0,0},{-12,4},{10,2},{-6,10},{8,8}};
    const int sizes[5]      = {18, 14, 12, 10, 9};
    for (int i = 0; i < 5; i++) {
        int alpha = m_dustAlpha - i * 28;
        if (alpha <= 0) continue;
        p.setBrush(QColor(101, 67, 33, alpha));
        p.drawEllipse(QPointF(tip.x() + offsets[i][0], tip.y() + offsets[i][1]),
                      sizes[i], sizes[i] / 2);
    }
}
