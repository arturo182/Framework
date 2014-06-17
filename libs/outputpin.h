#ifndef OUTPUTPIN_H
#define OUTPUTPIN_H

#include "pinitem.h"
#include "global.h"

class Wire;

class LIB_EXPORT OutputPin : public PinItem
{
    Q_OBJECT

    public:
        OutputPin(ComponentItem *parent, const double &x, const double y, const int &angle = -1);
        ~OutputPin();

        enum { Type = QGraphicsItem::UserType + 1 };
        int type() const { return Type; }

        QList<Wire*> wires() const { return m_wires; }
        void addWire(Wire *wire);
        void removeWire(Wire *wire);
        void updateWires();

        quint8 value() const { return m_value; }
        void setValue(const quint8 &value);

    signals:
        void valueChanged(const quint8 &value);

    private:
        quint8 m_value;
        QList<Wire*> m_wires;
};

#endif // OUTPUTPIN_H
