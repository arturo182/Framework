#ifndef COMPONENTPLUGIN_H
#define COMPONENTPLUGIN_H

#include "global.h"

class Component;

class LIB_EXPORT ComponentPlugin : public QObject
{
	Q_OBJECT

	public:
		ComponentPlugin(QObject *parent = 0);
		~ComponentPlugin();

		QList<Component*> components() const { return m_components; }

	protected:
		QList<Component*> m_components;

};

Q_DECLARE_INTERFACE(ComponentPlugin, "Framework.ComponentPlugin")

#endif // COMPONENTPLUGIN_H
