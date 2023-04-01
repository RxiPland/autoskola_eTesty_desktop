#include "questionswindow.h"
#include "ui_questionswindow.h"

#include <QCloseEvent>
#include <QPixmap>
#include <QJsonObject>
#include <QJsonDocument>


QuestionsWindow::QuestionsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuestionsWindow)
{
    ui->setupUi(this);
    ui->label->setAlignment(Qt::AlignCenter);
    ui->image_label->setAlignment(Qt::AlignCenter);

    this->show();
}

QuestionsWindow::~QuestionsWindow()
{
    delete ui;
}

void QuestionsWindow::closeEvent(QCloseEvent *bar)
{
    // before window close
    QuestionsWindow::closed = true;

    if(bar != nullptr){
        bar->accept();
    }
}

void QuestionsWindow::disableWidgets(bool disable)
{
    // disable widgets

    ui->plainTextEdit->setDisabled(disable);
    ui->plainTextEdit_2->setDisabled(disable);
    ui->plainTextEdit_3->setDisabled(disable);
}


void QuestionsWindow::newQuestion()
{
    // set new question

    QJsonObject question = QuestionsWindow::getRandomQuestion();

    if(question.isEmpty()){

        //return;
    }


    QPixmap questionImage("C:/Users/libor/Downloads/0447.jpg");
    ui->image_label->setPixmap(questionImage.scaled(ui->image_label->width(), ui->image_label->height(), Qt::KeepAspectRatio));
}


QJsonObject QuestionsWindow::getRandomQuestion()
{
    // get random question



    return QJsonObject();
}


void QuestionsWindow::on_plainTextEdit_clicked()
{
    qInfo() << "answer A";
}

void QuestionsWindow::on_plainTextEdit_2_clicked()
{
    qInfo() << "answer B";
}

void QuestionsWindow::on_plainTextEdit_3_clicked()
{
    qInfo() << "answer C";
}

