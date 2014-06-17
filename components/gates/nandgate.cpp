#include "nandgate.h"

#include <outputpin.h>
#include <inputpin.h>

NandGateItem::NandGateItem(Component *component) :
    ComponentItem(component)
{
    QPainterPath path;
    path.moveTo(20, 0);
    path.lineTo(20, 30);
    path.arcTo(20, 0, 30, 30, -90, 180);
    path.closeSubpath();

    path.addEllipse(50, 12.5, 5, 5);

    path.moveTo(5, 5);
    path.lineTo(20, 5);

    path.moveTo(5, 25);
    path.lineTo(20, 25);

    path.moveTo(55, 15);
    path.lineTo(65, 15);

    setPath(path);

    m_inputs << new InputPin(this, 0, 0, 270);
    m_inputs << new InputPin(this, 0, 20, 270);

    m_outputs << new OutputPin(this, 60, 10, 90);

    updateOutputs();
}

void NandGateItem::updateOutputs()
{
    m_outputs[0]->setValue(255 - qMin(m_inputs[0]->value(), m_inputs[1]->value()));
}

NandGate::NandGate(QObject *parent) :
    Component(parent)
{
}

QString NandGate::category() const
{
    return "Logic gates";
}

QString NandGate::name() const
{
    return "NAND gate";
}

ComponentItem *NandGate::item()
{
    return new NandGateItem(this);
}
