#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    void loadSettings();

    QString appVersion;
    QByteArray userAgent;

    bool checkUpdates;
    qint64 waitingIntervalMiliseconds;

    bool settingsChanged = false;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

    void on_toolButton_clicked();
    void on_toolButton_2_clicked();

    void on_checkBox_clicked();

    void on_doubleSpinBox_valueChanged(double arg1);


private:
    Ui::SettingsDialog *ui;
    QNetworkAccessManager manager;

    void closeEvent(QCloseEvent *bar = nullptr);
    void disableWidgets(bool disable=true);
    bool saveSettings();

};

#endif // SETTINGSDIALOG_H
