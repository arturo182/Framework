#ifndef XORGATE_H
#define XORGATE_H

#include <component.h>

#include <QGraphicsPathItem>
#include <QPen>

class XorGateItem : public ComponentItem
{
    Q_OBJECT

    public:
        XorGateItem(Component *component);

    public slots:
        void updateOutputs();
};

class XorGate : public Component
{
    Q_OBJECT

    public:
        XorGate(QObject *parent = 0);

        QString category() const;
        QString name() const;

        ComponentItem *item();
};

#endif // XORGATE_H
