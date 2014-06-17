#ifndef WIRE_H
#define WIRE_H

#include "global.h"

#include <QGraphicsPathItem>

class OutputPin;
class InputPin;

class LIB_EXPORT Wire : public QObject, public QGraphicsPathItem
{
    Q_OBJECT

    public:
        Wire(InputPin *input, OutputPin *output);
        Wire(const QPointF &start, const QPointF &end);
        ~Wire();

        QRectF boundingRect() const;

        enum { Type = QGraphicsItem::UserType + 3 };
        int type() const { return Type; }

        quint8 value() const;

        QPointF startPos() const;
        void setStartPos(const QPointF &start);

        QPointF endPos() const;
        void setEndPos(const QPointF &end);

        void updatePath();

    protected:
        QVariant itemChange(GraphicsItemChange change, const QVariant &value);
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    private slots:
        void updateColor(const quint8 &value);

    private:
        InputPin *m_input;
        OutputPin *m_output;

        QPointF m_startPos;
        QPointF m_endPos;
};

#endif // WIRE_H
