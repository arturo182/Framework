#include "component.h"

Component::Component(QObject *parent) :
    QObject(parent)
{ }

QPixmap Component::icon()
{
    ComponentItem *previewItem = item();

    const float width = previewItem->boundingRect().width();
    const float height = previewItem->boundingRect().height();
    const float size = qMax(width, height);
    QPixmap preview(size, size);
    preview.fill(Qt::transparent);

    QPainter p(&preview);
    p.translate((size - width) / 2, (size - height) / 2);
    p.setRenderHint(QPainter::Antialiasing);
    previewItem->paint(&p, 0, 0);
    delete previewItem;

    return preview.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}
