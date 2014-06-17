#ifndef BUFFER_H
#define BUFFER_H

#include <component.h>

#include <QGraphicsPathItem>
#include <QPen>

class BufferItem : public ComponentItem
{
    Q_OBJECT

    public:
        BufferItem(Component *component);

    public slots:
        void updateOutputs();
};

class Buffer : public Component
{
    Q_OBJECT

    public:
        Buffer(QObject *parent = 0);

        QString category() const;
        QString name() const;

        ComponentItem *item();
};

#endif // BUFFER_H
