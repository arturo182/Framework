#include "componenttree.h"

#include "componentlist.h"
#include "component.h"

#include <QApplication>
#include <QMenu>

ComponentDelegate::ComponentDelegate(QTreeWidget *treeWidget) :
    m_treeWidget(treeWidget)
{
}

void ComponentDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QAbstractItemModel *model = index.model();

    if(!model->parent(index).isValid()) {
        QStyleOptionButton buttonOption;

        buttonOption.state = option.state;
        buttonOption.state &= ~QStyle::State_HasFocus;

        buttonOption.rect = option.rect;
        buttonOption.palette = option.palette;
        buttonOption.features = QStyleOptionButton::None;
        m_treeWidget->style()->drawControl(QStyle::CE_PushButton, &buttonOption, painter, m_treeWidget);

        QStyleOption branchOption;
        static const int i = 9;
        QRect r = option.rect;
        branchOption.rect = QRect(r.left() + i/2, r.top() + (r.height() - i)/2, i, i);
        branchOption.palette = option.palette;
        branchOption.state = QStyle::State_Children;

        if (m_treeWidget->isExpanded(index))
            branchOption.state |= QStyle::State_Open;

        m_treeWidget->style()->drawPrimitive(QStyle::PE_IndicatorBranch, &branchOption, painter, m_treeWidget);

        QRect textrect = QRect(r.left() + i * 2, r.top(), r.width() - ((5*i)/2), r.height());
        QString text = elidedText(option.fontMetrics, textrect.width(), Qt::ElideMiddle, model->data(index, Qt::DisplayRole).toString());
        m_treeWidget->style()->drawItemText(painter, textrect, Qt::AlignCenter, option.palette, m_treeWidget->isEnabled(), text);
    } else {
        QItemDelegate::paint(painter, option, index);
    }
}

QSize ComponentDelegate::sizeHint(const QStyleOptionViewItem &opt, const QModelIndex &index) const
{
    return QItemDelegate::sizeHint(opt, index) + QSize(2, 2);
}

ComponentTree::ComponentTree(QWidget *parent) :
    QTreeWidget(parent),
    m_delegate(new ComponentDelegate(this)),
    m_viewMode(QListView::IconMode)
{
    setItemDelegate(m_delegate);

    connect(this, SIGNAL(itemPressed(QTreeWidgetItem*, int)), SLOT(handleMousePress(QTreeWidgetItem*)));
}

ComponentTree::~ComponentTree()
{
    delete m_delegate;
    m_delegate = 0;
}

void ComponentTree::addComponent(Component *component)
{
    const QString componentName = component->metaObject()->className();
    if(m_components.contains(componentName))
        return;

    m_components.insert(componentName, component);

    const QString categoryName = component->category();
    QTreeWidgetItem *categoryItem = m_categories.value(categoryName);
    if(!categoryItem) {
        categoryItem = new QTreeWidgetItem();
        categoryItem->setText(0, categoryName);
        addTopLevelItem(categoryItem);

        ComponentList *listWidget = new ComponentList();
        listWidget->setViewMode(m_viewMode);

        QTreeWidgetItem *listItem = new QTreeWidgetItem(categoryItem);
        setItemWidget(listItem, 0, listWidget);

        setItemExpanded(categoryItem, true);

        m_categories.insert(categoryName, categoryItem);
    }

    QTreeWidgetItem *childItem = categoryItem->child(0);
    if(!childItem)
        return;

    ComponentList *listWidget = qobject_cast<ComponentList*>(itemWidget(childItem, 0));
    if(!listWidget)
        return;

    listWidget->addComponent(component);

    adjustListHeight(categoryItem);
}

Component *ComponentTree::component(const QString &name)
{
    return m_components.value(name);
}

void ComponentTree::setViewMode(const QListView::ViewMode &mode)
{
    m_viewMode = mode;
    updateLists();
}

void ComponentTree::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;

    QAction *iconViewAction = menu.addAction(tr("Icon view"), this, SLOT(setIconMode()));
    iconViewAction->setCheckable(true);
    iconViewAction->setChecked(m_viewMode == QListView::IconMode);

    QAction *listViewAction = menu.addAction(tr("List view"), this, SLOT(setListMode()));
    listViewAction->setCheckable(true);
    listViewAction->setChecked(m_viewMode == QListView::ListMode);

    menu.exec(event->globalPos());
}

void ComponentTree::resizeEvent(QResizeEvent *event)
{
    QTreeWidget::resizeEvent(event);

    for(int i = 0; i < topLevelItemCount(); ++i)
        adjustListHeight(topLevelItem(i));
}

void ComponentTree::handleMousePress(QTreeWidgetItem *item)
{
    if(!(qApp->mouseButtons() & Qt::LeftButton))
        return;

    if(!item)
        return;

    if(item->parent())
        return;

    item->setExpanded(!item->isExpanded());
}

void ComponentTree::setIconMode()
{
    setViewMode(QListView::IconMode);
}

void ComponentTree::setListMode()
{
    setViewMode(QListView::ListMode);
}

void ComponentTree::updateLists()
{
    for(int i = 0; i < topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = topLevelItem(i);

        if(ComponentList *list = qobject_cast<ComponentList*>(itemWidget(item->child(0), 0))) {
            list->setViewMode(m_viewMode);
        }

        adjustListHeight(topLevelItem(i));
    }

    updateGeometries();
}

void ComponentTree::adjustListHeight(QTreeWidgetItem *item)
{
    QTreeWidgetItem *childItem = item->child(0);
    if(!childItem)
        return;

    if(ComponentList *listWidget = qobject_cast<ComponentList*>(itemWidget(childItem, 0))) {
        listWidget->doItemsLayout();

        const int height = qMax(listWidget->contentsSize().height() ,1);
        listWidget->setFixedHeight(height);
        childItem->setSizeHint(0, QSize(-1, height - 1));
    }
}
