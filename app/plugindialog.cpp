#include "plugindialog.h"
#include "ui_plugindialog.h"

#include <componentplugin.h>
#include <component.h>

PluginDialog::PluginDialog(const QMap<QString, ComponentPlugin *> &plugins, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::PluginDialog)
{
    m_ui->setupUi(this);

    QMapIterator<QString, ComponentPlugin*> it(plugins);
    while(it.hasNext()) {
        it.next();

        QTreeWidgetItem *treeItem = new QTreeWidgetItem(m_ui->treeWidget);
        treeItem->setIcon(0, QIcon(":/glyphs/plugin.png"));
        treeItem->setText(0, it.key());

        foreach(Component *component, it.value()->components()) {
            QTreeWidgetItem *childItem = new QTreeWidgetItem(treeItem);
            childItem->setIcon(0, QIcon(":/glyphs/package.png"));
            childItem->setText(0, component->name());
            childItem->setText(1, component->category());
        }

        m_ui->treeWidget->expandItem(treeItem);
    }
}

PluginDialog::~PluginDialog()
{
    delete m_ui;
}
