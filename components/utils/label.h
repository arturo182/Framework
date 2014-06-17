#ifndef LABEL_H
#define LABEL_H

#include <component.h>

class QTextLayout;

class LabelItem : public ComponentItem
{
    Q_OBJECT

    public:
        LabelItem(Component *component);

        QRectF boundingRect() const;

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    private:
        QRectF setupTextLayout(QTextLayout *layout);

    private:
        QString m_text;
};

class Label : public Component
{
    Q_OBJECT

    public:
        Label(QObject *parent = 0);

        QString category() const;
        QString name() const;

        ComponentItem *item();
};

#endif // LABEL_H
