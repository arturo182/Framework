#include "inputpin.h"

#include "componentitem.h"
#include "outputpin.h"
#include "wire.h"

#include <QBrush>

InputPin::InputPin(ComponentItem *parent, const double &x, const double &y, const int &angle) :
    PinItem(parent, x, y, angle),
    m_wire(0)
{
    connect(this, SIGNAL(valueChanged(quint8)), parent, SLOT(updateOutputs()));
    connect(this, SIGNAL(valueChanged(quint8)), parent, SLOT(update()));

    connect(this, SIGNAL(valueChanged(quint8)), SLOT(updateColor(quint8)));
}

InputPin::~InputPin()
{
    if(!m_wire)
        return;

    delete m_wire;
    m_wire = 0;
}

void InputPin::setWire(Wire *wire)
{
    m_wire = wire;

    emit valueChanged(value());
}

void InputPin::updateWires()
{
    if(!m_wire)
        return;

    m_wire->updatePath();
}

quint8 InputPin::value()
{
    if(!m_wire)
        return 0;

    return m_wire->value();
}

void InputPin::updateColor(const quint8 &value)
{
    setBrush(colorForValue(value));
}
