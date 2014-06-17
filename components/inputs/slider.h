#ifndef SLIDER_H
#define SLIDER_H

#include <component.h>

#include <QGraphicsPathItem>
#include <QPen>

class SliderItem : public ComponentItem
{
    Q_OBJECT

    public:
        SliderItem(Component *component);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    private:
        bool m_mouseDown;
};

class Slider : public Component
{
    Q_OBJECT

    public:
        Slider(QObject *parent = 0);

        QString category() const;
        QString name() const;

        ComponentItem *item();
};

#endif // SLIDER_H
