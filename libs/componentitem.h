#ifndef COMPONENTITEM_H
#define COMPONENTITEM_H

#include "global.h"

#include <QGraphicsPathItem>
#include <QObject>

class Component;
class OutputPin;
class InputPin;

class LIB_EXPORT ComponentItem : public QObject, public QGraphicsPathItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)

    public:
        ComponentItem(Component *component);

        const Component *component() const { return m_component; }

        virtual QRectF boundingRect() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        virtual bool hasProperties() const { return false; }
        virtual void showProperties() { }

    public slots:
        void update();
        virtual void updateOutputs() { }

    protected:
        virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    protected:
        Component *m_component;
        QList<InputPin*> m_inputs;
        QList<OutputPin*> m_outputs;

    friend LIB_EXPORT QDataStream &operator<<(QDataStream &str, const ComponentItem &item);
    friend LIB_EXPORT QDataStream &operator>>(QDataStream &str, ComponentItem &item);
};

#endif // COMPONENTITEM_H
