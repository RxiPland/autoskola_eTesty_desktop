
#include "startmenu.h"
#include "./ui_startmenu.h"

#include <QFile>
#include <QDir>
#include <QLabel>
#include <QMessageBox>


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



void StartMenu::on_pushButton_3_clicked()
{
    // reset stats

    QDir directory(QDir::currentPath());
    directory.mkdir("./Data");

    QFile statsFile(QDir::currentPath() + "/Data/stats.json");

    if(statsFile.exists()){
        statsFile.open(QIODevice::WriteOnly | QIODevice::Text);
        statsFile.write("{}");
        statsFile.close();
    }

    QMessageBox::information(this, "Oznámení", "Statistiky byly úspěšně vyresetovány");
}


void StartMenu::on_pushButton_2_clicked()
{
    // show stats

    QMessageBox msgBox;
    msgBox.setWindowTitle("Statistiky");
    msgBox.setText("počet otázek správně: \n\n\n");
    msgBox.exec();
}

