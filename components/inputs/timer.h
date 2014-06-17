#ifndef TIMER_H
#define TIMER_H

#include <component.h>

#include <QGraphicsPathItem>
#include <QDialog>
#include <QTimer>
#include <QPen>

class TimerItem;
class QComboBox;
class QSpinBox;

class TimerProperties : public QDialog
{
    Q_OBJECT

    public:
        TimerProperties(TimerItem *timer, QWidget *parent = 0);
        ~TimerProperties();

    public slots:
        void accept();

    private:
        TimerItem *m_timer;
        QSpinBox *m_signalSpinBox;
        QSpinBox *m_repeatSpinBox;
};

class TimerItem : public ComponentItem
{
    Q_OBJECT

    public:
        TimerItem(Component *component);

        bool hasProperties() const;
        void showProperties();

    private slots:
        void signalTimeout();
        void repeatTimeout();

    private:
        QTimer m_signalTimer;
        QTimer m_repeatTimer;

    friend class TimerProperties;
};

class Timer : public Component
{
    Q_OBJECT

    public:
        Timer(QObject *parent = 0);

        QString category() const;
        QString name() const;

        ComponentItem *item();
};

#endif // TIMER_H
