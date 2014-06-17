#include "mainwindow.h"

#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("Framework");
    QApplication::setOrganizationName("arturo182");
    QSettings::setDefaultFormat(QSettings::IniFormat);

    QApplication app(argc, argv);

    MainWindow wnd;
    wnd.show();

    return app.exec();
}
