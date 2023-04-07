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

    ui->label_2->clear();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::closeEvent(QCloseEvent *bar)
{
    // before window close

    if(settingsChanged){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Upozornění");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Bylo zjištěno neuložené nastavení! Chcete uložit změny?");
        QAbstractButton* pButtonYes = msgBox.addButton(" Ano ", QMessageBox::YesRole);
        msgBox.addButton(" Ne ", QMessageBox::YesRole);
        msgBox.exec();

        if (msgBox.clickedButton() == pButtonYes){
            // save settings

            bool saved = SettingsDialog::saveSettings();

            if(!saved){
                QMessageBox::critical(this, "Chyba", "Nastavení se nepodařilo uložit!");

                if(bar != nullptr){
                    bar->ignore();
                }

                return;

            } else{
                ui->label_2->clear();
            }
        }
    }

    if(bar != nullptr){
        bar->accept();
    }
}

void SettingsDialog::disableWidgets(bool disable)
{
    // disable widgets

    ui->pushButton->setDisabled(disable);
    ui->pushButton_2->setDisabled(disable);
    ui->pushButton_3->setDisabled(disable);
    ui->pushButton_4->setDisabled(disable);

    ui->checkBox->setDisabled(disable);

    ui->toolButton->setDisabled(disable);
}

bool SettingsDialog::saveSettings()
{
    // save settings if changed

    if(settingsChanged){

        QFile settingsFile(QDir::currentPath() + "/Data/settings.json");

        if (settingsFile.exists()){
            settingsFile.open(QIODevice::ReadOnly | QIODevice::Text);

            QByteArray fileContent = settingsFile.readAll();
            settingsFile.close();


            if(!fileContent.isEmpty()){

                QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

                if(!loadedJson.isEmpty()){
                    // everything OK

                    loadedJson["check_for_updates"] = ui->checkBox->isChecked();

                    QJsonDocument docData(loadedJson);

                    settingsFile.open(QIODevice::WriteOnly | QIODevice::Text);
                    settingsFile.write(docData.toJson());
                    settingsFile.close();

                    settingsChanged = false;

                    return true;
                }
            }
        }

    } else{
        return true;
    }

    return false;
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
                SettingsDialog::checkUpdates = loadedJson["check_for_updates"].toBool();

                ui->label->setText("Aktuální verze " + appVersion);
                ui->checkBox->setChecked(SettingsDialog::checkUpdates);
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
        msgBox.setText("Je dostupná novější verze!\n\nVaše verze: " + appVersion  + "\nDostupná verze: " + newestVersion + "\n\nPři instalaci nové verze se předchozí automaticky odstraní.");
        QAbstractButton* pButtonYes = msgBox.addButton("  Otevřít  ", QMessageBox::YesRole);
        msgBox.addButton("Zrušit", QMessageBox::YesRole);
        msgBox.exec();

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


void SettingsDialog::on_checkBox_clicked()
{
    // check updates checkbox

    SettingsDialog::checkUpdates = ui->checkBox->isChecked();

    if(!settingsChanged){
        ui->label_2->setText("Nastavení není uloženo");
        ui->label_2->setStyleSheet("color: red");
        SettingsDialog::settingsChanged = true;
    }
}


void SettingsDialog::on_toolButton_clicked()
{
    // help - check version
    QMessageBox::information(this, "Nápověda", "Pokud bude povoleno, tak se při spuštění aplikace automaticky zkontroluje, zda nevyšla nová verze programu. Kontrolovat aktualizace jde i manuálně.");
}


void SettingsDialog::on_pushButton_2_clicked()
{
    // default settings

    ui->checkBox->setChecked(true);

    SettingsDialog::checkUpdates = ui->checkBox->isChecked();


    ui->label_2->setText("Nastavení není uloženo");
    ui->label_2->setStyleSheet("color: red");
    SettingsDialog::settingsChanged = true;

    QMessageBox::information(this, "Oznámení", "Bylo nastaveno defaultní nastavení, nezapomeňte uložit změny");
}


void SettingsDialog::on_pushButton_3_clicked()
{
    // cancel settings

    this->close();
}


void SettingsDialog::on_pushButton_4_clicked()
{
    // save settings

    bool saved = SettingsDialog::saveSettings();

    if(saved){
        ui->label_2->clear();
        QMessageBox::information(this, "Oznámení", "Nastavení bylo úspěšně uloženo");
        this->close();

    } else{
        QMessageBox::critical(this, "Chyba", "Nastavení se nepodařilo uložit!");
    }
}

