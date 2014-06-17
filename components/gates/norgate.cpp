#include "norgate.h"

#include <outputpin.h>
#include <inputpin.h>

NorGateItem::NorGateItem(Component *component) :
    ComponentItem(component)
{
    QPainterPath path;
    path.moveTo(20, 0);
    path.quadTo(30, 15, 20, 30);
    path.quadTo(45, 30, 50, 15);
    path.quadTo(45, 0, 20, 0);

    path.addEllipse(50, 12.5, 5, 5);

    path.moveTo(5, 5);
    path.lineTo(23, 5);

    path.moveTo(5, 25);
    path.lineTo(23, 25);

    path.moveTo(55, 15);
    path.lineTo(65, 15);

    setPath(path);

    m_inputs << new InputPin(this, 0, 0, 270);
    m_inputs << new InputPin(this, 0, 20, 270);

    m_outputs << new OutputPin(this, 60, 10, 90);

    updateOutputs();
}

void NorGateItem::updateOutputs()
{
    m_outputs[0]->setValue(255 - qMax(m_inputs[0]->value(), m_inputs[1]->value()));
}

NorGate::NorGate(QObject *parent) :
    Component(parent)
{
}

QString NorGate::category() const
{
    return "Logic gates";
}

QString NorGate::name() const
{
    return "NOR gate";
}

ComponentItem *NorGate::item()
{
    return new NorGateItem(this);
}
