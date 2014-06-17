#include "componentlist.h"

#include "componentmimedata.h"
#include "component.h"

#include <QDebug>

ComponentList::ComponentList(QWidget *parent) :
    QListWidget(parent)
{
    setDragDropMode(QAbstractItemView::DragDrop);
    setFocusPolicy(Qt::NoFocus);
    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setIconSize(QSize(24, 24));
    setMovement(QListView::Static);
    setResizeMode(QListView::Adjust);
    setSelectionMode(QListView::NoSelection);
    setSortingEnabled(true);
    setSpacing(1);
    setUniformItemSizes(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void ComponentList::addComponent(Component *component)
{
    QListWidgetItem *item = new QListWidgetItem(this);
    item->setIcon(component->icon());
    item->setText(component->name());

    m_components.insert(item, component);
}

void ComponentList::mouseMoveEvent(QMouseEvent *event)
{
    if(!(event->buttons() & Qt::LeftButton))
        return;

    if(!currentItem())
        return;

    Component *component = m_components.value(currentItem());

    ComponentMimeData *mimeData = new ComponentMimeData();
    mimeData->setComponent(component);

    ComponentItem *item = component->item();
    QPixmap preview(item->boundingRect().width(), item->boundingRect().height());
    preview.fill(Qt::transparent);

    QPainter p(&preview);
    p.translate( - item->boundingRect().x(),  - item->boundingRect().y());
    p.setRenderHint(QPainter::Antialiasing);
    item->paint(&p, 0, 0);

    delete item;

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(preview);
    drag->setHotSpot(preview.rect().center());
    drag->start(Qt::CopyAction | Qt::MoveAction);
}
