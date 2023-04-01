#ifndef QUESTIONSWINDOW_H
#define QUESTIONSWINDOW_H

#include <QMainWindow>


namespace Ui {
class QuestionsWindow;
}

class QuestionsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuestionsWindow(QWidget *parent = nullptr);
    ~QuestionsWindow();

    void newQuestion();

    bool closed = false;

private slots:

    void on_plainTextEdit_clicked();
    void on_plainTextEdit_2_clicked();
    void on_plainTextEdit_3_clicked();

private:
    Ui::QuestionsWindow *ui;

    void closeEvent(QCloseEvent *bar = nullptr);
    void disableWidgets(bool disable = true);

    QJsonObject getRandomQuestion();


};

#endif // QUESTIONSWINDOW_H
