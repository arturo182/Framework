#include "label.h"

#include <QApplication>
#include <QTextLayout>

LabelItem::LabelItem(Component *component) :
    ComponentItem(component),
    m_text("Text")
{
    QPainterPath path;
    path.addText(0, 0, QFont("Tahoma", 14), m_text);
    setPath(path);
}

QRectF LabelItem::boundingRect() const
{
    return ComponentItem::boundingRect().adjusted(0, 0, 10, 10);
}

void LabelItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);//QColor(35, 40, 50));
    painter->drawRect(ComponentItem::boundingRect());

    painter->translate(5, 5);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::white);
    painter->drawPath(path());
}

Label::Label(QObject *parent) :
    Component(parent)
{

}

QString Label::category() const
{
    return "Utilities";
}

QString Label::name() const
{
    return "Label";
}

ComponentItem *Label::item()
{
    return new LabelItem(this);
}
