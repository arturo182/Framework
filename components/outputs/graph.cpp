#include "graph.h"

#include <inputpin.h>

#include <QDebug>

GraphItem::GraphItem(Component *component) :
    ComponentItem(component)
{
    QPainterPath path;
    path.addRect(20, 0, 110, 90);
    path.moveTo(5, 45);
    path.lineTo(20, 45);
    setPath(path);

    m_inputs << new InputPin(this, 0, 40, 270);

    connect(&m_refreshTimer, SIGNAL(timeout()), SLOT(updateValues()));
    m_refreshTimer.start(10);
}

void GraphItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ComponentItem::paint(painter, option, widget);

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, false);

    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(35, 40, 50));
    painter->drawRect(25, 5, 100, 80);

    painter->setBrush(QColor(130, 180, 10));
    for(int i = 100 - m_values.count(); i < m_values.count(); ++i) {
        painter->drawRect(25 + i, 85, 1, -80 * (m_values[i] / 255.0));
    }

    painter->restore();
}

void GraphItem::updateValues()
{
    m_values << m_inputs[0]->value();

    if(m_values.count() > 100)
        m_values.removeFirst();

    update();
}

Graph::Graph(QObject *parent) :
    Component(parent)
{
}

QString Graph::category() const
{
    return "Outputs";
}

QString Graph::name() const
{
    return "Graph";
}

ComponentItem *Graph::item()
{
    return new GraphItem(this);
}
