#ifndef ANDGATE_H
#define ANDGATE_H

#include <component.h>

#include <QGraphicsPathItem>
#include <QPen>

class AndGateItem : public ComponentItem
{
    Q_OBJECT

    public:
        AndGateItem(Component *component);

    public slots:
        void updateOutputs();
};

class AndGate : public Component
{
    Q_OBJECT

    public:
        AndGate(QObject *parent = 0);

        QString category() const;
        QString name() const;

        ComponentItem *item();
};

#endif // ANDGATE_H
