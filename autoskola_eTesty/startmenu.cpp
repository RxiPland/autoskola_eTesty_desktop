
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

    QString statsText = "Nastala chyba!";
    QByteArray fileContent;
    QJsonObject loadedJson;

    QFile statsFile(QDir::currentPath() + "/Data/stats.json");

    if(statsFile.exists()){

        statsFile.open(QIODevice::ReadOnly | QIODevice::Text);

        fileContent = statsFile.readAll();
        statsFile.close();

        if(!fileContent.isEmpty()){

            loadedJson = QJsonDocument::fromJson(fileContent).object();


            if(!loadedJson.isEmpty()){
                qint64 correctNum = loadedJson["correct"].toInteger();
                qint64 wrongNum = loadedJson["wrong"].toInteger();
                qint64 questionsCount = correctNum + wrongNum;

                statsText = "Celkem otázek: " + QString::number(questionsCount) + "\t\t\n\n";
                statsText += "Počet správně: " + QString::number(correctNum) + "\t\t\n";
                statsText += "Počet špatně: " + QString::number(wrongNum) + "\t\t\n\n";

                if(questionsCount > 0){
                    statsText += QString("Úspěšnost: %1").arg((qint64)((float)correctNum/((float)questionsCount/100))) + "%";
                }
            }
        }
    }

    QMessageBox::information(this, "Statistiky", statsText);
}


void StartMenu::on_pushButton_clicked()
{
    // start questions window

    QuestionsDialog qd;
    this->hide();

    qd.loadSettings();
    qd.newQuestion();

    qd.exec();

    if(qd.exitApp){
        this->close();
        return;
    }

    this->show();
}

