#include "ModelUni.h"

ModelUni::ModelUni(typemodel TypeModel, StorProject *StPr)
{

    TypeModelL = TypeModel;
    StorProj = StPr;

}




int ModelUni::columnCount(const QModelIndex &parent) const
{
    switch (TypeModelL)
    {
    case PROJECT:

    {
        (void) parent;
        return 2;

    }
     break;

    case CACHE:
    {
        (void) parent;
        return 1;
     }
    break;

    case DOCUM:
    {
      (void) parent;
       return 1;
    }
    break;
        
    case DATA:
    {

      (void) parent;
      return StorProj->GetFieldCod().length();
    }
    break;

    default:
    {
        (void) parent;
        return 2;


    }
    break;
    }



}

int ModelUni::rowCount(const QModelIndex &parent) const
{
    switch (TypeModelL)
    {
        case PROJECT:
            {
                (void) parent;
                return StorProj->GetFieldCod().length();
            }
                break;

        case CACHE:
            {
                (void) parent;
                return StorProj->Get_DataCountCach();
            }
                break;

        case DATA:
            {
                (void) parent;
                return StorProj->Get_DataCount();
            }
                break;
    case DOCUM:
        {
            (void) parent;
            return StorProj->GetDocumNameLevel().length();
        }
            break;

        default:
            {
                 (void) parent;
                 return 0;

            }
                break;
    }


}

QVariant ModelUni::data(const QModelIndex &index, int role) const
{


    switch (TypeModelL)
    {
    case PROJECT:

    {
        if (role == Qt::DisplayRole)
        {
         QString unswer = StorProj->GetFieldInfo().value(index.row()).value(index.column());
         return unswer;
        }
    return QVariant();
    }
    break;

    case CACHE:
    {
       if (role == Qt::DisplayRole)
        {

           //QString unswer = StCch.GetFields().value(index.row()).value(index.column());
           QString unswer = StorProj->Get_DataCach().value(index.row());
           qDebug()<<"Unswer "<<unswer;
           return unswer;

        }
        return QVariant();
    }
    break;

    case DOCUM:
    {

        if (role == Qt::DisplayRole)
         {

            QString unswer = StorProj->GetDocumNameLevel().value(index.row());


            return unswer;
         }
         return QVariant();


    }

         break;


    case DATA:
    {


        if (role == Qt::DisplayRole)
         {
             QString unswer;


            if (StorProj->Get_MinMax().value(0)<=index.row() && StorProj->Get_MinMax().value(1)>index.row() )

               unswer = StorProj->Get_FieldData().value(index.row() - StorProj->Get_MinMax().value(0)).value(index.column());



            return unswer;
         }
         return QVariant();


    }

        break;


    default:

        break;
    }


    return QVariant();




}


QVariant ModelUni::headerData(int section, Qt::Orientation orientation, int role) const
{


    switch (TypeModelL)
    {
    case PROJECT:

    {
        if (role != Qt::DisplayRole)
                 return QVariant();

        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
                         case 0:
                             return tr("Name");

                         case 1:
                             return tr("Value");

                         default:
                             return QVariant();
                     }
        }
        return QVariant();

    }

        break;

    case CACHE:

    {

        if (role != Qt::DisplayRole)
                 return QVariant();

        if (orientation == Qt::Horizontal)
        {

 // Разобраться!!!

            switch (section)
                {
                         case 0:
                             return tr("N doc");

                         case 1:
                             return tr("N text");

                         default:
                             return QVariant();
                }


        }
        return QVariant();

    }

        break;

    case DOCUM:

    {

        if (role != Qt::DisplayRole)
                 return QVariant();

        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
                         case 0:
                             return tr("N doc");

                         default:
                             return QVariant();
                     }
        }
        return QVariant();

    }

         break;

        

    case DATA:

    {

        if (role != Qt::DisplayRole)
                 return QVariant();

        if (orientation == Qt::Horizontal)

             return QString("%1").arg(StorProj->GetFieldName().value(section));

        else

           return QString("%1").arg(section + 1);

        return QVariant();

    }

         break;




/*
    case DOCKEY:

    {
        if (role != Qt::DisplayRole)
                 return QVariant();

        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
                         case 0:
                             return tr("Key");

                        case 1:
                              return tr("Document");

                         default:
                             return QVariant();
                     }
        }
        return QVariant();

    }

        break;

*/



        
   default:

        break;
    }

    return QVariant();

}





