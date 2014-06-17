#ifndef COMPONENTTREE_H
#define COMPONENTTREE_H

#include <QItemDelegate>
#include <QTreeWidget>
#include <QListView>

class Component;

class ComponentDelegate : public QItemDelegate
{
    public:
        ComponentDelegate(QTreeWidget *treeWidget);

        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    private:
        QTreeWidget *m_treeWidget;
};

class ComponentTree : public QTreeWidget
{
    Q_OBJECT

    public:
        ComponentTree(QWidget *parent = 0);
        ~ComponentTree();

        void addComponent(Component *component);
        Component *component(const QString &name);

        void setViewMode(const QListView::ViewMode &mode);
        QListView::ViewMode viewMode() const { return m_viewMode; }

    protected:
        void contextMenuEvent(QContextMenuEvent *event);
        void resizeEvent(QResizeEvent *event);

    private slots:
        void handleMousePress(QTreeWidgetItem *item);
        void setIconMode();
        void setListMode();
        void updateLists();

    private:
        void adjustListHeight(QTreeWidgetItem *item);

    private:
        QHash<QString, QTreeWidgetItem*> m_categories;
        QHash<QString, Component*> m_components;
        ComponentDelegate *m_delegate;
        QListView::ViewMode m_viewMode;
};

#endif // COMPONENTTREE_H
