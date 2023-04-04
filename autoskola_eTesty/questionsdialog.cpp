#include "questionsdialog.h"
#include "ui_questionsdialog.h"

#include <QCloseEvent>
#include <QPixmap>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QProcess>
#include <QTimer>
#include <QRandomGenerator>
#include <QRegularExpression>


QuestionsDialog::QuestionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionsDialog)
{
    ui->setupUi(this);

    ui->question_image->setAlignment(Qt::AlignCenter);
    this->show();
}


QuestionsDialog::~QuestionsDialog()
{
    delete ui;
}

void QuestionsDialog::closeEvent(QCloseEvent *bar)
{
    // before window close

    if(bar != nullptr){
        bar->accept();
    }
}

void QuestionsDialog::hideWidgets(bool hide)
{
    // hide widgets

    ui->answerA->setHidden(hide);
    ui->answerB->setHidden(hide);
    ui->answerC->setHidden(hide);

    ui->question_imageText->setHidden(hide);
    ui->question_text->setHidden(hide);
    ui->question_image->setHidden(hide);
}

void QuestionsDialog::loadSettings()
{
    // load settings from file

    QFile dataFile(QDir::currentPath() + "/Data/settings.json");

    if (dataFile.exists()){
        dataFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QByteArray fileContent = dataFile.readAll();
        dataFile.close();

        if(fileContent.isEmpty()){
            // File is empty

            QMessageBox::critical(this, "Chyba", "Soubor s nastavením je prázdný! Program bude restartován pro opravu.");

            QProcess::startDetached(QApplication::applicationFilePath());
            QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
            return;

        } else{
            QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

            if(loadedJson.isEmpty()){
                // JSON is corrupted

                QMessageBox::critical(this, "Chyba", "JSON v souboru s nastavením je poškozený! Program bude restartován pro opravu.");

                QProcess::startDetached(QApplication::applicationFilePath());
                QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
                return;

            } else{
                // everything OK


                QuestionsDialog::userAgent = loadedJson["user_agent"].toString().toUtf8();

            }
        }

    } else{
        // file with settings not found

        QMessageBox::critical(this, "Chyba", "Soubor s nastavením neexistuje! Program bude restartován pro opravu.");

        QProcess::startDetached(QApplication::applicationFilePath());
        QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
        return;
    }
}

void QuestionsDialog::newQuestion()
{
    // set new question

    QJsonObject questionData = QuestionsDialog::getRandomQuestion();

    if(questionData.isEmpty()){

        return;
    }


    if(questionData["question_media"].toString().isEmpty()){
        ui->question_imageText->setHidden(true);
        ui->question_imageText->clear();
        ui->question_text->setPlainText(questionData["question_text"].toString());
        ui->question_image->clear();
        ui->question_text->setHidden(false);

    } else{
        ui->question_imageText->setHidden(false);
        ui->question_imageText->setPlainText(questionData["question_text"].toString());
        ui->question_image->setText("[zde má být obrázek]");
        ui->question_text->setHidden(true);
    }

    ui->answerA->setPlainText(questionData["correct_text"].toString());
    ui->answerB->setPlainText(questionData["wrong1_text"].toString());
    ui->answerC->setPlainText(questionData["wrong2_text"].toString());

    //ui->plainTextEdit->setStyleSheet("background-image: url(C:/Users/RxiPland/Downloads/e8d.jpg); background-position: center center; background-repeat: no-repeat");
    //ui->plainTextEdit_2->setStyleSheet("background-image: url(C:/Users/RxiPland/Downloads/e8d.jpg); background-position: center center; background-repeat: no-repeat");
    //ui->plainTextEdit_3->setStyleSheet("background-image: url(C:/Users/RxiPland/Downloads/e8d.jpg); background-position: center center; background-repeat: no-repeat");

    //ui->plainTextEdit->setText("ahoj");
    //ui->plainTextEdit->setAlignment(Qt::AlignCenter);


    //QPixmap questionImage("C:/Users/RxiPland/Downloads/0117.jpg");
    //ui->image_label->setPixmap(questionImage.scaled(ui->image_label->width(), ui->image_label->height(), Qt::KeepAspectRatio));
}

QJsonObject QuestionsDialog::getRandomQuestion()
{
    // get random question
    QuestionsDialog::hideWidgets();

    QJsonObject question;

    int randomTopicId = QRandomGenerator::global()->bounded(1,8);

    if(randomTopicId < 1 || randomTopicId > 7){
        // should never happen

        QMessageBox::critical(this, "Nastala chyba", "Nepodařilo se vygenerovat náhodné číslo mezi 1 a 7!");

        QuestionsDialog::hideWidgets(false);
        return question;
    }

    QNetworkRequest request;
    request.setUrl(QUrl(url + QString::number(randomTopicId)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/html; charset=utf-8");
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);
    request.setRawHeader("Referer", (url + QString::number(previousTopicId)).toUtf8());

    QNetworkReply *replyGet = manager.get(request);

    // wait for completed
    QEventLoop loop;
    connect(replyGet, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QNetworkReply::NetworkError error = replyGet->error();

    if(error != QNetworkReply::NoError){
        // any error occured

        QString errortext = replyGet->errorString();
        QMessageBox::critical(this, "Nastala chyba", errortext);

        QuestionsDialog::hideWidgets(false);
        return question;
    }

    QByteArray responseHtml = replyGet->readAll();

    if(responseHtml.isEmpty()){
        // no HTML

        QMessageBox::critical(this, "Nastala chyba", "Server nic nevrátil!");

        QuestionsDialog::hideWidgets(false);
        return question;
    }

    // variables for json
    QString questionText;
    QString questionMedia;
    QString correctText;
    QString correctMedia;
    QString wrong1Text;
    QString wrong1Media;
    QString wrong2Text;
    QString wrong2Media;
    QString questionId;
    QString points;

    QRegularExpression rx;
    QRegularExpressionMatch match;
    QRegularExpressionMatchIterator iterator;

    if(responseHtml.contains("/img/single")){
        // image question and text answers

        // QUESTION TEXT
        rx = QRegularExpression(patternQuestionText);
        questionText = rx.match(responseHtml).captured(1).trimmed();

        // QUESTION MEDIA
        rx = QRegularExpression(patternQuestionMedia);
        questionMedia = rx.match(responseHtml).captured(1).trimmed();

        if(!questionMedia.isEmpty()){
            questionMedia = "https://www.autoskola-testy.cz" + questionMedia;
        }

        // CORRECT ANSWER TEXT
        rx = QRegularExpression(patternCorrect);
        correctText = rx.match(responseHtml).captured(1).trimmed();

        // WRONG ANSWERS TEXT
        rx = QRegularExpression(patternWrong);

        iterator = rx.globalMatch(responseHtml);

        match = iterator.next();
        wrong1Text = match.captured(1).trimmed();
        match = iterator.next();
        wrong2Text = match.captured(1).trimmed();


    } else if(responseHtml.contains("/img/tripple")){
        // text question and image answers

        // QUESTION TEXT
        rx = QRegularExpression(patternQuestionText);
        questionText = rx.match(responseHtml).captured(1).trimmed();

        // CORRECT MEDIA
        rx = QRegularExpression(patternCorrect);
        correctMedia = rx.match(responseHtml).captured(1).trimmed();

        if(!correctMedia.isEmpty()){
            correctMedia.replace("<img src=\"", "");
            correctMedia.replace("\">", "");

            correctMedia = "https://www.autoskola-testy.cz" + correctMedia;
        }

        // WRONG MEDIAS
        rx = QRegularExpression(patternWrong);
        iterator = rx.globalMatch(responseHtml);

        match = iterator.next();
        wrong1Media = match.captured(1).trimmed();

        if(!wrong1Media.isEmpty()){
            wrong1Media.replace("<img src=\"", "");
            wrong1Media.replace("\">", "");

            wrong1Media = "https://www.autoskola-testy.cz" + wrong1Media;
        }

        match = iterator.next();
        wrong2Media = match.captured(1).trimmed();

        if(!wrong2Media.isEmpty()){
            wrong2Media.replace("<img src=\"", "");
            wrong2Media.replace("\">", "");

            wrong2Media = "https://www.autoskola-testy.cz" + wrong2Media;
        }



    } else{
        // text question and text answers

        // QUESTION TEXT
        rx = QRegularExpression(patternQuestionText);
        questionText = rx.match(responseHtml).captured(1).trimmed();

        // CORRECT ANSWER TEXT
        rx = QRegularExpression(patternCorrect);
        correctText = rx.match(responseHtml).captured(1).trimmed();

        // WRONG ANSWERS TEXT
        rx = QRegularExpression(patternWrong);

        iterator = rx.globalMatch(responseHtml);

        match = iterator.next();
        wrong1Text = match.captured(1).trimmed();
        match = iterator.next();
        wrong2Text = match.captured(1).trimmed();

    }

    // QUESTION ID
    rx = QRegularExpression(patternQuestionId);
    questionId = rx.match(responseHtml).captured(1).trimmed();

    // POINTS
    rx = QRegularExpression(patternPoints);
    points = rx.match(responseHtml).captured(1).trimmed();

    // make json
    question["question_text"] = questionText;
    question["question_media"] = questionMedia;
    question["correct_text"] = correctText;
    question["correct_media"] = correctMedia;
    question["wrong1_text"] = wrong1Text;
    question["wrong1_media"] = wrong1Media;
    question["wrong2_text"] = wrong2Text;
    question["wrong2_media"] = wrong2Media;
    question["question_id"] = questionId;
    question["points"] = points;


    QuestionsDialog::previousTopicId = randomTopicId;
    QuestionsDialog::hideWidgets(false);

    return question;
}


void QuestionsDialog::on_answerA_clicked()
{
    qInfo() << "answer A";

    // if correct
    QTimer::singleShot(100, this, &QuestionsDialog::newQuestion);
}


void QuestionsDialog::on_answerB_clicked()
{
    qInfo() << "answer B";

    // if correct
    QTimer::singleShot(100, this, &QuestionsDialog::newQuestion);
}


void QuestionsDialog::on_answerC_clicked()
{
    qInfo() << "answer C";

    // if correct
    QTimer::singleShot(100, this, &QuestionsDialog::newQuestion);
}

