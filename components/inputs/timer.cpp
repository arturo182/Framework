#include "timer.h"

#include <outputpin.h>

#include <QInputDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QDebug>
#include <QLabel>
#include <QDialogButtonBox>

TimerProperties::TimerProperties(TimerItem *timer, QWidget *parent) :
    QDialog(parent),
    m_timer(timer),
    m_signalSpinBox(new QSpinBox),
    m_repeatSpinBox(new QSpinBox)
{
    m_signalSpinBox->setMinimum(1);
    m_signalSpinBox->setMaximum(INT_MAX);
    m_signalSpinBox->setSuffix(" ms");

    m_repeatSpinBox->setMinimum(1);
    m_repeatSpinBox->setMaximum(INT_MAX);
    m_repeatSpinBox->setSuffix(" ms");

    m_signalSpinBox->setValue(m_timer->m_signalTimer.interval());
    m_repeatSpinBox->setValue(m_timer->m_repeatTimer.interval());

    QDialogButtonBox *buttons = new QDialogButtonBox(this);
    buttons->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttons, SIGNAL(accepted()), SLOT(accept()));
    connect(buttons, SIGNAL(rejected()), SLOT(reject()));

    QFormLayout *layout = new QFormLayout(this);
    layout->addRow("Pulse every", m_signalSpinBox);
    layout->addRow("Pulse lasts:", m_repeatSpinBox);
    layout->addWidget(buttons);
    setLayout(layout);
}

TimerProperties::~TimerProperties()
{
    delete m_signalSpinBox;
    m_signalSpinBox = 0;

    delete m_repeatSpinBox;
    m_repeatSpinBox = 0;
}

void TimerProperties::accept()
{
    m_timer->m_signalTimer.start(m_signalSpinBox->value());
    m_timer->m_repeatTimer.setInterval(m_repeatSpinBox->value());

    QDialog::accept();
}

TimerItem::TimerItem(Component *component) :
    ComponentItem(component)
{
    connect(&m_signalTimer, SIGNAL(timeout()), SLOT(signalTimeout()));
    connect(&m_repeatTimer, SIGNAL(timeout()), SLOT(repeatTimeout()));

    m_signalTimer.setSingleShot(true);
    m_repeatTimer.setSingleShot(true);

    m_signalTimer.start(1000);
    m_repeatTimer.setInterval(1000);

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    path.addRect(0, 0, 50, 50);
    path.addEllipse(5, 5, 40, 40);

    path.moveTo(50, 25);
    path.lineTo(65, 25);

    path.moveTo(25, 25);
    path.lineTo(25, 10);

    path.moveTo(25, 25);
    path.lineTo(37, 22);
    setPath(path);

    m_outputs << new OutputPin(this, 60, 20, 90);
}

bool TimerItem::hasProperties() const
{
    return true;
}

void TimerItem::showProperties()
{
    TimerProperties dlg(this);
    dlg.exec();
}

void TimerItem::signalTimeout()
{
    m_outputs[0]->setValue(255);
    m_repeatTimer.start();
}

void TimerItem::repeatTimeout()
{
    m_outputs[0]->setValue(0);
    m_signalTimer.start();
}

Timer::Timer(QObject *parent) :
    Component(parent)
{
}

QString Timer::category() const
{
    return "Inputs";
}

QString Timer::name() const
{
    return "Timer";
}

ComponentItem *Timer::item()
{
    return new TimerItem(this);
}
