#include "buffer.h"

#include <outputpin.h>
#include <inputpin.h>

BufferItem::BufferItem(Component *component) :
    ComponentItem(component)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    path.moveTo(20, 0);
    path.lineTo(20, 30);
    path.lineTo(50, 15);
    path.lineTo(20, 0);

    path.moveTo(5, 15);
    path.lineTo(20, 15);

    path.moveTo(50, 15);
    path.lineTo(65, 15);

    setPath(path);

    m_inputs << new InputPin(this, 0, 10, 270);

    m_outputs << new OutputPin(this, 60, 10, 90);

    updateOutputs();
}

void BufferItem::updateOutputs()
{
    m_outputs[0]->setValue(m_inputs[0]->value());
}

Buffer::Buffer(QObject *parent) :
    Component(parent)
{
}

QString Buffer::category() const
{
    return "Logic gates";
}

QString Buffer::name() const
{
    return "Buffer";
}

ComponentItem *Buffer::item()
{
    return new BufferItem(this);
}
