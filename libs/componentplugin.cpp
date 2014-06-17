#include "componentplugin.h"

#include <component.h>

ComponentPlugin::ComponentPlugin(QObject *parent) :
    QObject(parent)
{
}

ComponentPlugin::~ComponentPlugin()
{
    qDeleteAll(m_components);
    m_components.clear();
}
