#include "mouse.h"

#include <outputpin.h>

#include <QDesktopWidget>
#include <QApplication>
#include <QCursor>

MouseItem::MouseItem(Component *component) :
    ComponentItem(component)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(0, 0, 80, 60);
    path.addText(70, 24, QFont("", 7), "X");
    path.addText(70, 44, QFont("", 7), "Y");

    path.addRoundedRect(QRect(20, 15, 40, 30), 20, 20);
    path.moveTo(35, 17);
    path.lineTo(35, 43);

    path.moveTo(20, 30);
    path.lineTo(34, 30);

    path.moveTo(80, 20);
    path.lineTo(95, 20);

    path.moveTo(80, 40);
    path.lineTo(95, 40);
    setPath(path);

    m_outputs << new OutputPin(this, 90, 15, 90);
    m_outputs << new OutputPin(this, 90, 35, 90);

    connect(&m_refreshTimer, SIGNAL(timeout()), SLOT(updateOutputs()));
    m_refreshTimer.start(10);
}

void MouseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ComponentItem::paint(painter, option, widget);

    QPainterPath path;
    path.moveTo(20, 30);
    path.cubicTo(0, 35, 25, 10, 5, 10);
    painter->drawPath(path);
}

void MouseItem::updateOutputs()
{
    const QPoint mousePos = QCursor::pos();
    const QRect desktopRect = qApp->desktop()->screenGeometry();
    const quint8 xValue = 255 * mousePos.x() / desktopRect.width();
    const quint8 yValue = 255 * mousePos.y() / desktopRect.height();

    m_outputs[0]->setValue(xValue);
    m_outputs[1]->setValue(yValue);
}

Mouse::Mouse(QObject *parent) :
    Component(parent)
{
}

QString Mouse::category() const
{
    return "Inputs";
}

QString Mouse::name() const
{
    return "Mouse";
}

ComponentItem *Mouse::item()
{
    return new MouseItem(this);
}
