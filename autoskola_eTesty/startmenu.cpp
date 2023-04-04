
#include "startmenu.h"
#include "./ui_startmenu.h"
#include "questionsdialog.h"

#include <QThread>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>


StartMenu::StartMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
{
    ui->setupUi(this);
    this->setWindowFlags(windowFlags() &(~Qt::WindowMaximizeButtonHint));
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

        QJsonObject newJson;
        newJson["correct"] = 0;
        newJson["wrong"] = 0;

        QJsonDocument docData(newJson);

        statsFile.open(QIODevice::WriteOnly | QIODevice::Text);
        statsFile.write(docData.toJson());
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


void StartMenu::on_pushButton_clicked()
{
    // start questions window

    QuestionsDialog qd;
    this->hide();

    qd.loadSettings();
    qd.newQuestion();

    qd.exec();


    this->show();
}

