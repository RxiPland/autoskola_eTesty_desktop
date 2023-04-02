#ifndef QUESTIONSDIALOG_H
#define QUESTIONSDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>

namespace Ui {
class QuestionsDialog;
}

class QuestionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QuestionsDialog(QWidget *parent = nullptr);
    ~QuestionsDialog();

    void newQuestion();
    void loadSettings();

private slots:
    void on_plainTextEdit_clicked();
    void on_plainTextEdit_2_clicked();
    void on_plainTextEdit_3_clicked();

private:
    Ui::QuestionsDialog *ui;
    QNetworkAccessManager manager;

    void closeEvent(QCloseEvent *bar = nullptr);
    void hideWidgets(bool disable = true);

    QJsonObject getRandomQuestion();

    QByteArray userAgent;

};

#endif // QUESTIONSDIALOG_H
