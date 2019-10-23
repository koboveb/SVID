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

//-------Get Выдача
const QStringList &GetFieldCod() const;//выдача Кодов полей
const QStringList &GetFieldType() const;//выдача Типов полей
const QStringList &GetFieldName() const;//выдача Имен полей
const QList<int> &GetFieldWidth() const;//выдача Ширины полей
const QStringList &GetFieldDialogName() const;//выдача Диалогов полей
const QStringList &GetFieldPath() const;//выдача Путей полей

const QStringList &GetDialogName() const; //выдача Имен диалогов
/*
const QList<QStringList> &Get_FieldDialog() const; //выдача полей диалогов
const QStringList &Get_DialogName() const;// имена диалогов
const int &Get_DialogCount() const; //количество диалогов
*/

const QStringList &GetDocumName() const; // имена документов
const QStringList &GetDocumLevel() const; // уровни документов

const int &Get_DataCount() const; //количество записей в данных
const QList<QStringList> &Get_FieldData() const; //основные данные
const QList <int>  &Get_MinMax() const; //интервал подгрузки
const int  &Get_PageSize() const; //размер страницы

const QList<QStringList> &GetFieldInfo() const; // данные для инфо


//---------Set Установка

void SetFieldInfo (int i, QString tVal); // установка значений в инфо



private:

//--путь
QString path;

//--файл проекта
    QFile* v_file_project;

//--размер страницы
    int tPageSize;

//--количество записей данных
int DataCount;


//--Поля

    QStringList l_vv_FieldCod; //Поля. Код
    QStringList l_vv_FieldType; //Поля. Тип
    QStringList l_vv_FieldName; //Поля. Имя поля
    QList<int> l_vv_FieldWidth; //Поля. Ширина
    QStringList l_vv_FieldDialogName; //Поля. Имя диалога
    QStringList l_vv_FieldPath; //Поля. Имя диалога

//--Диалоги
    QStringList l_vv_DialogName; //Диалоги Имена

//--Переменные для полей
    QList<QStringList> l_vv_FieldDialog; // Поля. Диалоги. Параметры


//--Переменные для документов

    QStringList l_vv_DocName; // Документ Имя
    QStringList l_vv_DocLevel; // Документ Уровень

    QList<QStringList> l_vv_DocDialog; // Список кодов Диалогов для документа
    //QList<QList<int>> l_vv_DocField; // Список кодов Поля для документов

//--Переменные для данных

    QList< QStringList > l_vv_FieldData; //список полей

    QList <int> l_MinMax; // список Мин и Макс знач интервала


//--Cписок для инфо
QList<QStringList> l_vv_FielInfo;



};

#endif // STORPROJECT_H
