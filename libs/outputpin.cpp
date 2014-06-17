#include "outputpin.h"

#include "wire.h"

#include <QBrush>

OutputPin::OutputPin(ComponentItem *parent, const double &x, const double y, const int &angle) :
    PinItem(parent, x, y, angle),
    m_value(0)
{ }

OutputPin::~OutputPin()
{
    qDeleteAll(m_wires);
    m_wires.clear();
}

void OutputPin::addWire(Wire *wire)
{
    m_wires << wire;
}

void OutputPin::removeWire(Wire *wire)
{
    m_wires.removeAll(wire);
}

void OutputPin::updateWires()
{
    foreach(Wire *wire, m_wires)
        wire->updatePath();
}

void OutputPin::setValue(const quint8 &value)
{
    if(m_value == value)
        return;

    m_value = value;

    setBrush(colorForValue(m_value));
    update();

    emit valueChanged(m_value);
}
