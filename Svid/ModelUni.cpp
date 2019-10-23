#include "ModelUni.h"

ModelUni::ModelUni(typemodel TypeModel, StorProject *StPr)
{

    TypeModelL = TypeModel;
    StorProj = StPr;

 /*
    if (StorProj == NULL)
 StorProj = new StorProject;
*/
    switch (TypeModelL)
    {
    case PROJECT:

    {
    }

        break;

    case CACHE:
    {

        //StCch.Load(i);

    }
        break;


    case DOCUM:
    {


    }
         break;   



    case DATA:
    {
    }
         break;


/*
    case DOCKEY:
    {
    }
         break;

*/


    default:

        break;
    }

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

/*
    case DOCKEY:
    {

      (void) parent;
       return 2;
    }
    break;
*/
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
/*
        case CACHE:
            {
                (void) parent;
                //return StCch.GetDialogsCount();
            }
                break;
*/
        case DATA:
            {
                (void) parent;
                return StorProj->Get_DataCount();
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
/*
           QString unswer = StCch.GetFields().value(index.row()).value(index.column());
           return unswer;
           */
        }
        return QVariant();
    }
    break;

    case DOCUM:
    {

        if (role == Qt::DisplayRole)
         {

            QString unswer = StorProj->GetDocumName().value(index.row());


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





/*
    case DOCKEY:
    {


        if (role == Qt::DisplayRole)
         {

            QString unswer = StDat.getlValsKeyKey().value(index.row()).value(index.column());

            return unswer;
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

/*
bool ModelUni::setData(const QModelIndex &index, const QVariant &value, int role)
 {


    switch (TypeModelL)
    {
    case PROJECT:

    {


        if (index.isValid() && role == Qt::EditRole)
        {

           StorProj->SetFieldInfo(index.row(), value.toString());
           emit dataChanged(index, index);
            return true;
        }
        return false;

    }
    break;

    case CACHE:

    {

        if (index.isValid() && role == Qt::EditRole)
        {


            QStringList lValue;

            lValue << value.toString();
            StCch.SetRow(index.row(), lValue);

           emit dataChanged(index, index);
            return true;
        }
        return false;
    }

        break;

    case DOCUM:

    {


    }

         break;

    default:

        break;
    }

    return false;

 }

*/

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

                         case 1:
                             return tr("N text");

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





        
   default:

        break;
    }

    return QVariant();

}
/*
bool ModelUni::insertRows(const QModelIndex &parent)
{

        switch (TypeModelL)
             {
             case PROJECT:

             {

             }

                 break;

             case CACHE:

             {

            (void) parent;
            beginInsertRows(QModelIndex(), position, position+rows-1);
            QStringList ltt;
            ltt << "" << "";
            StCch.InsertRow(ltt);
            endInsertRows();
                 return true;


             }

                 break;

             case DOCUM:

             {


             }

                  break;

             default:

                 break;
             }

  return false;

}

bool ModelUni::Save(QString DataForSave)
{

  switch (TypeModelL)
         {
         case PROJECT:

         {}

             break;

         case CACHE:

         {
            StCch.Save(QString::fromLocal8Bit("%1%2").arg(DataForSave).arg("\n"));
         }

             break;

         case DOCUM:

         {}

              break;

         case DATA:

         {
            StDat.Save(DataForSave);
         }

                break;


         default:

             break;
         }

return false;

}
*/




