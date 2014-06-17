#ifndef NORGATE_H
#define NORGATE_H

#include <component.h>

#include <QGraphicsPathItem>
#include <QPen>

class NorGateItem : public ComponentItem
{
    Q_OBJECT

    public:
        NorGateItem(Component *component);

    public slots:
        void updateOutputs();
};

class NorGate : public Component
{
    Q_OBJECT

    public:
        NorGate(QObject *parent = 0);

        QString category() const;
        QString name() const;

        ComponentItem *item();
};

#endif // NORGATE_H
