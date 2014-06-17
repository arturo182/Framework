#ifndef COMPONENT_H
#define COMPONENT_H

#include <QGraphicsDropShadowEffect>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QPen>

#include "componentitem.h"
#include "pinitem.h"
#include "global.h"
#include "wire.h"

class LIB_EXPORT Component : public QObject
{
	Q_OBJECT

	public:
		Component(QObject *parent);

		virtual QString name() const = 0;
		virtual QString category() const = 0;
		QPixmap icon();

		virtual ComponentItem *item() = 0;
};

#endif // COMPONENT_H
