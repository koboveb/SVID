#include <QFile>
#include <QtXml>


#ifndef STORPROJECT_H
#define STORPROJECT_H

class StorProject
{
public:
    StorProject(const QString &tPath);
    ~StorProject();

//-------Load

void LoadDocum();
void LoadData (int CurrentRow);
void LoadDataCount();
void LoadDataCachCount();
void LoadDataCach();

//-------Get Выдача
const QStringList &GetFieldCod() const;//выдача Кодов полей
const QStringList &GetFieldType() const;//выдача Типов полей
const QStringList &GetFieldName() const;//выдача Имен полей
const QList<int> &GetFieldWidth() const;//выдача Ширины полей
const QStringList &GetFieldDialogName() const;//выдача Диалогов полей
const QStringList &GetFieldPath() const;//выдача Путей полей

const QStringList &GetDialogName() const; //выдача Имен диалогов
const QStringList &GetDialogCodName() const; //выдача Код.Имя диалогов

QList<int> &GetFieldDocumForShow(QString tNameDocum );//выдача полей документов для отображения

const QStringList &GetDocumName() const; // имена документов
const QStringList &GetDocumLevel() const; // уровни документов
const QStringList &GetDocumNameLevel() const; // выдача документов от уровня

const int &Get_DataCount() const; //количество записей в данных
const int &Get_DataCountCach() const; //количество записей в кэше

const QList<QStringList> &Get_FieldData() const; //основные данные
const QList <int>  &Get_MinMax() const; //интервал подгрузки
const int  &Get_PageSize() const; //размер страницы

const QList<QStringList> &GetFieldInfo() const; // данные для инфо

const QStringList &Get_DataCach() const; //данные кэша

//---------Set Установка

void SetFieldInfo (int i, QString tVal); // установка значений в инфо
void SetDocumNameLevel(QString tDocum); // установка уровня для имен документов
void SetCachCurrentCount(int i); // установка текущего количества кэша

private:

//--путь
QString path;

//--файл проекта
    QFile* v_file_project;

//--размер страницы
    int tPageSize;

//--количество записей данных
int DataCount;
//--количество записей данных кэша
QList<int> lDataCachCount;

//--количество в текущем кэше
int CachCurrentCount = 0;

//--данные в текущем кэше
QStringList CachCurrentData;

//--Поля

    QStringList l_vv_FieldCod; //Поля. Код
    QStringList l_vv_FieldType; //Поля. Тип
    QStringList l_vv_FieldName; //Поля. Имя поля
    QList<int> l_vv_FieldWidth; //Поля. Ширина
    QStringList l_vv_FieldDialogName; //Поля. Имя диалога
    QStringList l_vv_FieldDialogCod; //Поля. Код диалога
    QStringList l_vv_FieldPath; //Поля. Путь документа

//--Диалоги

    QStringList l_vv_DialogName; //Диалоги Имена
    QStringList l_vv_DialogCodName; //Диалоги Код + Имя

//--Переменные для полей
    QList<QStringList> l_vv_FieldDialog; // Поля. Диалоги. Параметры


//--Переменные для документов

    QStringList l_vv_DocName; // Документ Имя
    QStringList l_vv_DocLevel; // Документ Уровень

    QStringList lDocumLevel; // Документы от уровня

    QList<QStringList> l_vv_DocDialogCod; // Список кодов Диалогов для документа
    QList<int> lFieldDocum; // Список для отображения полей документов
    //QList<QList<int>> l_vv_DocField; // Список кодов Поля для документов

//--Переменные для данных

    QList< QStringList > l_vv_FieldData; //список полей

    QList <int> l_MinMax; // список Мин и Макс знач интервала


//--Cписок для инфо
QList<QStringList> l_vv_FielInfo;

//--Переменные для кэша
QList<QStringList> l_vv_Cache; //список полей



};

#endif // STORPROJECT_H
