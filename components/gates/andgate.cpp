#include "andgate.h"

#include <outputpin.h>
#include <inputpin.h>

#include <QtPlugin>
#include <QPen>

AndGateItem::AndGateItem(Component *component) :
    ComponentItem(component)
{
    QPainterPath path;
    path.moveTo(20, 0);
    path.lineTo(20, 30);
    path.arcTo(20, 0, 30, 30, -90, 180);
    path.closeSubpath();

    path.moveTo(5, 5);
    path.lineTo(20, 5);

    path.moveTo(5, 25);
    path.lineTo(20, 25);

    path.moveTo(50, 15);
    path.lineTo(65, 15);

    setPath(path);

    m_inputs << new InputPin(this, 0, 0, 270);
    m_inputs << new InputPin(this, 0, 20, 270);

    m_outputs << new OutputPin(this, 60, 10, 90);

    updateOutputs();
}

void AndGateItem::updateOutputs()
{
    m_outputs[0]->setValue(qMin(m_inputs[0]->value(), m_inputs[1]->value()));
}

AndGate::AndGate(QObject *parent) :
    Component(parent)
{
}

QString AndGate::category() const
{
    return "Logic gates";
}

QString AndGate::name() const
{
    return "AND gate";
}

ComponentItem *AndGate::item()
{
    return new AndGateItem(this);
}
