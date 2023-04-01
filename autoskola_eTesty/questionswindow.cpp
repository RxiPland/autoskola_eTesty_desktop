#include "questionswindow.h"
#include "ui_questionswindow.h"

#include <QCloseEvent>
#include <QPixmap>


QuestionsWindow::QuestionsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuestionsWindow)
{
    ui->setupUi(this);

    this->show();
}

QuestionsWindow::~QuestionsWindow()
{
    delete ui;
}

void QuestionsWindow::startQuiz()
{
    // start quiz

    QPixmap questionImage("C:/Users/libor/Downloads/0447.jpg");
    ui->label->setAlignment(Qt::AlignCenter);
    ui->image_label->setAlignment(Qt::AlignCenter);
    ui->image_label->setPixmap(questionImage.scaled(ui->image_label->width(), ui->image_label->height(), Qt::KeepAspectRatio));
}

void QuestionsWindow::closeEvent(QCloseEvent *bar)
{
    // before window close
    QuestionsWindow::closed = true;

    if(bar != nullptr){
        bar->accept();
    }
}
