#include "plugin.h"

#include "digit.h"
#include "graph.h"

#include <QtPlugin>

Plugin::Plugin(QObject *parent) :
	ComponentPlugin(parent)
{
	m_components << new Digit(this);
	m_components << new Graph(this);
}
