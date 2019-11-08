#ifndef TTABLEVIEW_H
#define TTABLEVIEW_H
#include <QTableView>
#include <QWheelEvent>

#include <QDebug>

class TTableView: public QTableView
{

    Q_OBJECT

public:
    TTableView(QWidget *parent):QTableView(parent){}

    void wheelEvent(QWheelEvent *event);

signals:

    void ScrollValueChanged();


};

#endif // TTABLEVIEW_H
