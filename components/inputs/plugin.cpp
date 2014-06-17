#include "plugin.h"

#include "button.h"
#include "slider.h"
#include "switch.h"
#include "mouse.h"
#include "timer.h"

#include <QtPlugin>

Plugin::Plugin(QObject *parent) :
	ComponentPlugin(parent)
{
	m_components << new Button(this);
	m_components << new Mouse(this);
	m_components << new Slider(this);
	m_components << new Switch(this);
	m_components << new Timer(this);

}

