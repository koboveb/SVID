#include "DialGen.h"


DialGen::DialGen(StorProject *StPr, QWidget *parent)
{

    flagChangeSlot = false;
    flagNewView = 0;
    bForSeach = 0;
    countSearch = 0;
    tStorage = StPr;



//-----Создание моделей



             ModelProj = new ModelUni(PROJECT, tStorage);
             ModelData = new ModelUni(DATA, tStorage);

             ModelDoc0 = new ModelUni(DOCUM, tStorage);
             ModelDoc1 = new ModelUni(DOCUM, tStorage);
             ModelDoc2 = new ModelUni(DOCUM, tStorage);
             ModelDoc3 = new ModelUni(DOCUM, tStorage);

             ModelKeyDoc = new ModelUni(DOCKEY, tStorage);


//устанавливаем размер массива

            parChangeTextBit.resize(tStorage->GetFieldCod().length());

//Создание массива текстовых полей
             for (int i = 0; i < tStorage->GetFieldCod().length(); i++)
             {
               tTextEdit = new TTextEdit(parent);
               tTextEdit->setMinimumHeight(20);

               listTextEdit.append(tTextEdit);


               //-----------------------------------------------------------
               ModelUni *ModelCache = new ModelUni(CACHE, tStorage);


              // QListView *tListCacheKey = new QListView(); // Представление в виде списка для кэша ключей
              QListView *tListCache = new QListView(); // Представление в виде списка


               lModelCach << ModelCache;



               if(i == 0)
                {
                   //tListCash->setModel(ModelDoc);
                   //tListCache->setModel(ModelDoc0);
                  tListCache->setModel(ModelKeyDoc);
                  // lListViewCache << tListCache;
                }

               else
                {
                    tListCache->setModel(ModelCache);
                    lListViewCache << tListCache;
                }


            //устанавливаем массив битов для отследивания изменений данных
                parChangeTextBit.clearBit(i);

             }



//Создание Форм

             StakeForText = new QStackedWidget;
             StakeGenSub = new QStackedWidget;
             StakeGenSubTab = new QStackedWidget;
             StakeGenSubCache = new QStackedWidget;
         //    StakeGenSubDocum = new QStackedWidget;


             SplitVer = new QSplitter(Qt::Vertical);
             SplitHor = new QSplitter(Qt::Horizontal);

             TableViewInfo =new QTableView(parent);

             TableViewInfo->setWordWrap(false);
             TableViewInfo->setShowGrid(false);


            // tTextEdit = new TTextEdit(parent);
            // tTextEdit->setMinimumHeight(20);

             tabsRd = new QTabWidget(parent);
             tabsRd->setTabPosition(QTabWidget::South);


             SplitHor->addWidget(TableViewInfo);
             SplitHor->addWidget(SplitVer);


             SplitHor->setStretchFactor(0, 0);
             SplitHor->setStretchFactor(1, 1);

             SplitVer->addWidget(StakeForText);
             SplitVer->addWidget(StakeGenSub);


             StakeGenSub->addWidget(StakeGenSubTab);
             StakeGenSub->addWidget(StakeGenSubCache);
             //StakeGenSub->addWidget(StakeGenSubDocum);


             StakeGenSubTab->addWidget(tabsRd);


             //SplitVer->addWidget(tabsRd);

             SplitVer->setStretchFactor(0, 1);
             SplitVer->setStretchFactor(1, 25);


            //Добавление массива текстовых полей и списка кэша в stake
             for (int i = 0; i < tStorage->GetFieldCod().length(); i++)
            {

               StakeForText->addWidget(listTextEdit.at(i));

               QStackedWidget *StakeGenSubCashSub = new QStackedWidget;

               StakeGenSubCache->addWidget(StakeGenSubCashSub);



// Временно! Исправить!!
/*
               // Временный виджет для текста. Использую вместо числа. Для перспективы
                  QTextEdit *tTextTemp = new QTextEdit(parent);

               // Временный виджет для календаря.
                  QCalendarWidget *CalendarGenSubCash = new QCalendarWidget;



             // qDebug()<<"Type "<<ModelProj->GetField_Type(i);

             // QString tTypeField = ModelProj->GetField_Type(i);

               QString tType = tStorage->Get_FieldDialog().value(i).value(3);


              if (tType == "Gen")
              {

                 // ModelKeyDoc->SetDocKey("25");
              QListView *tListCacheKeyDoc = new QListView(); // Представление для списка структурных номеров
              tListCacheKeyDoc->setModel(ModelKeyDoc);
              StakeGenSubCashSub->addWidget(tListCacheKeyDoc);

              }

               if (tType == "Doc")
                 StakeGenSubCashSub->addWidget(lListViewCache.at(i));

               if (tType == "Cal")
                   StakeGenSubCashSub->addWidget(CalendarGenSubCash);

               if (tType == "Txt")
                  StakeGenSubCashSub->addWidget(lListViewCache.at(i));

               if (tType == "Num")
                   StakeGenSubCashSub->addWidget(tTextTemp);

               if (tType == "Blk")
                   StakeGenSubCashSub->addWidget(tTextTemp);

*/

            }


// Установка моделей в Info

             TableViewInfo->setModel(ModelProj);


// Скрытие всех полей Info
             for (int k = 0 ; k < tStorage->GetFieldCod().length(); k++)
             TableViewInfo->hideRow(k);


// Установка модели выбора Info
             SelecInfo  = TableViewInfo->selectionModel();



// Создание вкладок Gen и Установка моделей в Gen--------------------------------------------------------------------------


for(int i = 0; i < tStorage->GetDialogName().length(); i++)
    {
        TTableView  *TableViewGen =new TTableView(parent);
        TableViewGen->setModel(ModelData);
        tabsRd->addTab(TableViewGen, tStorage->GetDialogCodName().value(i));

        TableViewGen->setWordWrap(false);
        TableViewGen->setShowGrid(false);

// Скртие колонок
       for (int k = 0 ; k < tStorage->GetFieldName().length(); k++)
            {
           // qDebug()<<tStorage->GetDialogName().value(i)<<" "<<tStorage->GetFieldDialogName().value(k);

                if (tStorage->GetDialogName().value(i) == tStorage->GetFieldDialogName().value(k))
                    TableViewGen->setColumnWidth(k, tStorage->GetFieldWidth().value(k)); //ширина колонок
                else
                        TableViewGen->setColumnWidth(k, 0); //ширина колонок
            }

// Действие. Изменение выделения
                lTableViewGen << TableViewGen;
                connect(TableViewGen->selectionModel(), &QItemSelectionModel::selectionChanged,this, &DialGen::SlotCurrentChangedGen);

// Действие. Изменение панели СкролБара
                connect(TableViewGen->verticalScrollBar(), &QScrollBar::sliderReleased,this, &DialGen::ScrollBarValueChanged);

// Действие. Изменение прокрутки
                connect(TableViewGen, &TTableView::ScrollValueChanged,this, &DialGen::ScrollBarValueChangedUpDown);


// Установка модели выбора Gen
// Из первой вкладки берем модель выбора. В другие устанавливаем из первой вкладки
    if (i==0)
        SelecGen  =  TableViewGen->selectionModel();
    else
        TableViewGen->setSelectionModel(SelecGen);

// заполнение строк данными
    tStorage->LoadData(ModelData->rowCount(QModelIndex()));
    lTableViewGen[tabsRd->currentIndex()]->viewport()->update();

// Установка на первую запись
    tCurrentRowInfo = 0;
    tCurrentRowInfoPrev = 0;

// Переход на последнюю запись
      SlotKeyEnd();

}
//--------------------------------------------------------------------------------------------------------------------------------------


// Установка горячих клавиш

            QShortcut *keyCtrlDPgUp = new QShortcut(parent); // Инициализируем объект
                           keyCtrlDPgUp->setKey(Qt::Key_PageUp); // Устанавливаем сочетание клавиш
                    connect(keyCtrlDPgUp, &QShortcut::activated, this, &DialGen::SlotKeyPgUp);

            QShortcut *keyCtrlDPgDown = new QShortcut(parent); // Инициализируем объект
                           keyCtrlDPgDown->setKey(Qt::Key_PageDown); // Устанавливаем сочетание клавиш
                    connect(keyCtrlDPgDown, &QShortcut::activated, this, &DialGen::SlotKeyPgDown);


            QShortcut *keyCtrlDRight = new QShortcut(parent); // Инициализируем объект
                          keyCtrlDRight->setKey(Qt::SHIFT + Qt::Key_PageDown); // Устанавливаем сочетание клавиш
                    connect(keyCtrlDRight, &QShortcut::activated, this, &DialGen::SlotKeyMyRight);

            QShortcut *keyCtrlDLeft = new QShortcut(parent); // Инициализируем объект
                          keyCtrlDLeft->setKey(Qt::SHIFT + Qt::Key_PageUp); // Устанавливаем сочетание клавиш
                    connect(keyCtrlDLeft, &QShortcut::activated, this, &DialGen::SlotKeyMyLeft);


            QShortcut *keyEnter = new QShortcut(parent); // Инициализируем объект
                          keyEnter->setKey(Qt::Key_Return); // Устанавливаем сочетание клавиш
                    connect(keyEnter, &QShortcut::activated, this, &DialGen::SlotKeyReturn);


            QShortcut *keyEnterShift = new QShortcut(parent); // Инициализируем объект
                          keyEnterShift->setKey(Qt::SHIFT + Qt::Key_Return); // Устанавливаем сочетание клавиш
                    connect(keyEnterShift, &QShortcut::activated, this, &DialGen::SlotKeyShiftReturn);


            QShortcut *keyCtrlD = new QShortcut(parent); // Инициализируем объект
                           keyCtrlD->setKey(Qt::CTRL + Qt::Key_Return); // Устанавливаем сочетание клавиш
                     connect(keyCtrlD, &QShortcut::activated, this, &DialGen::SlotKeyNewDoc);


            QShortcut *keyEnd = new QShortcut(parent); // Инициализируем объект
                           keyEnd->setKey(Qt::Key_End); // Устанавливаем сочетание клавиш
                     connect(keyEnd, &QShortcut::activated, this, &DialGen::SlotKeyEnd);

//-----------------------------------------------------------------------------------------------------------




// Действие. Изменение вкладки
        connect(tabsRd,  &QTabWidget::currentChanged,this, &DialGen::SlotCurrentChangedTab);
        // connect(tabsRd,  &QTabWidget::tabBarClicked,this, &DialGen::SlotCurrentChangedTab);
// Действие. Изменение строки
        //  connect(TableViewGen->selectionModel(), &QItemSelectionModel::selectionChanged,this, &DialGen::SlotCurrentChangedGen);
        connect(TableViewInfo->selectionModel(), &QItemSelectionModel::selectionChanged,this, &DialGen::SlotCurrentChangedInfo);




// Действие над полем Text
for (int i = 0; i < tStorage->GetFieldCod().length(); i++)

    {
        connect(listTextEdit.at(i), &TTextEdit::sKRight, this, &DialGen::SlotKeyRight);
        connect(listTextEdit.at(i), &TTextEdit::sKLeft, this, &DialGen::SlotKeyLeft);

        connect(listTextEdit.at(i), &TTextEdit::sReturn, this, &DialGen::SlotKeyReturn);
        connect(listTextEdit.at(i), &TTextEdit::sShiftReturn, this, &DialGen::SlotKeyShiftReturn);

        connect(listTextEdit.at(i), &TTextEdit::sKUp, this, &DialGen::SlotKeyUP);
        connect(listTextEdit.at(i), &TTextEdit::sKDown, this, &DialGen::SlotKeyDown);

        connect(listTextEdit.at(i), &TTextEdit::textChanged, this, &DialGen::SlotChangedText);
        connect(listTextEdit.at(i), &TTextEdit::sKTab, this, &DialGen::SlotKeyTab);

        connect(listTextEdit.at(i), &TTextEdit::sKEnd, this, &DialGen::SlotKeyEnd);

   //  connect(listTextEdit.at(i), &TTextEdit::sAltReturn, this, &DialGen::mClearValinInfo);

    }
//-----------------------------------------------------------------------------------------------------------------



}

QSplitter* DialGen::GetIDSplitter()
{
 return SplitHor;
}

void DialGen::SlotCurrentChangedTab()
{

}

void DialGen::SlotCurrentChangedGen(const QItemSelection & selected)
{

    //Скрытие всех полей    
    for (int k = 0 ; k < tStorage->GetFieldCod().length(); k++)
      TableViewInfo->hideRow(k);

    QModelIndexList indexest = selected.indexes();
    tCurrentRowGen = indexest.value(0).row();

    //Выделение строки полностью

    QModelIndex  tGenIndexL = ModelData->index(tCurrentRowGen, 0, QModelIndex());
    QModelIndex  tGenIndexR = ModelData->index(tCurrentRowGen, tStorage->GetFieldCod().length()-1, QModelIndex());

    SelecGen->setCurrentIndex(tGenIndexL, QItemSelectionModel::Select);

    QItemSelection tSelGen(tGenIndexL,tGenIndexR);
    SelecGen->select(tSelGen,QItemSelectionModel::Select);

    //Установка значения в таблицу инфо

    for (int k = 0 ; k < tStorage->GetFieldCod().length(); k++)
     {

        QModelIndex ttt = ModelData->index(indexest.value(0).row(),k, QModelIndex());
        QString ttText = ModelData->data(ttt, Qt::DisplayRole).toString();




//-------если не пусто, то показываем
        if (ttText != "")

          {
                TableViewInfo->showRow(k);
                tStorage->SetFieldInfo(k,ttText);

//-------установка значений в текстовое поле

               listTextEdit.at(k)->setText(ttText);
               listTextEdit.at(k)->setFocus();
               listTextEdit.at(k)->selectAll();


          }

     }


    TableViewInfo->resizeColumnsToContents();
    TableViewInfo->reset();

//Устанавливает выделение в Инфо
    QModelIndex tMasLeftS = ModelProj->index(tCurrentRowInfo, 0, QModelIndex());
    QModelIndex tMasRightS = ModelProj->index(tCurrentRowInfo, 1, QModelIndex());
    QItemSelection tSelInfoS(tMasLeftS, tMasRightS);
    SelecInfo->select(tSelInfoS, QItemSelectionModel::Select);




}

void DialGen::SlotCurrentChangedInfo(const QItemSelection & selected)
{


    QModelIndexList indexest = selected.indexes();

    tCurrentRowInfo = indexest.value(0).row();
    QModelIndex  tGenIndexL = ModelProj->index(tCurrentRowInfo, 0, QModelIndex());

    SelecInfo->setCurrentIndex(tGenIndexL, QItemSelectionModel::Select);

   StakeForText->setCurrentIndex(tCurrentRowInfo);
   StakeGenSubCache->setCurrentIndex(tCurrentRowInfo);
   StakeGenSub->update();

   //StakeGenSubCash->setCurrentWidget(tCurrentRowInfo);
    //StakeGenSubCash-> update();


       if(tCurrentRowInfo >= 0)
    {
   listTextEdit.at(tCurrentRowInfo)->setFocus();
   listTextEdit.at(tCurrentRowInfo)->selectAll();
    }

}


void DialGen::SlotKeyPgUp()
{

    //подгрузка данных
        QScrollBar*  tScrolBar = lTableViewGen[tabsRd->currentIndex()]->verticalScrollBar();
        QModelIndex  tSetIndex = ModelData->index(tScrolBar->value(), 0, QModelIndex());
        QString tDataIndex = lTableViewGen[tabsRd->currentIndex()]->model()->data(tSetIndex).toString();



        if(tStorage->Get_PageSize()/2 - tScrolBar->value() <= 0)
        {

            if (tDataIndex == "")
            {

                tStorage->LoadData(tScrolBar->value());

                lTableViewGen[tabsRd->currentIndex()]->viewport()->update();

            }



        }
            else
        {



            QModelIndex  tSetIndexFirst =   ModelData->index(0, 0, QModelIndex());
            QString tDataIndexFirst = lTableViewGen[tabsRd->currentIndex()]->model()->data(tSetIndexFirst).toString();



             if (tDataIndexFirst == "")
             {

                 tStorage->LoadData(tScrolBar->value());

                 lTableViewGen[tabsRd->currentIndex()]->viewport()->update();

             }

        }


    //--------------------------------------------------

    tCurrentRowGen = SelecGen->currentIndex().row();

    QModelIndex  tMasLeftD = ModelData->index(tCurrentRowGen, 0, QModelIndex());
    //QModelIndex  tMasRightD = ModelData->index(tCurrentRowGen, ModelProj->GetFileds().length()-1, QModelIndex());
    QModelIndex  tMasRightD = ModelData->index(tCurrentRowGen, tStorage->GetFieldCod().length()-1, QModelIndex());

    QItemSelection tSelGenD(tMasLeftD, tMasRightD);

 while (tCurrentRowGen - 1 >= 0)
    {
        tCurrentRowGen = tCurrentRowGen - 1;
        if ( !lTableViewGen[tabsRd->currentIndex()]->isRowHidden(tCurrentRowGen))

        {
            QModelIndex tMasLeftS = ModelData->index(tCurrentRowGen, 0, QModelIndex());
            QModelIndex tMasRightS = ModelData->index(tCurrentRowGen, tStorage->GetFieldCod().length()-1, QModelIndex());


            QItemSelection tSelGenS(tMasLeftS, tMasRightS);

            SelecGen->select(tSelGenD, QItemSelectionModel::Deselect);

            emit  SelecGen->selectionChanged(tSelGenS, tSelGenD); //эммитирует сигнал для изменения select
            break;

        }

    }


}


void DialGen::SlotKeyPgDown()
{

//подгрузка данных
    QScrollBar*  tScrolBar = lTableViewGen[tabsRd->currentIndex()]->verticalScrollBar();
    QModelIndex  tSetIndex = ModelData->index(tScrolBar->value() + tStorage->Get_PageSize()/2, 0, QModelIndex());
    QString tDataIndex = lTableViewGen[tabsRd->currentIndex()]->model()->data(tSetIndex).toString();

   if  (((ModelData->rowCount(QModelIndex())-tStorage->Get_PageSize()/2) - tScrolBar->value()) > 0)

   {
    if (tDataIndex == "")
    {


        tStorage->LoadData(tScrolBar->value()+tStorage->Get_PageSize()/2);
        lTableViewGen[tabsRd->currentIndex()]->viewport()->update();

    }
   }

   else
    {
      QModelIndex  tSetIndexLast =   ModelData->index(ModelData->rowCount(QModelIndex())-1, 0, QModelIndex());

      QString tDataIndexLast = lTableViewGen[tabsRd->currentIndex()]->model()->data(tSetIndexLast).toString();

      if (tDataIndexLast == "")
       {


          tStorage->LoadData(tScrolBar->value());
          lTableViewGen[tabsRd->currentIndex()]->viewport()->update();

       }

   }
//--------------------------------------------------
    tCurrentRowGen = SelecGen->currentIndex().row();

    QModelIndex  tMasLeftD = ModelData->index(tCurrentRowGen, 0, QModelIndex());
    QModelIndex  tMasRightD = ModelData->index(tCurrentRowGen, tStorage->GetFieldCod().length()-1, QModelIndex());
    QItemSelection tSelGenD(tMasLeftD, tMasRightD);

 while (tCurrentRowGen + 1 < ModelData->rowCount(QModelIndex()))
    {
        tCurrentRowGen = tCurrentRowGen + 1;
        if ( !lTableViewGen[tabsRd->currentIndex()]->isRowHidden(tCurrentRowGen))

        {
            QModelIndex tMasLeftS = ModelData->index(tCurrentRowGen, 0, QModelIndex());
            QModelIndex tMasRightS = ModelData->index(tCurrentRowGen, tStorage->GetFieldCod().length()-1, QModelIndex());
            QItemSelection tSelGenS(tMasLeftS, tMasRightS);

            //SelecGen->select(tSelGenS, QItemSelectionModel::Select);
            SelecGen->select(tSelGenD, QItemSelectionModel::Deselect);

            emit  SelecGen->selectionChanged(tSelGenS, tSelGenD); //эммитирует сигнал для изменения select
            break;

        }

    }


}

void DialGen::SlotKeyMyRight()
{
    tabsRd->setCurrentIndex(tabsRd->currentIndex()+1);
}

void DialGen::SlotKeyMyLeft()
{
     tabsRd->setCurrentIndex(tabsRd->currentIndex()-1);
}

void DialGen::SlotKeyReturn()
{



    if (flagNewView == 1 ) //режим нового документа
    {

        TextSearch.clear();
        countSearch = 0;
        //bool ok2;

        QModelIndex  tMasLeftD = ModelProj->index(tCurrentRowInfo, 0, QModelIndex());
        QModelIndex  tMasRightD = ModelProj->index(tCurrentRowInfo, 1, QModelIndex());
        QItemSelection tSelInfoD(tMasLeftD, tMasRightD);


        //Установка значения в таблицу инфо

        QString ttText = listTextEdit.at(tCurrentRowInfoPrev)->toPlainText();
        QModelIndex MMIndex = TableViewInfo->model()->index(tCurrentRowInfoPrev,1);
        TableViewInfo->model()->setData(MMIndex,ttText, Qt::EditRole);


        //Если новая запись, то в кэш

           // NewRowsInCash(listTextEdit.at(tCurrentRowInfo)->toPlainText().replace(",", "."));

        if(tCurrentRowInfo == 0)

        {
            //Зависимость документа от уровня

            QString ttText = listTextEdit.at(tCurrentRowInfo)->toPlainText();
            QStringList lLev = tStorage->GetDocumLevel();

 //           qDebug()<<"lLev "<<lLev;

            //скрываем все строки
/*

            for (int i=0; i<lLev.length();i++)

            {

              lListViewCache.at(StakeGenSubCache->currentIndex() + 1)->setRowHidden(i,1);

            }
*/
            //--------------------


           QStringList lttText = ttText.split(".");

/*

           if (ttText != "")
           {

               //qDebug()<<"lttText "<< lttText.length();
               if (lttText.length() == 2 )

                  lListViewCache.value(1)->setModel(ModelDoc3);

               else if(lttText.length() == 1)

                   lListViewCache.value(1)->setModel(ModelDoc2);
            }
           else
           {

                    lListViewCache.value(1)->setModel(ModelDoc1);

           }

*/



        }


        if (tCurrentRowInfo == 1)

        {

             lfShow = tStorage->GetFieldDocumForShow(listTextEdit.at(tCurrentRowInfo)->toPlainText());



             for(int k=2; k<lfShow.length(); k++)
              {
                 if (lfShow.value(k) == 0) // если 0, то скрываем 1 показываем
                    TableViewInfo->setRowHidden(k,true);
                 else
                    TableViewInfo->setRowHidden(k, false);
              }


        }


       while (tCurrentRowInfo + 1 < tStorage->GetFieldCod().length())
                    {

                        tCurrentRowInfo = tCurrentRowInfo + 1;
                        if ( !TableViewInfo->isRowHidden(tCurrentRowInfo))

                        {

                            // Доделать Вывод типа поля

                             // qDebug()<<tCurrentRowInfo  <<" " << ModelProj->GetField_Type(tCurrentRowInfo);

                            //----------------------------------


                                tCurrentRowInfoPrev = tCurrentRowInfo;
                                QModelIndex tMasLeftS = ModelProj->index(tCurrentRowInfo, 0, QModelIndex());
                                QModelIndex tMasRightS = ModelProj->index(tCurrentRowInfo, 1, QModelIndex());
                                QItemSelection tSelInfoS(tMasLeftS, tMasRightS);

                                SelecInfo->select(tSelInfoS, QItemSelectionModel::Select);
                                SelecInfo->select(tSelInfoD, QItemSelectionModel::Deselect);

                               emit  SelecInfo->selectionChanged(tSelInfoS, tSelInfoD); //эммитирует сигнал для изменения select
                               break;
                        }

                    }

   }


//Режим просмотра
 else

    {


        QModelIndex  tMasLeftD = ModelProj->index(tCurrentRowInfo, 0, QModelIndex());
        QModelIndex  tMasRightD = ModelProj->index(tCurrentRowInfo, 1, QModelIndex());
        QItemSelection tSelInfoD(tMasLeftD, tMasRightD);


     while (tCurrentRowInfo + 1 < tStorage->GetFieldCod().length())
        {
            tCurrentRowInfo = tCurrentRowInfo + 1;
            if ( !TableViewInfo->isRowHidden(tCurrentRowInfo))

            {

                QModelIndex tMasLeftS = ModelProj->index(tCurrentRowInfo, 0, QModelIndex());
                QModelIndex tMasRightS = ModelProj->index(tCurrentRowInfo, 1, QModelIndex());
                QItemSelection tSelInfoS(tMasLeftS, tMasRightS);

                SelecInfo->select(tSelInfoS, QItemSelectionModel::Select);
                SelecInfo->select(tSelInfoD, QItemSelectionModel::Deselect);


                emit  SelecInfo->selectionChanged(tSelInfoS, tSelInfoD); //эммитирует сигнал для изменения select
                break;


            }

        }


    }

}

void DialGen::SlotKeyShiftReturn()
{

    TextSearch.clear();
    countSearch = 0;

    QModelIndex  tMasLeftD = ModelProj->index(tCurrentRowInfo, 0, QModelIndex());
    QModelIndex  tMasRightD = ModelProj->index(tCurrentRowInfo, 1, QModelIndex());
    QItemSelection tSelInfoD(tMasLeftD, tMasRightD);


 while (tCurrentRowInfo - 1 >= 0)
    {
        tCurrentRowInfo = tCurrentRowInfo - 1;
        if ( !TableViewInfo->isRowHidden(tCurrentRowInfo))

        {

            QModelIndex tMasLeftS = ModelProj->index(tCurrentRowInfo, 0, QModelIndex());
            QModelIndex tMasRightS = ModelProj->index(tCurrentRowInfo, 1, QModelIndex());
            QItemSelection tSelInfoS(tMasLeftS, tMasRightS);

            SelecInfo->select(tSelInfoS, QItemSelectionModel::Select);
            SelecInfo->select(tSelInfoD, QItemSelectionModel::Deselect);


            emit  SelecInfo->selectionChanged(tSelInfoS, tSelInfoD); //эммитирует сигнал для изменения select
            break;


        }

    }

}

void DialGen::SlotKeyNewDoc()
{

    if (flagNewView == 0 )

    {

        //qDebug()<<"NewDIALOG";
        //-------Скрытие строк


        for(int k=2;k<TableViewInfo->model()->rowCount(QModelIndex());k++)
        {
           TableViewInfo->setRowHidden(k, true);
        }


            StakeGenSub->setCurrentIndex(1);

        //Переход на первую запись в инфо


            QModelIndex  tMasLeftD = ModelProj->index(tCurrentRowInfo, 0, QModelIndex());
            QModelIndex  tMasRightD = ModelProj->index(tCurrentRowInfo, 1, QModelIndex());
            QItemSelection tSelInfoD(tMasLeftD, tMasRightD);

             tCurrentRowInfo = 0;

            QModelIndex tMasLeftS = ModelProj->index(tCurrentRowInfo, 0, QModelIndex());
            QModelIndex tMasRightS = ModelProj->index(tCurrentRowInfo, 1, QModelIndex());
            QItemSelection tSelInfoS(tMasLeftS, tMasRightS);

            SelecInfo->select(tSelInfoS, QItemSelectionModel::Select);
            SelecInfo->select(tSelInfoD, QItemSelectionModel::Deselect);

            emit  SelecInfo->selectionChanged(tSelInfoS, tSelInfoD); //эммитирует сигнал для изменения select

        //-----------------------------





        flagNewView = 1;

    }

    else

    {

        //if (flagChangeSlot == true)
            NewRowsSave();


       StakeGenSub->setCurrentIndex(0);
       flagNewView = 0;

    }



}

void DialGen::SlotKeyRight()
{


    QTextCursor cursor = listTextEdit.at(tCurrentRowInfo)->textCursor();

    cursor.clearSelection();


    listTextEdit.at(tCurrentRowInfo)->setTextCursor(cursor);

    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 1);
    listTextEdit.at(tCurrentRowInfo)->setTextCursor(cursor);


}

void DialGen::SlotKeyLeft()
{


    QTextCursor cursor = listTextEdit.at(tCurrentRowInfo)->textCursor();

    cursor.clearSelection();


    listTextEdit.at(tCurrentRowInfo)->setTextCursor(cursor);

    cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
    listTextEdit.at(tCurrentRowInfo)->setTextCursor(cursor);


}

void DialGen::SlotKeyUP()
{
    
if (flagNewView == 1 )

{

    flagChangeSlot = true;
    QModelIndex  tMIndexCurrent =  lListViewCache.at(tCurrentRowInfo)->selectionModel()->currentIndex();

    int ddd = tMIndexCurrent.row();
    if (ddd < 0)
    {

        QModelIndex  tMIndex = lListViewCache.at(tCurrentRowInfo)->model()->index(0,0, QModelIndex());

        lListViewCache.at(tCurrentRowInfo)->selectionModel()->clearSelection();
        lListViewCache.at(tCurrentRowInfo)->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);

        listTextEdit.at(tCurrentRowInfo)->setText(lListViewCache.at(tCurrentRowInfo)->model()->data(tMIndex, Qt::DisplayRole).toString());
        listTextEdit.at(tCurrentRowInfo)->selectAll();

        CurrentData = lListViewCache.at(tCurrentRowInfo)->model()->data(tMIndex, Qt::DisplayRole).toString();


    }

    else
    {

        QModelIndex  tMIndex = lListViewCache.at(tCurrentRowInfo)->model()->index(ddd - 1, 0, QModelIndex());


        lListViewCache.at(tCurrentRowInfo)->selectionModel()->clearSelection();
        lListViewCache.at(tCurrentRowInfo)->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);

        listTextEdit.at(tCurrentRowInfo)->setText(lListViewCache.at(tCurrentRowInfo)->model()->data(tMIndex, Qt::DisplayRole).toString());
        listTextEdit.at(tCurrentRowInfo)->selectAll();

        CurrentData = lListViewCache.at(tCurrentRowInfo)->model()->data(tMIndex, Qt::DisplayRole).toString();

//----------------------------------------------------------------------------------------------------------------------

    }
    flagChangeSlot = false;

}


}

void DialGen::SlotKeyDown()
{

if (flagNewView == 1 )

{

    flagChangeSlot = true;
    QModelIndex  tMIndexCurrent =  lListViewCache.at(tCurrentRowInfo)->selectionModel()->currentIndex();

    int ddd = tMIndexCurrent.row();



    if (ddd < 0)
    {

        QModelIndex  tMIndex = lListViewCache.at(tCurrentRowInfo)->model()->index(0,0, QModelIndex());

        lListViewCache.at(tCurrentRowInfo)->selectionModel()->clearSelection();
        lListViewCache.at(tCurrentRowInfo)->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);

        listTextEdit.at(tCurrentRowInfo)->setText(lListViewCache.at(tCurrentRowInfo)->model()->data(tMIndex, Qt::DisplayRole).toString());
        listTextEdit.at(tCurrentRowInfo)->selectAll();

        CurrentData = lListViewCache.at(tCurrentRowInfo)->model()->data(tMIndex, Qt::DisplayRole).toString();

    }

    else
    {

       QModelIndex  tMIndex = lListViewCache.at(tCurrentRowInfo)->model()->index(ddd + 1,0, QModelIndex());

       lListViewCache.at(tCurrentRowInfo)->selectionModel()->clearSelection();
       lListViewCache.at(tCurrentRowInfo)->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);

       listTextEdit.at(tCurrentRowInfo)->setText(lListViewCache.at(tCurrentRowInfo)->model()->data(tMIndex, Qt::DisplayRole).toString());
       listTextEdit.at(tCurrentRowInfo)->selectAll();
       CurrentData = lListViewCache.at(tCurrentRowInfo)->model()->data(tMIndex, Qt::DisplayRole).toString();



 //-------------------------------------------------------------------------------

    }
     flagChangeSlot = false;

}



}

void DialGen::SlotKeyTab()
{

    if (flagNewView == 1 )
    {

        if(TextSearch != NULL)
        {

            QModelIndexList lSearch; //массив для найденых строк
            lSearch = lListViewCache.at(tCurrentRowInfo)->model()->match(lListViewCache.at(tCurrentRowInfo)->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearch, -1, Qt::MatchContains);


            QModelIndex  tMIndexS;
            if (lSearch.length()>0)
                {


                    tMIndexS = lSearch.at(countSearch);
                    lListViewCache.at(tCurrentRowInfo)->selectionModel()->clearSelection();
                    lListViewCache.at(tCurrentRowInfo)->selectionModel()->setCurrentIndex(tMIndexS, QItemSelectionModel::Select);
                    CurrentData = lListViewCache.at(tCurrentRowInfo)->model()->data(tMIndexS, Qt::DisplayRole).toString();

                    if(countSearch == lSearch.length() - 1)
                       countSearch = 0;
                    else
                       countSearch = countSearch + 1;


                }




            //------------------------Выделение найденой строки
            QModelIndex  tMIndexCurrent =  lListViewCache.at(tCurrentRowInfo)->selectionModel()->currentIndex();



           int dddd = tMIndexCurrent.row();





           if (dddd >= 0)
           {



            QModelIndex  tMIndex = lListViewCache.at(tCurrentRowInfo)->model()->index(dddd, 0, QModelIndex());


            lListViewCache.at(tCurrentRowInfo)->selectionModel()->clearSelection();
            lListViewCache.at(tCurrentRowInfo)->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);

           listTextEdit.at(tCurrentRowInfo)->setText(lListViewCache.at(tCurrentRowInfo)->model()->data(tMIndex, Qt::DisplayRole).toString());
           listTextEdit.at(tCurrentRowInfo)->selectAll();



           }




        }
        else
        {


            TextSearch = listTextEdit.at(tCurrentRowInfo)->toPlainText().replace(",", ".") ;
            if(TextSearch != NULL) //Если поле для ввода не пустое

            {

                QModelIndexList lSearch; //массив для найденых строк
                lSearch = lListViewCache.at(tCurrentRowInfo)->model()->match(lListViewCache.at(tCurrentRowInfo)->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearch, -1, Qt::MatchContains);

                QModelIndex  tMIndexS;
                if (lSearch.length()>0)
                {
                    tMIndexS = lSearch.at(countSearch);

                    lListViewCache.at(tCurrentRowInfo)->selectionModel()->clearSelection();
                    lListViewCache.at(tCurrentRowInfo)->selectionModel()->setCurrentIndex(tMIndexS, QItemSelectionModel::Select);

                    CurrentData = lListViewCache.at(tCurrentRowInfo)->model()->data(tMIndexS, Qt::DisplayRole).toString();

                    if(countSearch == lSearch.length() - 1)
                     countSearch = 0;
                    else
                    countSearch = countSearch + 1;
                }




                //------------------------Выделение найденой строки
                QModelIndex  tMIndexCurrent =  lListViewCache.at(tCurrentRowInfo)->selectionModel()->currentIndex();

               int dddd = tMIndexCurrent.row();
               if (dddd >= 0)
               {
                QModelIndex  tMIndex = lListViewCache.at(tCurrentRowInfo)->model()->index(dddd, 0, QModelIndex());

                lListViewCache.at(tCurrentRowInfo)->selectionModel()->clearSelection();
                lListViewCache.at(tCurrentRowInfo)->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);

                listTextEdit.at(tCurrentRowInfo)->setText(lListViewCache.at(tCurrentRowInfo)->model()->data(tMIndex, Qt::DisplayRole).toString());
                listTextEdit.at(tCurrentRowInfo)->selectAll();

               }



            }



        }


    }

}

void DialGen::SlotChangedText()
{

    if (flagNewView == 1 )
    {

        if (flagChangeSlot)
             return;



     QString TextSearchLocal = listTextEdit.at(tCurrentRowInfo)->toPlainText().replace(",", ".") ;

     QModelIndexList lSearch; //массив для найденых строк
     lSearch = lListViewCache.at(tCurrentRowInfo)->model()->match(lListViewCache.at(tCurrentRowInfo)->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearchLocal, 1, Qt::MatchStartsWith);


     QModelIndex  tMIndex;
     if (lSearch.length()>0)
     {
       tMIndex = lSearch.at(0);

       lListViewCache.at(tCurrentRowInfo)->selectionModel()->clearSelection();
       lListViewCache.at(tCurrentRowInfo)->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);

            CurrentData = lListViewCache.at(tCurrentRowInfo)->model()->data(tMIndex, Qt::DisplayRole).toString();

            bForSeach = 1;


        }


        parChangeTextBit.setBit(tCurrentRowInfo);



    }



}

void DialGen::mClearValinInfo()
{
/*
  for (int i = 0; i < ModelProj->rowCount(QModelIndex()); i++)
  {
    if (parChangeTextBit.at(i) == true)
        lModelCach.at(i)->Save(listTextEdit.at(i)->toPlainText());

        QModelIndex MMIndex = TableViewInfo->model()->index(i,1);
        ModelProj->setData(MMIndex,"", Qt::EditRole);


  }

  //Установка на первую запись
  tCurrentRowInfo = 0;
  QModelIndex  tMasLeft = ModelProj->index(tCurrentRowInfo, 0, QModelIndex());
  SelecInfo->setCurrentIndex(tMasLeft, QItemSelectionModel::Select);


  //---Обнуляем параметры изменения
  for (int i = 0; i < ModelProj->rowCount(QModelIndex()); i++)
   parChangeTextBit.clearBit(i);
  //----
*/
}

void DialGen::NewRowsInCash(QString TextSearch)
{



    QModelIndexList lSearch; //массив для найденых строк
    lSearch = lListViewCache.at(tCurrentRowInfo)->model()->match(lListViewCache.at(tCurrentRowInfo)->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearch, 1, Qt::MatchStartsWith);

    if (lSearch.length()==0)
    {


        lListViewCache.at(tCurrentRowInfo)->model()->insertRow(0, QModelIndex());
        int tCountRow = lListViewCache.at(tCurrentRowInfo)->model()->rowCount(QModelIndex());
        int tLastRow = tCountRow - 1;

        QModelIndex MMIndexNull = lListViewCache.at(tCurrentRowInfo)->model()->index(tLastRow,0);
        lListViewCache.at(tCurrentRowInfo)->model()->setData(MMIndexNull, TextSearch, Qt::EditRole);

        //Обновление
        lListViewCache.at(tCurrentRowInfo)->update(MMIndexNull);


    }

}

void DialGen::SlotKeyEnd()
{

   tCurrentRowGen = SelecGen->currentIndex().row();
   int tCurrentRowGenEnd = ModelData->rowCount(QModelIndex()) - 1;
   int tCurrentColGenEnd = tStorage->GetFieldCod().length() - 1;

   QModelIndex tMasLeftS = ModelData->index(tCurrentRowGenEnd, 0, QModelIndex());
   QModelIndex tMasRightS = ModelData->index(tCurrentRowGenEnd, tCurrentColGenEnd, QModelIndex());
   QItemSelection tSelGenS(tMasLeftS, tMasRightS);

   QModelIndex  tMasLeftD = ModelData->index(tCurrentRowGen, 0, QModelIndex());
   QModelIndex  tMasRightD = ModelData->index(tCurrentRowGen, tCurrentColGenEnd, QModelIndex());
   QItemSelection tSelGenD(tMasLeftD, tMasRightD);

    SelecGen->select(tSelGenD, QItemSelectionModel::Deselect);

    emit  SelecGen->selectionChanged(tSelGenS, tSelGenD); //эммитирует сигнал для изменения select

}

void DialGen::NewRowsSave()
{
/*
 qDebug()<<"NewRowsSave";

     QString tTextForWrite;

     QList<QString> mTextForWritre;

     for(int i=0; i<listTextEdit.length(); i++)
     {
         tTextForWrite.append(listTextEdit.at(i)->toPlainText());
         mTextForWritre<<listTextEdit.at(i)->toPlainText();

         if (i==0)
          tTextForWrite.append("-");

         if (i<listTextEdit.length()-1)
          tTextForWrite.append("|");
         else
            tTextForWrite.append("\r\n");
     }

     ModelData->Save(tTextForWrite);
*/
}

void DialGen::ScrollBarValueChanged()
{

    QScrollBar*  tScrolBar = lTableViewGen[tabsRd->currentIndex()]->verticalScrollBar();

    ttCurrentRowGenPrev = tScrolBar->value();
    tStorage->LoadData(ttCurrentRowGenPrev);
    lTableViewGen[tabsRd->currentIndex()]->viewport()->update();

}

void DialGen::ScrollBarValueChangedUpDown()
{
    QScrollBar*  tScrolBar = lTableViewGen[tabsRd->currentIndex()]->verticalScrollBar();

   if (ttCurrentRowGenPrev < tScrolBar->value())
       SlotKeyPgDown();
   else
        SlotKeyPgUp();

ttCurrentRowGenPrev = tScrolBar->value();

}

