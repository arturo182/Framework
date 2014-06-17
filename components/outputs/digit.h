#ifndef DIGIT_H
#define DIGIT_H

#include <component.h>
#include <QTimer>

class DigitItem : public ComponentItem
{
    Q_OBJECT

    public:
        DigitItem(Component *component);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    private:
        static const char segmentChars[16][8];
};

class Digit : public Component
{
    Q_OBJECT

    public:
        Digit(QObject *parent = 0);

        QString category() const;
        QString name() const;

        ComponentItem *item();
};

#endif // DIGIT_H
