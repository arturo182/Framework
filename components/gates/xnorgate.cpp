#include "xnorgate.h"

#include <outputpin.h>
#include <inputpin.h>

XnorGateItem::XnorGateItem(Component *component) :
    ComponentItem(component)
{
    QPainterPath path;
    path.moveTo(20, 0);
    path.quadTo(30, 15, 20, 30);
    path.quadTo(45, 30, 50, 15);
    path.quadTo(45, 0, 20, 0);

    path.moveTo(15, 1);
    path.quadTo(25, 15, 15, 29);
    path.quadTo(25, 15, 15, 1);

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

void XnorGateItem::updateOutputs()
{
    m_outputs[0]->setValue(255 - qMax(qMin<quint8>(255 - m_inputs[0]->value(), m_inputs[1]->value()), qMin<quint8>(m_inputs[0]->value(), 255 - m_inputs[1]->value())));
}

XnorGate::XnorGate(QObject *parent) :
    Component(parent)
{
}

QString XnorGate::category() const
{
    return "Logic gates";
}

QString XnorGate::name() const
{
    return "XNOR gate";
}

ComponentItem *XnorGate::item()
{
    return new XnorGateItem(this);
}
