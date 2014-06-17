#include "wire.h"

#include "component.h"
#include "outputpin.h"
#include "inputpin.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <qmath.h>

Wire::Wire(InputPin *input, OutputPin *output) :
    m_input(input),
    m_output(output),
    m_startPos(QPointF(-1, -1)),
    m_endPos(QPointF(-1, -1))
{
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);

    updateColor(m_output->value());
    updatePath();

    m_input->setWire(this);
    m_output->addWire(this);

    connect(m_output, SIGNAL(valueChanged(quint8)), SLOT(updateColor(quint8)));
    connect(m_output, SIGNAL(valueChanged(quint8)), m_input, SIGNAL(valueChanged(quint8)));
}

Wire::Wire(const QPointF &start, const QPointF &end) :
    m_input(0),
    m_output(0),
    m_startPos(start),
    m_endPos(end)
{
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);

    updateColor(0);
    updatePath();
}

Wire::~Wire()
{
    if(!m_input && !m_output)
        return;

    m_input->setWire(0);
    m_output->removeWire(this);

    disconnect(m_output, SIGNAL(valueChanged(quint8)), this, SLOT(updateColor(quint8)));
    disconnect(m_output, SIGNAL(valueChanged(quint8)), m_input, SIGNAL(valueChanged(quint8)));
}

QRectF Wire::boundingRect() const
{
    QRectF rect = QGraphicsPathItem::boundingRect();

    return rect.adjusted(-2, -2, 2, 2);
}

quint8 Wire::value() const
{
    if(!m_output)
        return 0;

    return m_output->value();
}

QPointF Wire::startPos() const
{
    if(m_startPos != QPointF(-1, -1))
        return m_startPos;

    if(m_input)
        return m_input->scenePos() + m_input->boundingRect().center();

    return QPointF(-1, -1);
}

void Wire::setStartPos(const QPointF &start)
{
    m_startPos = start;
    updatePath();
}

QPointF Wire::endPos() const
{
    if(m_endPos != QPointF(-1, -1))
        return m_endPos;

    if(m_output)
        return m_output->scenePos() + m_output->boundingRect().center();

    return QPointF(-1, -1);
}

void Wire::setEndPos(const QPointF &end)
{
    m_endPos = end;
    updatePath();
}

float distance(const QPointF &p1, const QPointF &p2)
{
    float vx, vy;

    vx = p2.x() - p1.x();
    vy = p2.y() - p1.y();

    return qSqrt( vx * vx + vy * vy );
}

void Wire::updatePath()
{
    prepareGeometryChange();

    QPointF start = startPos();
    QPointF end = endPos();

    int angle1 = m_input ? m_input->angle() : -1;
    int angle2 = m_output ? m_output->angle() : -1;

    float minX = qMin(start.x(), end.x());
    float maxX = qMax(start.x(), end.x());
    float minY = qMin(start.y(), end.y());
    float maxY = qMax(start.y(), end.y());

    QPointF middle(minX + (maxX - minX) / 2.0, minY + (maxY - minY) / 2.0);
    QPointF c1(middle.x(), minY);
    QPointF c2(middle.x(), maxY);

    if(minY != start.y())  {
        qSwap(start, end);
        qSwap(angle1, angle2);
    }

    float dist = qMin(100.0, distance(start, end) / 2.0);
    QList<QPointF> controlPoints;
    controlPoints << c1 << c2;

    if(angle1 > -1) {
        QPointF d1(dist * qSin(angle1 * (M_PI / 180.0)),
                   -dist * qCos(angle1 * (M_PI / 180.0)));

        d1 += start;

        if(d1.x() == c1.x()) {
            c1.setY(d1.y());
        } else if(d1.y() == c1.y()) {
            c1.setX(d1.x());
        } else {
            controlPoints[0] = d1;
        }
    }

    if(angle2 > -1) {
        QPointF d2(dist * qSin(angle2 * (M_PI / 180.0)),
                   -dist * qCos(angle2 * (M_PI / 180.0)));

        d2 += start;

        if(d2.x() == c2.x()) {
            c2.setY(d2.y());
        } else if(d2.y() == c1.y()) {
            c2.setX(d2.x());
        } else {
            controlPoints[1] = d2;
        }
    }

    QPainterPath path;
    path.moveTo(start);
    path.cubicTo(controlPoints[0], controlPoints[1], end);
    setPath(path);
}



//void Wire::setLine(const QPointF &loc_1, const QPointF &loc_2)
//{

//}

QVariant Wire::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change ==  QGraphicsItem::ItemSelectedChange) {
        if(value.toBool()) {
            QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
            effect->setOffset(0, 0);
            effect->setColor(QColor(130, 180, 10));
            effect->setBlurRadius(8 * scene()->views().first()->transform().m11());
            setGraphicsEffect(effect);
        } else {
            setGraphicsEffect(0);
        }
    }

    return QGraphicsPathItem::itemChange(change, value);
}

void Wire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 6, Qt::SolidLine, Qt::RoundCap));
    painter->drawPath(path());

    painter->setPen(pen());
    painter->drawPath(path());
}

void Wire::updateColor(const quint8 &value)
{
    setPen(QPen(PinItem::colorForValue(value), 4.0, Qt::SolidLine, Qt::RoundCap));
    update();
}

