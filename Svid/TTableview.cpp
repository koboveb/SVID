#include "TTableview.h"

void TTableView::wheelEvent(QWheelEvent *event)
{

    switch (event->phase())
    {

    case Qt::ScrollUpdate :
        QTableView::wheelEvent(event);
        emit ScrollValueChanged();
        break;

    default:
        QTableView::wheelEvent(event);
        break;
    }
}
