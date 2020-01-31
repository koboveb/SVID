#include "StorProject.h"

StorProject::StorProject(const QString &tPath)
{

//-----------------Получение путей
    int tDirCount = tPath.count("/");
    QString tpath = tPath.section("/",0, tDirCount-1);

   #ifdef  Q_OS_WIN
   path =QString("%1").arg("C://Путь к проекту//"); // доработать
   #endif

   #ifdef Q_OS_UNIX
   path =QString::fromLocal8Bit("%1/").arg(tpath);
   #endif


//-----------------Установка значений

    tPageSize = 100;

    v_file_project = new  QFile(QString::fromLocal8Bit("%1Svid.ini").arg(path));
    v_file_project->open(QIODevice::ReadOnly|QIODevice::Text);
bool okk;
//--Загрузка полей
    while (!v_file_project->atEnd())
    {

        QString t1 = v_file_project->readLine();
        QStringList ltField = t1.replace("\n","").split("|");

        l_vv_FieldCod.append(ltField.value(0));
        l_vv_FieldType.append(ltField.value(1));
        l_vv_FieldName.append(ltField.value(2));

        QString tWidth = ltField.value(3);
        l_vv_FieldWidth.append(tWidth.toInt(&okk,10));

        l_vv_FieldDialogCod.append(ltField.value(4)); // Код диалога
        l_vv_FieldDialogName.append(ltField.value(5));// Имя диалога
        l_vv_FieldPath.append(ltField.value(6));      // Путь кэша и документов

   }

//--Список диалогов

QString tCodName = QString::fromLocal8Bit("%1.%2").arg(l_vv_FieldDialogCod.value(0)) .arg(l_vv_FieldDialogName.value(0));
l_vv_DialogName.append(l_vv_FieldDialogName.value(0));
l_vv_DialogCodName.append(tCodName);

for(int i = 1; i < l_vv_FieldDialogCod.length(); i++)
{

    if (l_vv_FieldDialogCod.value(i-1) != l_vv_FieldDialogCod.value(i))
    {
        tCodName = QString::fromLocal8Bit("%1.%2").arg(l_vv_FieldDialogCod.value(i)) .arg(l_vv_FieldDialogName.value(i));

        l_vv_DialogCodName.append(tCodName);
        l_vv_DialogName.append(l_vv_FieldDialogName.value(i));

    }


}

//----Загрузка в панель Info

for (int i=0; i<l_vv_FieldName.length();i++)
   {
       QStringList l_Temp;
       l_Temp.append(l_vv_FieldName.value(i));
       l_Temp.append("");
       l_vv_FielInfo.append(l_Temp);
   }

//--
LoadDocum();
LoadDataCount();
LoadDataCachCount();
LoadDataCach();

}


StorProject::~StorProject()
{
}

//-----------------Загрузка документов

void StorProject::LoadDocum()
{


//------Открытие файла Документов
    QFile* f_Doc;
    f_Doc = new  QFile(QString::fromLocal8Bit("%1").arg(l_vv_FieldPath.value(1)));
    f_Doc->open(QIODevice::ReadOnly|QIODevice::Text);

//------Парсинг Документов


 while (!f_Doc->atEnd())
    {

        QString t1 = f_Doc->readLine();
        QStringList l_Field = t1.replace("\n","").split("|");


        for (int i = 0; i< l_Field.length(); i++)

        {
            if (i == 0)
              l_vv_DocName.append(l_Field.value(i));

            if (i == 1)
               l_vv_DocLevel.append(l_Field.value(i));

            if (i == 2)
            {
                QString tv_CodDial = l_Field.value(i);
                QStringList lt_vv_CodDialog = tv_CodDial.split(".");
                l_vv_DocDialogCod.append(lt_vv_CodDialog); // Загрузка кодов диаогов в результирующий список

            }

        }


    }

}

//-----------------Загрузка данных


void StorProject::LoadData(int CurrentRow)
{

//------Открытие файла Данных
  QFile* f_Doc;
    f_Doc = new  QFile(QString::fromLocal8Bit("%1").arg(l_vv_FieldPath.value(0)));
    f_Doc->open(QIODevice::ReadOnly|QIODevice::Text);

        l_vv_FieldData.clear(); // очищаем список данных
        l_MinMax.clear(); // очищаем список интервала

        int tcount = 0;


        if ((CurrentRow - tPageSize/2)<0 )
        l_MinMax.append(0);
        else
        l_MinMax.append(CurrentRow - tPageSize/2);


        l_MinMax.append(CurrentRow + tPageSize/2);

        while (tcount<=l_MinMax.value(1) && !f_Doc->atEnd())
            {

            QString t1 = f_Doc->readLine();

                if (tcount>=l_MinMax.value(0))
                {
                  QStringList row = t1.replace("\n","").split("|");
                  l_vv_FieldData.append(row);
                }

                 tcount = tcount + 1;
             }
     f_Doc->close();

}


void StorProject::LoadDataCach()
{
    l_vv_Cache.clear();
//------Открытие файла кэша
    for (int i=0; i<l_vv_FieldPath.length(); i++)

    {
        if (l_vv_FieldPath.value(i) != "" && i>1)
               {
                    QFile* f_Doc;
                    f_Doc = new  QFile(QString::fromLocal8Bit("%1").arg(l_vv_FieldPath.value(i)));
                    f_Doc->open(QIODevice::ReadOnly|QIODevice::Text);

                    QStringList lT;

                        while (!f_Doc->atEnd())

                            {
                                QString t1 = f_Doc->readLine();
                                QString row = t1.replace("\n","");
                                lT.append(row);

                            }


                               l_vv_Cache.append(lT);

              f_Doc->close();


            }
        else
        {
            QStringList lT;
            lT.append("");

           l_vv_Cache.append(lT);
        }

       // qDebug()<<"l_vv_Cache "<<l_vv_Cache.at(i).length();
        //qDebug()<<"l_vv_Cache "<<l_vv_Cache;


    }

//qDebug()<<"l_vv_Cache "<<l_vv_Cache;

}



void StorProject::LoadDataCount()
{

//------Открытие файла Данных
    QFile* f_Doc;
     f_Doc = new  QFile(QString::fromLocal8Bit("%1").arg(l_vv_FieldPath.value(0)));
     f_Doc->open(QIODevice::ReadOnly|QIODevice::Text);


     DataCount = 0;

      while (!f_Doc->atEnd())

      {

       DataCount = DataCount + 1 ;
       f_Doc->readLine();

      }

       f_Doc->close();

}


void StorProject::LoadDataCachCount()
{

//------Открытие файла Кэша


 for (int i = 0; i<l_vv_FieldPath.length();i++)
 {

     if (l_vv_FieldPath.value(i) != "" && i>1)
    {
        QFile* f_Cach;
        f_Cach = new  QFile(QString::fromLocal8Bit("%1").arg(l_vv_FieldPath.value(i)));
        f_Cach->open(QIODevice::ReadOnly|QIODevice::Text);
            int DataCachCount = 0;

      while (!f_Cach->atEnd())

        {
            DataCachCount = DataCachCount + 1 ;
            f_Cach->readLine();

        }

        lDataCachCount << DataCachCount ;

     f_Cach->close();
    }
     else
        lDataCachCount << 0;
 }

}


//--выдача Кодов полей
const QStringList &StorProject::GetFieldCod() const
{
    return l_vv_FieldCod;
}

//--выдача Типов полей
const QStringList &StorProject::GetFieldType() const
{
    return l_vv_FieldType;
}

//--выдача Имен полей
const QStringList &StorProject::GetFieldName() const
{
    return l_vv_FieldName;
}

//--выдача Ширины полей
const QList<int> &StorProject::GetFieldWidth() const
{
    return l_vv_FieldWidth;
}

//--выдача Диалогов полей
const QStringList &StorProject::GetFieldDialogName() const
{
    return l_vv_FieldDialogName;
}

//--выдача Путей полей
const QStringList &StorProject::GetFieldPath() const
{
    return l_vv_FieldPath;
}


//--выдача Имен диалогов
const QStringList &StorProject::GetDialogName() const
{
    return l_vv_DialogName;
}

//--выдача Код.Имен диалогов
const QStringList &StorProject::GetDialogCodName() const
{
    return l_vv_DialogCodName;
}



//--------Количество записей данных
const int &StorProject::Get_DataCount() const
{

    return DataCount;

}

//--Количество записей кэша
const int &StorProject::Get_DataCountCach() const
{

 //qDebug()<<"CachCurrentCount "<<CachCurrentCount;

    return CachCurrentCount;

}

//--Список данных кэша

const QStringList &StorProject::Get_DataCach() const
{
   //qDebug()<<"CachCurrentData "<<CachCurrentData;

    return CachCurrentData;
}


//--Список данных
const QList<QStringList> &StorProject::Get_FieldData() const
{
    return  l_vv_FieldData;
}

//--Интервал подгрузки
const QList <int>  &StorProject::Get_MinMax() const
{
    return l_MinMax;
}


//--Размер страницы

const int &StorProject::Get_PageSize() const
{

    return tPageSize;

}

//--Для Инфо

const QList<QStringList> &StorProject::GetFieldInfo() const
{

    return l_vv_FielInfo;

}

void StorProject::SetFieldInfo (int i, QString tVal)
{

    QStringList tList = l_vv_FielInfo.at(i);
    tList.replace(1, tVal);
    l_vv_FielInfo.replace(i,tList);

}


void StorProject::SetDocumNameLevel(QString tDocum)
{

    lDocumLevel.clear();

    if (tDocum == "")
    {
         for (int i=0; i<l_vv_DocLevel.length(); i++)
        {
            if (l_vv_DocLevel.at(i) == "0")
                lDocumLevel.append(l_vv_DocName.at(i));
         }
    }
    else
    {
        int tcNom = tDocum.count('.');

        for (int i=0; i<l_vv_DocLevel.length(); i++)
        {
            QString ttcNom =  QString::number(tcNom + 1);

            if (l_vv_DocLevel.at(i) == ttcNom)
                lDocumLevel.append(l_vv_DocName.at(i));
        }

    }

    //qDebug()<<"lDocumLevel "<<lDocumLevel;

}

// установка текущего количества кэш
void StorProject::SetCachCurrentCountData(int i)
{


 CachCurrentCount = lDataCachCount.value(i);
 CachCurrentData = l_vv_Cache.value(i);

 //qDebug()<<"i "<<i;
 //qDebug()<<"l_vv_Cache.value "<<l_vv_Cache.value(i);

 //qDebug()<<"l_vv_Cache.value+1 "<<l_vv_Cache.value(i + 1);
 //qDebug()<<"CachCurrentData "<<CachCurrentData;

   //qDebug()<<"lDataCachCount "<<lDataCachCount;
   //qDebug()<<"l_vv_Cache "<<l_vv_Cache;
}



const QStringList &StorProject::GetDocumName() const
{

return l_vv_DocName;


}


const QStringList &StorProject::GetDocumLevel() const
{

    return l_vv_DocLevel;

}


const QStringList &StorProject::GetDocumNameLevel() const
{

   // qDebug()<<"lDocumLevel "<<lDocumLevel;

    return lDocumLevel;

}


QList<int> &StorProject::GetFieldDocumForShow(QString tNameDocum )
{
  lFieldDocum.clear();
   QStringList lt_vv_CodDialog;


//----Ищем требуемый документ

   for (int i = 0; i<l_vv_DocName.length(); i++)

   {
       if (l_vv_DocName.value(i) == tNameDocum)
       {
           lt_vv_CodDialog = l_vv_DocDialogCod.value(i);

       }

   }


//---Сопоставляет отображаемые поля с документом


  for (int i = 0; i < l_vv_FieldDialogCod.length(); i++)

   {      

       lFieldDocum.append(0);
       for (int k = 0; k < lt_vv_CodDialog.length(); k++)

       {

        if(l_vv_FieldDialogCod.value(i) == lt_vv_CodDialog.value(k))

            lFieldDocum.replace(i, 1);
       }

   }


   return lFieldDocum;

}

