#include "componentitem.h"

#include "component.h"
#include "outputpin.h"
#include "inputpin.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDialog>
#include <QPen>

ComponentItem::ComponentItem(Component *component) :
    m_component(component)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemSendsGeometryChanges);
    setPen(QPen(QColor(35, 40, 50), 2.0));
    setBrush(Qt::white);
}

QRectF ComponentItem::boundingRect() const
{
    QRectF rect = QGraphicsPathItem::boundingRect();

    foreach(InputPin *input, m_inputs)
        rect |= input->boundingRect().translated(input->pos());

    foreach(OutputPin *output, m_outputs)
        rect |= output->boundingRect().translated(output->pos());

    return rect;
}

QVariant ComponentItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if((change == ItemPositionHasChanged) || (change == ItemRotationHasChanged) || (change == ItemScaleHasChanged)) {
        foreach(InputPin *input, m_inputs)
            input->updateWires();

        foreach(OutputPin *output, m_outputs)
            output->updateWires();
    } else if(change == QGraphicsItem::ItemSelectedChange) {
        if(value.toBool()) {
            QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
            effect->setOffset(0, 0);
            effect->setColor(QColor(130, 180, 10));
            effect->setBlurRadius(15 * scene()->views().first()->transform().m11()); //also known as scale
            setGraphicsEffect(effect);
        } else {
            setGraphicsEffect(0);
        }
    }

    if(change == ItemPositionChange) {
        QPoint newPos = QGraphicsPathItem::itemChange(change, value).toPoint();

        if(scene() && scene()->property("snapToGrid").toBool()) {
            const int gridSize = scene()->property("gridSize").toInt();

            newPos.setX(newPos.x() - (newPos.x() % gridSize));
            newPos.setY(newPos.y() - (newPos.y() % gridSize));
        }

        return newPos;
    }

    return QGraphicsPathItem::itemChange(change, value);
}

void ComponentItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawPath(path());
}

void ComponentItem::update()
{
    QGraphicsPathItem::update();
}

QDataStream &operator<<(QDataStream &str, const ComponentItem &item)
{
    str << item.pos();
    str << item.rotation();
    str << item.scale();

    foreach(OutputPin *output, item.m_outputs) {
        str << output->value();
    }

    return str;
}

QDataStream &operator>>(QDataStream &str, ComponentItem &item)
{
    QPointF pos;
    str >> pos;
    item.setPos(pos);

    qreal rotation;
    str >> rotation;
    item.setRotation(rotation);

    qreal scale;
    str >> scale;
    item.setScale(scale);

    foreach(OutputPin *output, item.m_outputs) {
        quint8 value;
        str >> value;
        output->setValue(value);
    }

    return str;
}
