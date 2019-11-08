#ifndef TTEXTEDIT_H
#define TTEXTEDIT_H
#include <QTextEdit>
#include <QKeyEvent>
#include <QDebug>

class TTextEdit : public QTextEdit
{

    Q_OBJECT

public:

    TTextEdit(QWidget *parent):QTextEdit(parent){}

    void keyPressEvent(QKeyEvent * event);

signals:
    void sReturn();
    void sShiftReturn();
    void sAltReturn();

    void sKDown();
    void sKUp();
    void sKRight();
    void sKLeft();
    void sKTab();
    void sKEnd();

    void sKPgDown();
    void sKPgUp();
};

#endif // TTEXTEDIT_H
