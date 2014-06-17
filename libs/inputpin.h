#ifndef INPUTPIN_H
#define INPUTPIN_H

#include "pinitem.h"
#include "global.h"

class OutputPin;
class Wire;

class LIB_EXPORT InputPin : public PinItem
{
    Q_OBJECT

    public:
        InputPin(ComponentItem *parent, const double &x, const double &y, const int &angle = -1);
        ~InputPin();

        enum { Type = QGraphicsItem::UserType + 2 };
        int type() const { return Type; }

        const Wire *wire() const { return m_wire; }
        void setWire(Wire *wire);
        void updateWires();

        quint8 value();

    signals:
        void valueChanged(const quint8 &value);

    private slots:
        void updateColor(const quint8 &value);

    private:
        Wire *m_wire;
};

#endif // INPUTPIN_H
