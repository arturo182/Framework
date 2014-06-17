#include "digit.h"

#include <inputpin.h>

const char DigitItem::segmentChars[16][8] =
{
    { 1, 1, 1, 1, 1, 1, 0 }, // 0
    { 0, 1, 1, 0, 0, 0, 0 }, // 1
    { 1, 1, 0, 1, 1, 0, 1 }, // 2
    { 1, 1, 1, 1, 0, 0, 1 }, // 3
    { 0, 1, 1, 0, 0, 1, 1 }, // 4
    { 1, 0, 1, 1, 0, 1, 1 }, // 5
    { 1, 0, 1, 1, 1, 1, 1 }, // 6
    { 1, 1, 1, 0, 0, 0, 0 }, // 7
    { 1, 1, 1, 1, 1, 1, 1 }, // 8
    { 1, 1, 1, 1, 0, 1, 1 }, // 9
    { 1, 1, 1, 0, 1, 1, 1 }, // A
    { 0, 0, 1, 1, 1, 1, 1 }, // B
    { 1, 0, 0, 1, 1, 1, 0 }, // C
    { 0, 1, 1, 1, 1, 0, 1 }, // D
    { 1, 0, 0, 1, 1, 1, 1 }, // E
    { 1, 0, 0, 0, 1, 1, 1 }  // F
};

DigitItem::DigitItem(Component *component) :
    ComponentItem(component)
{
    QPainterPath path;
    path.addRect(20, 0, 65, 75);

    path.moveTo(5, 15);
    path.lineTo(20, 15);

    path.moveTo(5, 30);
    path.lineTo(20, 30);

    path.moveTo(5, 45);
    path.lineTo(20, 45);

    path.moveTo(5, 60);
    path.lineTo(20, 60);

    setPath(path);

    m_inputs << new InputPin(this, 0, 10, 270);
    m_inputs << new InputPin(this, 0, 25, 270);
    m_inputs << new InputPin(this, 0, 40, 270);
    m_inputs << new InputPin(this, 0, 55, 270);
}

void DigitItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ComponentItem::paint(painter, option, widget);

    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(130, 180, 10));

    QPainterPath path;

    const int one = (m_inputs[0]->value() > 127) ? 1 : 0;
    const int two = (m_inputs[1]->value() > 127) ? 2 : 0;
    const int four = (m_inputs[2]->value() > 127) ? 4 : 0;
    const int eight = (m_inputs[3]->value() > 127) ? 8 : 0;
    const int num = one + two + four + eight;

    //top
    if(segmentChars[num][0]) {
        path.moveTo(2, 0);
        path.lineTo(33, 0);
        path.lineTo(25, 8);
        path.lineTo(10, 8);
        path.closeSubpath();
    }

    //right up
    if(segmentChars[num][1]) {
        path.moveTo(35, 2);
        path.lineTo(27, 10);
        path.lineTo(27, 20);
        path.lineTo(32, 25);
        path.lineTo(35, 22);
        path.closeSubpath();
    }

    //right bottom
    if(segmentChars[num][2]) {
        path.moveTo(35, 53);
        path.lineTo(27, 45);
        path.lineTo(27, 35);
        path.lineTo(32, 30);
        path.lineTo(35, 33);
        path.closeSubpath();
    }

    //bottom
    if(segmentChars[num][3]) {
        path.moveTo(2, 55);
        path.lineTo(10, 47);
        path.lineTo(25, 47);
        path.lineTo(33, 55);
        path.closeSubpath();
    }

    //left bottom
    if(segmentChars[num][4]) {
        path.moveTo(0, 53);
        path.lineTo(8, 45);
        path.lineTo(8, 35);
        path.lineTo(3, 30);
        path.lineTo(0 ,33);
        path.closeSubpath();
    }

    //left up
    if(segmentChars[num][5]) {
        path.moveTo(0, 2);
        path.lineTo(8, 10);
        path.lineTo(8, 20);
        path.lineTo(3, 25);
        path.lineTo(0, 22);
        path.closeSubpath();
    }

    //middle
    if(segmentChars[num][6]) {
        path.moveTo(5, 27);
        path.lineTo(8, 24);
        path.lineTo(27, 24);
        path.lineTo(30, 27);
        path.lineTo(30, 28);
        path.lineTo(27, 31);
        path.lineTo(8, 31);
        path.lineTo(5, 28);
        path.closeSubpath();
    }

    painter->translate(35, 10);
    painter->drawPath(path);
}

Digit::Digit(QObject *parent) :
    Component(parent)
{
}

QString Digit::category() const
{
    return "Outputs";
}

QString Digit::name() const
{
    return "Digit";
}

ComponentItem *Digit::item()
{
    return new DigitItem(this);
}
