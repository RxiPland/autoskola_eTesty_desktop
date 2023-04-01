
#include "startmenu.h"
#include "./ui_startmenu.h"


StartMenu::StartMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
{
    ui->setupUi(this);
}

StartMenu::~StartMenu()
{
    delete ui;
}


