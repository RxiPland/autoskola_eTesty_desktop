#include "questionsdialog.h"
#include "ui_questionsdialog.h"

#include <QCloseEvent>
#include <QPixmap>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QProcess>
#include <QTimer>


QuestionsDialog::QuestionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionsDialog)
{
    ui->setupUi(this);

    ui->label->setAlignment(Qt::AlignCenter);
    ui->image_label->setAlignment(Qt::AlignCenter);

    this->show();
}


QuestionsDialog::~QuestionsDialog()
{
    delete ui;
}

void QuestionsDialog::closeEvent(QCloseEvent *bar)
{
    // before window close

    if(bar != nullptr){
        bar->accept();
    }
}

void QuestionsDialog::hideWidgets(bool hide)
{
    // hide widgets

    ui->plainTextEdit->setHidden(hide);
    ui->plainTextEdit_2->setHidden(hide);
    ui->plainTextEdit_3->setHidden(hide);

    ui->label->setHidden(hide);
    ui->image_label->setHidden(hide);
}

void QuestionsDialog::loadSettings()
{
    // load settings from file

    QFile dataFile(QDir::currentPath() + "/Data/settings.json");

    if (dataFile.exists()){
        dataFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QByteArray fileContent = dataFile.readAll();
        dataFile.close();

        if(fileContent.isEmpty()){
            // File is empty

            QMessageBox::critical(this, "Chyba", "Soubor s nastavením je prázdný! Program bude restartován pro opravu.");

            QProcess::startDetached(QApplication::applicationFilePath());
            QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
            return;

        } else{
            QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

            if(loadedJson.isEmpty()){
                // JSON is corrupted

                QMessageBox::critical(this, "Chyba", "JSON v souboru s nastavením je poškozený! Program bude restartován pro opravu.");

                QProcess::startDetached(QApplication::applicationFilePath());
                QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
                return;

            } else{
                // everything OK


                QuestionsDialog::userAgent = loadedJson["user_agent"].toString().toUtf8();

            }
        }

    } else{
        // file with settings not found

        QMessageBox::critical(this, "Chyba", "Soubor s nastavením neexistuje! Program bude restartován pro opravu.");

        QProcess::startDetached(QApplication::applicationFilePath());
        QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
        return;
    }
}

void QuestionsDialog::newQuestion()
{
    // set new question

    qInfo() << "new question";

    QJsonObject question = QuestionsDialog::getRandomQuestion();

    if(question.isEmpty()){

        //return;
    }


    QPixmap questionImage("C:/Users/libor/Downloads/0447.jpg");
    ui->image_label->setPixmap(questionImage.scaled(ui->image_label->width(), ui->image_label->height(), Qt::KeepAspectRatio));
}

QJsonObject QuestionsDialog::getRandomQuestion()
{
    // get random question
    QuestionsDialog::hideWidgets();

    QJsonObject question;
    /*

    QNetworkRequest request;
    request.setUrl(QUrl("https://api.github.com/repos/RxiPland/y2mate_desktop/releases/latest"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);

    QNetworkReply *replyGet = manager.get(request);

    while (!replyGet->isFinished())
    {
        qApp->processEvents();
    }

    QNetworkReply::NetworkError error = replyGet->error();
    */

    QuestionsDialog::hideWidgets(false);

    return question;
}


void QuestionsDialog::on_plainTextEdit_clicked()
{
    qInfo() << "answer A";

    ui->plainTextEdit->setStyleSheet("background-image: url(C:/Users/libor/Downloads/e8d.jpg); background-position: center center;");

    // if correct
    QTimer::singleShot(1000, this, &QuestionsDialog::newQuestion);
}

void QuestionsDialog::on_plainTextEdit_2_clicked()
{
    qInfo() << "answer B";

    ui->plainTextEdit_2->setStyleSheet("background-image: url(C:/Users/libor/Downloads/e8d.jpg); background-position: center center;");

    // if correct
    QTimer::singleShot(1000, this, &QuestionsDialog::newQuestion);
}

void QuestionsDialog::on_plainTextEdit_3_clicked()
{
    qInfo() << "answer C";

    ui->plainTextEdit_3->setStyleSheet("background-image: url(C:/Users/libor/Downloads/e8d.jpg); background-position: center center;");

    // if correct
    QTimer::singleShot(1000, this, &QuestionsDialog::newQuestion);
}

