#ifndef NANDGATE_H
#define NANDGATE_H

#include <component.h>

#include <QGraphicsPathItem>
#include <QPen>

class NandGateItem : public ComponentItem
{
    Q_OBJECT

    public:
        NandGateItem(Component *component);

    public slots:
        void updateOutputs();
};

class NandGate : public Component
{
    Q_OBJECT

    public:
        NandGate(QObject *parent = 0);

        QString category() const;
        QString name() const;

        ComponentItem *item();
};

#endif // NANDGATE_H
