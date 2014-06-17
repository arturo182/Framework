#ifndef MOUSE_H
#define MOUSE_H

#include <component.h>
#include <QTimer>

class MouseItem : public ComponentItem
{
    Q_OBJECT

    public:
        MouseItem(Component *component);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    public slots:
        void updateOutputs();

    private:
        QTimer m_refreshTimer;
};

class Mouse : public Component
{
    Q_OBJECT

    public:
        Mouse(QObject *parent = 0);

        QString category() const;
        QString name() const;

        ComponentItem *item();
};

#endif // MOUSE_H
