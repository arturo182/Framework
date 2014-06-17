#include "pinitem.h"

#include "componentitem.h"
#include "wire.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPen>

QColor PinItem::colorForValue(const quint8 &value)
{
    const float percent = value / 255.0;
    const QColor green(QColor(130, 180, 10));
    const QColor white(Qt::white);
    QColor color;

    color.setRed(white.red() + ((green.red() - white.red()) * percent));
    color.setGreen(white.green() + ((green.green() - white.green())  * percent));
    color.setBlue(white.blue() + ((green.blue() - white.blue()) * percent));

    return color;
}

PinItem::PinItem(ComponentItem *parent, const double &x, const double y, const int &angle) :
    QObject(parent),
    QGraphicsEllipseItem(parent),
    m_angle(angle)
{
    setPen(QPen(QColor(35, 40, 50), 1));
    setBrush(Qt::white);
    setRect(0, 0, 10, 10);
    setPos(x, y);

    setAcceptHoverEvents(true);
}

void PinItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setRect(-2, -2, 14, 14);
}

void PinItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setRect(0, 0, 10, 10);
}

void PinItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}
