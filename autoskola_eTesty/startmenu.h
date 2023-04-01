
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

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::StartMenu *ui;
};

#endif // STARTMENU_H
