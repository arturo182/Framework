#include "commands.h"

#include "scene.h"

#include <componentitem.h>

#include <QDebug>

AddCommand::AddCommand(Scene *scene, ComponentItem *item) :
	m_scene(scene),
	m_item(item)
{
}

void AddCommand::undo()
{
	m_scene->removeItem(m_item);
}

void AddCommand::redo()
{
	m_scene->addItem(m_item);
}

DeleteCommand::DeleteCommand(Scene *scene, const QList<ComponentItem *> &items) :
	m_scene(scene),
	m_items(items)
{

}

void DeleteCommand::undo()
{
	foreach(ComponentItem *item, m_items) {
		m_scene->addItem(item);
	}
}

void DeleteCommand::redo()
{
	foreach(ComponentItem *item, m_items) {
		m_scene->removeItem(item);
	}
}

RotateCommand::RotateCommand(const QList<ComponentItem*> &items, const double &angle) :
	m_items(items),
	m_angle(angle)
{
}

void RotateCommand::undo()
{
	foreach(ComponentItem *item, m_items) {
		if(!item)
			continue;

		item->setRotation(item->rotation() - m_angle);
	}
}

void RotateCommand::redo()
{
	foreach(ComponentItem *item, m_items) {
		if(!item)
			continue;

		item->setRotation(item->rotation() + m_angle);
	}
}

AlignCommand::AlignCommand(const QList<ComponentItem*> &items, const Qt::AlignmentFlag &alignment) :
	m_items(items),
	m_alignment(alignment)
{
	foreach(ComponentItem *item, m_items)
		m_oldPositions << item->pos();
}

void AlignCommand::undo()
{
	for(int i = 0; i < m_items.count(); ++i)
		m_items[i]->setPos(m_oldPositions[i]);
}

void AlignCommand::redo()
{
	if(!m_items.count())
		return;

	qreal minY = m_items.first()->y();
	qreal minX = m_items.first()->x();

	qreal maxY = m_items.first()->y() + m_items.first()->boundingRect().bottom();
	qreal maxX = m_items.first()->x() + m_items.first()->boundingRect().right();

	foreach(ComponentItem *item, m_items) {
		minY = qMin(minY, item->y());
		minX = qMin(minX, item->x());

		maxY = qMax(maxY, item->y() + item->boundingRect().bottom());
		maxX = qMax(maxX, item->x() + item->boundingRect().right());
	}

	foreach(ComponentItem *item, m_items) {
		switch(m_alignment) {
			case Qt::AlignLeft:
				item->setX(minX);
			break;

			case Qt::AlignHCenter:
				item->setX((maxX + minX) / 2 - item->boundingRect().right() / 2);
			break;

			case Qt::AlignRight:
				item->setX(maxX - item->boundingRect().right());
			break;

			case Qt::AlignTop:
				item->setY(minY);
			break;

			case Qt::AlignVCenter:
				item->setY((maxY + minY) / 2 - item->boundingRect().bottom() / 2);
			break;

			case Qt::AlignBottom:
				item->setY(maxY - item->boundingRect().bottom());
			break;

			default:
			break;
		}
	}
}


FlipCommand::FlipCommand(const QList<ComponentItem*> &items, const Qt::Orientation &orientation) :
	m_items(items),
	m_orientation(orientation)
{
}

void FlipCommand::undo()
{
	redo();
}

void FlipCommand::redo()
{
	foreach(ComponentItem *item, m_items) {
		switch(m_orientation) {
			case Qt::Horizontal:
				item->setScale(-1);
			break;

			case Qt::Vertical:
				item->setScale(1);
			break;
		}
	}
}
