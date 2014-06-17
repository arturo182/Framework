#ifndef GRAPH_H
#define GRAPH_H

#include <component.h>

#include <QTimer>

class GraphItem : public ComponentItem
{
    Q_OBJECT

    public:
        GraphItem(Component *component);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    private slots:
        void updateValues();

    private:
        QList<quint8> m_values;
        QTimer m_refreshTimer;
};

class Graph : public Component
{
    Q_OBJECT

    public:
        Graph(QObject *parent = 0);

        QString category() const;
        QString name() const;

        ComponentItem *item();
};

#endif // GRAPH_H
