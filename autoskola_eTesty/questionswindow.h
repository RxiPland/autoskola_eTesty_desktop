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

    void startQuiz();

    bool closed = false;

private:
    Ui::QuestionsWindow *ui;

    void closeEvent(QCloseEvent *bar = nullptr);

};

#endif // QUESTIONSWINDOW_H
