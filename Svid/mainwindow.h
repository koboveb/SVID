#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "DialGen.h"


#include <QStackedWidget>
#include <QShortcut>
#include <QKeyEvent>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(StorProject *StPr, QWidget *parent = 0);
    ~MainWindow();


private:


    DialGen *tDialGen;
    StorProject *tStorage;

    Ui::MainWindow *ui;
    QStackedWidget *StakeGen;

};

#endif // MAINWINDOW_H
