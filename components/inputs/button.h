#ifndef BUTTON_H
#define BUTTON_H

#include <component.h>

class ButtonItem : public ComponentItem
{
    Q_OBJECT

    public:
        ButtonItem(Component *component);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    private:
        bool m_mouseDown;
};

class Button : public Component
{
    Q_OBJECT

    public:
        Button(QObject *parent = 0);

        QString category() const;
        QString name() const;

        ComponentItem *item();
};

#endif // BUTTON_H
