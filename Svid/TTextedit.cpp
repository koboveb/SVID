#include "TTextedit.h"

void TTextEdit::keyPressEvent(QKeyEvent *event)
{

    switch (event->key())
    {
    case Qt::Key_Up:
       emit sKUp();
        break;
    case Qt::Key_Down:       
       emit sKDown();
        break;
    case Qt::Key_Right:
       emit sKRight();
        break;
    case Qt::Key_Left:
       emit sKLeft();
        break;

    case Qt::Key_End:
       emit sKEnd();
        break;

        /*
    case Qt::Key_PageDown:
       emit sKPgDown();
        break;
    case Qt::Key_PageUp:
       emit sKPgUp();
        break;
        */

    case Qt::Key_Tab:
       emit sKTab();
        break;
    case Qt::Key_Return:


        switch (event->modifiers())
        {
        case Qt::ShiftModifier:
            emit sShiftReturn();
            break;
        case Qt::AltModifier:
            emit sAltReturn();
            break;
        default:
            emit sReturn();
            break;
        }


        break;
    default:
        QTextEdit::keyPressEvent(event);
        break;
    }

}

