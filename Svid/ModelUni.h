#ifndef MODELUNI_H
#define MODELUNI_H

#include "StorProject.h"
//#include "StorCache.h"
//#include "StorData.h"


enum typemodel { PROJECT, CACHE, DOCUM, MAXNUM, DATA, DOCKEY, DOCPROJECT };
class ModelUni: public QAbstractTableModel
{

//Q_OBJECT

public:
    ModelUni(typemodel TypeModel, StorProject *StPr);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
//    bool insertRows(const QModelIndex &parent = QModelIndex());
   // bool setData(const QModelIndex &index, const QVariant &value, int role);

   // void LoadDataToModel(int i);

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;


    // void SetDocKey (QString ttDocKey);

   // void setRowsOffset(int i);
    //void setRowsPage(int i);


  //  int MyColumnCount() const;
  //  int SearchRow(QString TuxtForFind);

   // QList<int> GetFieldForShowDocum(QString NameDocum) const;
   // QList<int> GetFieldForShowDialog(QString NameDialog) const;
   // QList<int> GetFieldForHideDialog(QString NameDialog) const;


   // QList<QStringList> Get_FieldDialog();


   // QStringList GetDialogs() const;
   // QStringList GetFileds() const;
   // QStringList GetDocumLevel() const;

//Перенести Stor
    //bool Save(QString DataForSave);

  // bool canFetchMore(const QModelIndex &parent) const;
  // void fetchMore(const QModelIndex &parent);

   // int GetCounRowPlus() const;

 //   int GetPageSize() const;

    //int GetField_Width(int i) const;
   // QString GetField_Type(int i) const;


   // StorProject StorPro;
//static StorProject *StorProj;



private:




StorProject *StorProj;


    //StorCache StCch;
   // StorData StDat;


    QStringList d1;
    QStringList d2;

    QList<QStringList> lPoleInfo;

   // int tCounRowPlus; // количество элементов, добавленные в модель

    int tRowsOffset; // значение для смещение строк;

    int tRowsPageMin; // значение миним строки страницы;
    int tRowsPageBase; // значение базовой строки страницы;
    int tRowsPageMax; // значение максимал строки страницы;

    int tPrevI; //Предыдущее значение строки

    int tPageSize; //размер страницы

    typemodel TypeModelL;





signals:
  //  void numberPopulated(int number); //Разобраться

};

#endif // MODELUNI_H
