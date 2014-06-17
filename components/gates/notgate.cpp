#include "notgate.h"

#include <outputpin.h>
#include <inputpin.h>

NotGateItem::NotGateItem(Component *component) :
    ComponentItem(component)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    path.moveTo(20, 0);
    path.lineTo(20, 30);
    path.lineTo(50, 15);
    path.lineTo(20, 0);

    path.addEllipse(50, 12.5, 5, 5);

    path.moveTo(5, 15);
    path.lineTo(20, 15);

    path.moveTo(55, 15);
    path.lineTo(65, 15);

    setPath(path);

    m_inputs << new InputPin(this, 0, 10, 270);

    m_outputs << new OutputPin(this, 60, 10, 90);

    updateOutputs();
}

void NotGateItem::updateOutputs()
{
    m_outputs[0]->setValue(255 - m_inputs[0]->value());
}

NotGate::NotGate(QObject *parent) :
    Component(parent)
{
}

QString NotGate::category() const
{
    return "Logic gates";
}

QString NotGate::name() const
{
    return "NOT gate";
}

ComponentItem *NotGate::item()
{
    return new NotGateItem(this);
}

