
#include "startmenu.h"
#include "./ui_startmenu.h"
#include "questionsdialog.h"
#include "settingsdialog.h"

#include <QThread>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QProcess>


StartMenu::StartMenu(QWidget *parent, QString appVersion)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
{
    ui->setupUi(this);
    this->setWindowFlags(windowFlags() &(~Qt::WindowMaximizeButtonHint));

    this->setWindowTitle(this->windowTitle() + " | " + appVersion);
    StartMenu::appVersion = appVersion;
}

StartMenu::~StartMenu()
{
    delete ui;
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
                qint64 averageTime = loadedJson["question_average_time"].toInteger();

                statsText = "Celkem otázek: " + QString::number(questionsCount) + "\t\t\n\n";
                statsText += "Počet správně: " + QString::number(correctNum) + "\t\t\n";
                statsText += "Počet špatně: " + QString::number(wrongNum) + "\t\t\n\n";

                if(questionsCount > 0){

                    if(correctNum == questionsCount){
                        statsText += "Úspěšnost: 100% " + QString("(%1 z %2)").arg(QString::number(correctNum), QString::number(questionsCount)) + "\t\t\n";
                    } else{
                        statsText += QString("Úspěšnost: %1").arg((qint64)((float)correctNum/((float)questionsCount/100))) + "% " + QString("(%1 z %2)").arg(QString::number(correctNum), QString::number(questionsCount)) + "\t\t\n";
                    }
                    statsText += QString("Průměrný čas jedné otázky: %1").arg(averageTime) + "s" + "\t\t";
                }
            }
        }
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Statistiky");
    msgBox.setIconPixmap(QPixmap(":/icons/etesty_logo.jpg"));
    msgBox.setWindowIcon(this->windowIcon());
    msgBox.setText(statsText);
    QAbstractButton* pButtonReset = msgBox.addButton(" Reset ", QMessageBox::NoRole);
    msgBox.addButton(" Ok ", QMessageBox::NoRole);

    pButtonReset->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    msgBox.exec();

    if (msgBox.clickedButton() == pButtonReset){

        QDir directory(QDir::currentPath());
        directory.mkdir("./Data");

        QFile statsFile(QDir::currentPath() + "/Data/stats.json");

        QJsonObject newJson;
        newJson["correct"] = 0;
        newJson["wrong"] = 0;
        newJson["question_average_time"] = 0;

        QJsonDocument docData(newJson);

        statsFile.open(QIODevice::WriteOnly | QIODevice::Text);
        statsFile.write(docData.toJson());
        statsFile.close();

        QMessageBox::information(this, "Oznámení", "Statistiky byly úspěšně vyresetovány");

        return;
    }
}


void StartMenu::on_pushButton_3_clicked()
{
    // settings dialog

    SettingsDialog sd;
    sd.loadSettings();
    sd.exec();
}

void StartMenu::on_pushButton_4_clicked()
{
    // open website (autoskola-testy.cz)

    QStringList arguments;
    arguments.append("/C");
    arguments.append("start");
    arguments.append("https://www.autoskola-testy.cz");

    QProcess::startDetached("cmd.exe", arguments);
}


void StartMenu::on_pushButton_5_clicked()
{
    // open website (github.com)

    QStringList arguments;
    arguments.append("/C");
    arguments.append("start");
    arguments.append("https://github.com/RxiPland/autoskola_eTesty_desktop");

    QProcess::startDetached("cmd.exe", arguments);
}

