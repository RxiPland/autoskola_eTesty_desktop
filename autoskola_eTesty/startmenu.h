
#ifndef STARTMENU_H
#define STARTMENU_H

#include <QMainWindow>
#include <QNetworkAccessManager>


QT_BEGIN_NAMESPACE
namespace Ui { class StartMenu; }
QT_END_NAMESPACE

class StartMenu : public QMainWindow

{
    Q_OBJECT

public:
    StartMenu(QWidget *parent = nullptr);
    ~StartMenu();

    QString appVersion;
    QByteArray userAgent;
    bool checkForUpdates = true;

    void loadSettings();
    void checkNewVersion();


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::StartMenu *ui;
    QNetworkAccessManager manager;
};

#endif // STARTMENU_H
