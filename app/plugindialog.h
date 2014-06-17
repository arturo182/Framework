#ifndef PLUGINDIALOG_H
#define PLUGINDIALOG_H

#include <QDialog>

class ComponentPlugin;

namespace Ui
{
    class PluginDialog;
}

class PluginDialog : public QDialog
{
    Q_OBJECT

    public:
        PluginDialog(const QMap<QString, ComponentPlugin*> &plugins, QWidget *parent = 0);
        ~PluginDialog();

    private:
        Ui::PluginDialog *m_ui;
};

#endif // PLUGINDIALOG_H
