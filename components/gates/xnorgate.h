#ifndef XNORGATE_H
#define XNORGATE_H

#include <component.h>

#include <QGraphicsPathItem>
#include <QPen>

class XnorGateItem : public ComponentItem
{
    Q_OBJECT

    public:
        XnorGateItem(Component *component);

    public slots:
        void updateOutputs();
};

class XnorGate : public Component
{
    Q_OBJECT

    public:
        XnorGate(QObject *parent = 0);

        QString category() const;
        QString name() const;

        ComponentItem *item();
};

#endif // XNORGATE_H
