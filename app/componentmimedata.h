#ifndef COMPONENTMIMEDATA_H
#define COMPONENTMIMEDATA_H

#include <QMimeData>

class Component;

class ComponentMimeData : public QMimeData
{
	Q_OBJECT

	public:
		ComponentMimeData();

		void setComponent(Component *component) { m_component = component; }
		Component *component() const { return m_component; }

	private:
		Component *m_component;
};

#endif // COMPONENTMIMEDATA_H
