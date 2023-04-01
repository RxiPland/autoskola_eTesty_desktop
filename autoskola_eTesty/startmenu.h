
#ifndef STARTMENU_H
#define STARTMENU_H

#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class StartMenu; }
QT_END_NAMESPACE

class StartMenu : public QMainWindow

{
    Q_OBJECT

public:
    StartMenu(QWidget *parent = nullptr);
    ~StartMenu();

private:
    Ui::StartMenu *ui;
};

#endif // STARTMENU_H
