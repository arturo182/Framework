#include "plugin.h"

#include "label.h"

#include <QtPlugin>

Plugin::Plugin(QObject *parent) :
	ComponentPlugin(parent)
{
	m_components << new Label(this);
}
