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
    void on_answerA_clicked();
    void on_answerB_clicked();
    void on_answerC_clicked();

private:
    Ui::QuestionsDialog *ui;
    QNetworkAccessManager manager;

    void closeEvent(QCloseEvent *bar = nullptr);
    void hideWidgets(bool disable = true);

    QJsonObject getRandomQuestion();

    int width = 0;
    int height = 0;

    int previousTopicId = 1;
    QByteArray userAgent;

    QString url = "https://www.autoskola-testy.cz/prohlizeni_otazek.php?random=";

    QString patternQuestionText = "\"question-text\".+>(.+)\n*\t*</p>";
    QString patternQuestionMedia = "src=\"(/img/[a-zA-z0-9/]+.[a-zA-Z0-9]+)";

    QString patternCorrect = "\"answer otazka_spravne\".+\n*\t*.+<p>(.+)</p>";
    QString patternWrong = "\"answer otazka_spatne\".+\n*\t*.+<p>(.+)</p>";

    QString patternQuestionId = "má kód (\\d+)";
    QString patternPoints = "za její správné zodpovězení v testech se získá.+(\\d) body?";

};

#endif // QUESTIONSDIALOG_H
