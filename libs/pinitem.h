#ifndef PINITEM_H
#define PINITEM_H

#include "global.h"

#include <QGraphicsEllipseItem>
#include <QPointer>
#include <QObject>

class ComponentItem;

class LIB_EXPORT PinItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

    public:
        static QColor colorForValue(const quint8 &value);

    public:
        PinItem(ComponentItem *parent, const double &x, const double y, const int &angle = -1);

        int angle() const { return m_angle; }

        virtual void updateWires() = 0;

    protected:
        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

    private:
        int m_angle;
};
#endif // PINITEM_H
