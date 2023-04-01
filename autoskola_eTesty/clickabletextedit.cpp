
#include "clickabletextedit.h"
#include <QMouseEvent>


ClickableTextEdit::ClickableTextEdit(QWidget* parent, Qt::WindowFlags f)
    : QTextEdit(parent) {

}

ClickableTextEdit::~ClickableTextEdit() {

}

void ClickableTextEdit::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}
