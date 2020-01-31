#include "mainwindow.h"
#include <QApplication>
#include "StorProject.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    StorProject *tStorage = new StorProject(a.applicationDirPath());
    MainWindow w(tStorage);
    w.show();

    return a.exec();
}
