#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(StorProject *StPr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
       ui->setupUi(this);

    tStorage = StPr;

    StakeGen = new QStackedWidget;
    tDialGen = new DialGen(tStorage, this);

    StakeGen->addWidget(tDialGen->GetIDSplitter());


//   tDialNew = new SvidDialNew(this);
//    StakeGen->addWidget(tDialNew->GetIDSplitter());


     setCentralWidget(StakeGen);





}

MainWindow::~MainWindow()
{
    delete ui;
}

