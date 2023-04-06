#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QProcess>
#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QCloseEvent>


SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::disableWidgets(bool disable)
{
    // disable widgets

    ui->pushButton->setDisabled(disable);
}

void SettingsDialog::closeEvent(QCloseEvent *bar)
{
    // before window close

    if(bar != nullptr){
        bar->accept();
    }
}

void SettingsDialog::loadSettings()
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

                SettingsDialog::userAgent = loadedJson["user_agent"].toString().toUtf8();
                SettingsDialog::appVersion = loadedJson["app_version"].toString();

                ui->label->setText("Aktuální verze " + appVersion);
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

void SettingsDialog::on_pushButton_clicked()
{
    // check new version
    SettingsDialog::disableWidgets();

    QNetworkRequest request;
    request.setUrl(QUrl("https://api.github.com/repos/RxiPland/autoskola_eTesty_desktop/releases/latest"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);

    QNetworkReply *replyGet = manager.get(request);

    while (!replyGet->isFinished())
    {
        qApp->processEvents();
    }

    QNetworkReply::NetworkError error = replyGet->error();

    if (error == QNetworkReply::HostNotFoundError || error == QNetworkReply::UnknownNetworkError){
        // no internet connection available

        QMessageBox::critical(this, "Aktualizace", QString("Nelze se připojit k internetu nebo server (%1) není dostupný!").arg("api.github.com"));
        SettingsDialog::disableWidgets(false);

        return;

    } else if (error != QNetworkReply::NoError){

        QMessageBox::critical(this, "Aktualizace", QString("Nastala chyba: %1").arg(replyGet->errorString()));
        SettingsDialog::disableWidgets(false);

        return;
    }

    QByteArray response = replyGet->readAll();
    replyGet->deleteLater();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();

    QString newestVersion = jsonObject["tag_name"].toString();

    if (newestVersion != appVersion && newestVersion != ""){

        QMessageBox msgBox;
        msgBox.setWindowTitle("Aktualizace");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Je dostupná novější verze!\n\nVaše verze: " + appVersion  + "\nDostupná verze: " + newestVersion);
        QAbstractButton* pButtonYes = msgBox.addButton("  Otevřít  ", QMessageBox::YesRole);
        msgBox.addButton("Zrušit", QMessageBox::YesRole);

        if(msgBox.clickedButton() == pButtonYes){
            // open github page

            QStringList arguments;
            arguments.append("/C");
            arguments.append("start");
            arguments.append("https://github.com/RxiPland/autoskola_eTesty_desktop");

            QProcess::startDetached("cmd.exe", arguments);
        }


    } else{
        QMessageBox::information(this, "Aktualizace", QString("Již máte nejnovější verzi (%1)").arg(newestVersion));
    }

    SettingsDialog::disableWidgets(false);
}
