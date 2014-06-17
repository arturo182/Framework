#include "slider.h"

#include <outputpin.h>
#include <inputpin.h>

#include <QApplication>

SliderItem::SliderItem(Component *component) :
    ComponentItem(component),
    m_mouseDown(false)
{
    QPainterPath path;
    path.addRect(0, 0, 90, 34);
    path.moveTo(90, 17);
    path.lineTo(105, 17);
    setPath(path);

    m_outputs << new OutputPin(this, 100, 12, 90);
}

void SliderItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ComponentItem::paint(painter, option, widget);

    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(220, 220, 220));
    painter->drawRoundRect(QRect(5, 14, 80, 6), 15, 50);

    painter->setBrush(QColor(130, 180, 10));

    const float percent = qBound(0.0, m_outputs[0]->value() / 255.0, 1.0);
    painter->drawEllipse(QRect(5 + percent * 70, 11, 12, 12));
}

void SliderItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    const float percent = qBound(0.0, m_outputs[0]->value() / 255.0, 1.0);

    const QRectF handle(5 + percent * 70, 11, 12, 12);
    if(handle.contains(event->pos())) {
        m_mouseDown = true;
        setFlag(QGraphicsItem::ItemIsMovable, false);
    }

    ComponentItem::mousePressEvent(event);
}

void SliderItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    ComponentItem::mouseMoveEvent(event);

    if(!m_mouseDown)
        return;

    const int xPos = qBound(5.0, event->pos().x(), 85.0) - 5;
    m_outputs[0]->setValue(255 * (xPos / 80.0));
    update();
}

void SliderItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_mouseDown = false;
    setFlag(QGraphicsItem::ItemIsMovable);

    ComponentItem::mouseReleaseEvent(event);
}

Slider::Slider(QObject *parent) :
    Component(parent)
{
}

QString Slider::category() const
{
    return "Inputs";
}

QString Slider::name() const
{
    return "Slider";
}

ComponentItem *Slider::item()
{
    return new SliderItem(this);
}
