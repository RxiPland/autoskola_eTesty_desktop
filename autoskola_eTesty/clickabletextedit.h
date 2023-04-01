
#ifndef CLICKABLETEXTEDIT_H
#define CLICKABLETEXTEDIT_H


#include <QTextEdit>
#include <QWidget>
#include <QMouseEvent>
#include <Qt>

class ClickableTextEdit : public QTextEdit {
    Q_OBJECT

public:
    explicit ClickableTextEdit(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableTextEdit();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // CLICKABLETEXTEDIT_H
