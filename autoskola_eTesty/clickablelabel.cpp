
#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel{parent}
{

}

ClickableLabel::~ClickableLabel()
{

}

void ClickableLabel::mouseReleaseEvent(QMouseEvent *event)
{
    emit clicked();
}
