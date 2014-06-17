#include "switch.h"

#include <outputpin.h>

#include <QPainter>

SwitchItem::SwitchItem(Component *component) :
    ComponentItem(component),
    m_mouseDown(false)
{
    QPainterPath path;
    path.addRect(0, 0, 50, 50);
    path.moveTo(50, 25);
    path.lineTo(65, 25);
    setPath(path);

    m_outputs << new OutputPin(this, 60, 20, 90);
}

void SwitchItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    const QRectF surface(5, 15, 40, 20);
    if(surface.contains(event->pos())) {
        if(m_outputs[0]->value() == 0) {
            m_outputs[0]->setValue(255);
        } else {
            m_outputs[0]->setValue(0);
        }

        m_mouseDown = true;
        setFlag(QGraphicsItem::ItemIsMovable, false);
    }

    ComponentItem::mousePressEvent(event);
}

void SwitchItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    ComponentItem::mouseReleaseEvent(event);

    if(!m_mouseDown)
        return;

    m_mouseDown = false;
    setFlag(QGraphicsItem::ItemIsMovable);
}

void SwitchItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ComponentItem::paint(painter, option, widget);

    painter->setPen(Qt::NoPen);
    painter->setBrush((m_outputs[0]->value() == 255) ? QColor(130, 180, 10) : QColor(35, 40, 50));
    painter->drawRoundedRect(QRect(5, 15, 40, 20), 12, 12);

    QLinearGradient bgGradient(0, 15, 0, 35);
    bgGradient.setColorAt(0, Qt::white);
    bgGradient.setColorAt(1, QColor(220, 220, 220));
    bgGradient.setSpread(QGradient::RepeatSpread);

    painter->setPen(QPen(QColor(130, 140, 140), 1.0));
    painter->setBrush(bgGradient);
    painter->drawEllipse((m_outputs[0]->value() == 255) ? QRect(28, 15, 20, 20) : QRect(5, 15, 20, 20));
}

Switch::Switch(QObject *parent) :
    Component(parent)
{
}

QString Switch::category() const
{
    return "Inputs";
}

QString Switch::name() const
{
    return "Switch";
}

ComponentItem *Switch::item()
{
    return new SwitchItem(this);
}
