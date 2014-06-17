#include "plugin.h"

#include "nandgate.h"
#include "xnorgate.h"
#include "andgate.h"
#include "notgate.h"
#include "norgate.h"
#include "xorgate.h"
#include "orgate.h"
#include "buffer.h"

#include <QtPlugin>

Plugin::Plugin(QObject *parent) :
	ComponentPlugin(parent)
{
	m_components << new Buffer(this);
	m_components << new AndGate(this);
	m_components << new NandGate(this);
	m_components << new NorGate(this);
	m_components << new NotGate(this);
	m_components << new OrGate(this);
	m_components << new XnorGate(this);
	m_components << new XorGate(this);
}


