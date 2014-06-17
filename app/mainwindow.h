#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

namespace Ui
{
    class MainWindow;
}

class ComponentPlugin;
class QSignalMapper;
class QUndoStack;
class QSlider;
class Scene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();

        enum { MaxMru = 8 };

    protected:
        void closeEvent(QCloseEvent *event);
        bool eventFilter(QObject *obj, QEvent *e);

    private slots:
        void newFile();
        void open();
        bool save();
        bool saveAs();
        void updateMruMenu();
        void clearMru();
        void print();
        void selectAll();
        void about();
        void aboutPlugins();
        void zoomIn();
        void zoomOut();
        void setZoom(const int &value);
        void updateActions();
        void loadMruFile(const QString &fileName);

    private:
        void loadFile(const QString &fileName);
        bool saveFile(const QString &fileName);
        bool maybeSave();
        void setCurrentFile(const QString &fileName = QString());
        void createZoom();
        void readSettings();
        void writeSettings();
        void connectActions();
        void loadPlugins();

    private:
        Ui::MainWindow *m_ui;
        Scene *m_scene;
        QSlider *m_zoomSlider;
        QSignalMapper *m_mruMapper;
        QString m_fileName;
        QMap<QString, ComponentPlugin*> m_plugins;

};

#endif // MAINWINDOW_H
