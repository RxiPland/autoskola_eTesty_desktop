
#include "startmenu.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>


QString appVersion = "v1.0.0";


void checkStatsFile(){
    // check file with stats

    QFile statsFile(QDir::currentPath() + "/Data/stats.json");

    if(statsFile.exists()){

        statsFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QByteArray fileContent = statsFile.readAll();
        statsFile.close();

        if(fileContent.isEmpty()){
            // File is empty

        } else{
            QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

            if(loadedJson.isEmpty()){
                // JSON is corrupted

            } else{
                // OK

                return;
            }
        }
    }


    QDir directory(QDir::currentPath());
    directory.mkdir("./Data");

    statsFile.open(QIODevice::WriteOnly | QIODevice::Text);
    statsFile.write("{}");
    statsFile.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // check if json is not corrupted
    checkStatsFile();

    StartMenu w;
    w.show();
    return a.exec();
}
