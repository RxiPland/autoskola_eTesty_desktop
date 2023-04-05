
#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H


#include <QWidget>
#include <QMouseEvent>
#include <Qt>
#include <QLabel>


class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel();

signals:
    void clicked();

protected:
    void mouseReleaseEvent(QMouseEvent* event);

};

#endif // CLICKABLELABEL_H
