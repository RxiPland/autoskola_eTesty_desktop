
#include "startmenu.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>


QString appVersion = "v1.0.0";


void checkFilesIntegrity(){
    // check stats and settings file

    QJsonObject loadedJson;
    QByteArray fileContent;
    QDir directory(QDir::currentPath());

    bool corrupted = false;


    // STATS FILE INTEGRITY
    QFile statsFile(QDir::currentPath() + "/Data/stats.json");

    if(statsFile.exists()){

        statsFile.open(QIODevice::ReadOnly | QIODevice::Text);

        fileContent = statsFile.readAll();
        statsFile.close();

        if(fileContent.isEmpty()){
            // File is empty
            corrupted = true;

        } else{
            loadedJson = QJsonDocument::fromJson(fileContent).object();

            if(loadedJson.isEmpty()){
                // JSON is corrupted
                corrupted = true;

            } else{
                // OK
                corrupted = false;
            }
        }

    } else{
        // file does not exists
        corrupted = true;
    }


    if(corrupted){
        directory.mkdir("./Data");

        statsFile.open(QIODevice::WriteOnly | QIODevice::Text);
        statsFile.write("{}");
        statsFile.close();
    }


    // SETTINGS FILE INTEGRITY
    QFile settingsFile(QDir::currentPath() + "/Data/settings.json");

    if(settingsFile.exists()){

        settingsFile.open(QIODevice::ReadOnly | QIODevice::Text);

        fileContent = settingsFile.readAll();
        settingsFile.close();

        if(fileContent.isEmpty()){
            // File is empty
            corrupted = true;

        } else{
            loadedJson = QJsonDocument::fromJson(fileContent).object();

            if(loadedJson.isEmpty()){
                // JSON is corrupted
                corrupted = true;

            } else{
                // OK
                corrupted = false;
            }
        }

    } else{
        // file does not exists
        corrupted = true;
    }


    if(corrupted){
        directory.mkdir("./Data");

        QJsonObject newJson;
        newJson["user_agent"] = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/111.0.0.0 Safari/537.36";

        QJsonDocument docData(newJson);

        settingsFile.open(QIODevice::WriteOnly | QIODevice::Text);
        settingsFile.write(docData.toJson());
        settingsFile.close();
    }
    //corrupted = false;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // check if json is not corrupted
    checkFilesIntegrity();

    StartMenu w;
    w.show();
    return a.exec();
}
