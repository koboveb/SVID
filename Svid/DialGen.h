#ifndef SVIDDIAGENN_H
#define SVIDDIAGENN_H


#include "ModelUni.h"

#include "TTextedit.h"
#include "TTableview.h"

#include <QTableView>
#include <QListView>

#include <QSplitter>


#include <QShortcut>
#include <QKeyEvent>

#include <QStackedWidget>
#include <QCalendarWidget>

//#include <QHeaderView> //Временно
//#include <QAbstractScrollArea> //Времено
#include <QScrollBar>


class DialGen: public QObject
{
    QOBJECT_H

public:
    DialGen(StorProject *StPr, QWidget *parent);
    QSplitter *GetIDSplitter();
    void sSetFocus();
    void mClearValinInfo();

private:

    StorProject *tStorage;

    ModelUni *ModelProj;
    ModelUni *ModelData;

    ModelUni *ModelDoc0;
    ModelUni *ModelDoc1;
    ModelUni *ModelDoc2;
    ModelUni *ModelDoc3;

    ModelUni *ModelKeyDoc;

    QStackedWidget *StakeGenSub;
    QStackedWidget *StakeGenSubTab;
    QStackedWidget *StakeGenSubCache;
   // QStackedWidget *StakeGenSubDocum;



    QStackedWidget *StakeForText;

    QSplitter *SplitVer;
    QSplitter *SplitHor;

    QTableView *TableViewInfo;
    //QTableView *TableViewGen;

    QItemSelectionModel *SelecGen;
    QItemSelectionModel *SelecInfo;


    TTextEdit *tTextEdit;

    QTabWidget *tabsRd;

    QList <ModelUni*> lModelCach;
    QList <ModelUni*> lModelDocum;


    QList<TTextEdit*> listTextEdit;
    //QList<QTableView*> lTableViewGen;

     QList<TTableView*> lTableViewGen;

    QList<QListView*> lListViewCacheKey;
    QList<QListView*> lListViewCache;
    QList<QListView*> lListViewDocum;

   // QList<QThread*> lListQThread;

    int tCurrentRowGen;
    int ttCurrentRowGenPrev;

    int tCurrentRowInfoPrev;
    int tCurrentRowInfo;





    bool flagNewView;
    bool flagChangeSlot;
    bool bForSeach;

    QString CurrentData;
    QBitArray parChangeTextBit; //вспомогательный массив для отслеживания изменений в базе
    QString TextSearch;


    int tlfShowLast;
    QList<int> lfShow; //массив строк для перемещения

    int countSearch; // счётчик для перехода по массиву найденных строк

//Методы


    void SlotCurrentChangedTab();

    void SlotCurrentChangedGen (const QItemSelection &selected);
    void SlotCurrentChangedInfo(const QItemSelection &selected);

    void SlotKeyPgUp();
    void SlotKeyPgDown();

    void SlotKeyMyRight();
    void SlotKeyMyLeft();

    void SlotKeyReturn();
    void SlotKeyShiftReturn();


    void SlotKeyNewDoc();

    void SlotKeyRight();
    void SlotKeyLeft();

    void SlotKeyUP();
    void SlotKeyDown();

    void SlotKeyTab();
    void SlotChangedText();

    void SlotKeyEnd();

    void NewRowsInCash(QString TextSearch);
    void NewRowsSave();

    void ScrollBarValueChanged();

    void ScrollBarValueChangedUpDown();


};

#endif // SVIDDIAGENN_H
