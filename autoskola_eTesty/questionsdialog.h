#ifndef QUESTIONSDIALOG_H
#define QUESTIONSDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QElapsedTimer>

namespace Ui {
class QuestionsDialog;
}

class QuestionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QuestionsDialog(QWidget *parent = nullptr);
    ~QuestionsDialog();

    void loadSettings();
    void loadQuestions();
    void newQuestion();

    qint64 waitIntervalMs = 0;

    qint64 questionCount = 0;
    qint64 correctNum = 0;
    qint64 wrongNum = 0;

    bool exitApp = true;

    void updateTimeLabel();

    QStringList getQuestionsUrls(int topicId);

    QList<QStringList> topicsQuestionsUrls;

private slots:
    void on_answerA_clicked();
    void on_answerB_clicked();
    void on_answerC_clicked();

    void on_question_image_clicked();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_checkBox_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::QuestionsDialog *ui;
    QNetworkAccessManager manager;

    void closeEvent(QCloseEvent *bar = nullptr);
    void hideWidgets(bool hide = true);
    void disableWidgets(bool disable = true);

    void correct();
    void wrong();
    bool wrongLock = false;

    QElapsedTimer elapsedTime;

    QJsonObject getRandomQuestion();
    QString downloadFile(QString url, QString topicId, QString fileOrder);

    int width = 0;
    int height = 0;
    QString questionImagePath;
    QString correctLetter;

    int previousQuestionTopic = 0;

    bool automaticNewQuestion = true;

    QByteArray userAgent;

    QString urlRandom = "https://www.autoskola-testy.cz/prohlizeni_otazek.php?random=";
    QString urlTopic = "https://www.autoskola-testy.cz/prohlizeni_otazek.php?okruh=";

    QString patternQuestionsUrls = "kód (\\d+), <a href=\"(\\S+)\">";

    QString patternQuestionText = "\"question-text\".+>(.+)\n*\t*</p>";
    QString patternQuestionMedia = "src=\"(/img/[a-zA-z0-9/]+.[a-zA-Z0-9]+)";

    QString patternCorrect = "\"answer otazka_spravne\".+\n*\t*.+<p>(.+)</p>";
    QString patternWrong = "\"answer otazka_spatne\".+\n*\t*.+<p>(.+)</p>";

    QString patternQuestionId = "má kód (\\d+)";
    QString patternPoints = "za její správné zodpovězení v testech se získá.+(\\d) body?";

};

#endif // QUESTIONSDIALOG_H
