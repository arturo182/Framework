#ifndef PLUGIN_H
#define PLUGIN_H

#include <componentplugin.h>

class Plugin : public ComponentPlugin
{
	Q_OBJECT
	Q_INTERFACES(ComponentPlugin)
	Q_PLUGIN_METADATA(IID "Framework.Plugins.Gates")

	public:
		Plugin(QObject *parent = 0);
};

#endif // PLUGIN_H
