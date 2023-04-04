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
    width = ui->question_text->width();
    height = ui->question_text->height()+(width/8);

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

    ui->label->setHidden(hide);
    ui->label_2->setHidden(hide);
    ui->label_3->setHidden(hide);
    ui->label_4->setHidden(hide);

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

    QString questionText = questionData["question_text"].toString();
    QString questionMedia = questionData["question_media"].toString();
    QString correctText = questionData["correct_text"].toString();
    QString correctMedia = questionData["correct_media"].toString();
    QString wrong1Text = questionData["wrong1_text"].toString();
    QString wrong1Media = questionData["wrong1_media"].toString();
    QString wrong2Text = questionData["wrong2_text"].toString();
    QString wrong2Media = questionData["wrong2_media"].toString();

    //QString questionId = questionData["question_id"].toString();
    int questionTopicId = questionData["topic_id"].toInt();
    //QString points = questionData["points"].toString();


    // 0 = error
    // 1 = text question and text answers
    // 2 = image question and text answers
    // 3 = text question and image answers
    // 4 = image question and image answers
    int questionType = 0;

    if(
        !questionText.isEmpty() &&
        questionMedia.isEmpty() &&
        !correctText.isEmpty() &&
        correctMedia.isEmpty() &&
        !wrong1Text.isEmpty() &&
        wrong1Media.isEmpty() &&
        wrong2Media.isEmpty()
    ){
        questionType = 1;

    } else if (
        !questionText.isEmpty() &&
        !questionMedia.isEmpty() &&
        !correctText.isEmpty() &&
        correctMedia.isEmpty() &&
        !wrong1Text.isEmpty() &&
        wrong1Media.isEmpty() &&
        wrong2Media.isEmpty()
    ){
        questionType = 2;

    } else if (
        !questionText.isEmpty() &&
        questionMedia.isEmpty() &&
        correctText.isEmpty() &&
        !correctMedia.isEmpty() &&
        wrong1Text.isEmpty() &&
        !wrong1Media.isEmpty() &&
        wrong2Text.isEmpty() &&
        !wrong2Media.isEmpty()
    ){
        questionType = 3;

    } else{
        qInfo() << "error";
        // write output to log file
    }


    if(questionType == 1){
        hideWidgets();

        ui->question_imageText->setHidden(true);
        ui->question_imageText->clear();

        ui->question_image->setHidden(true);
        ui->question_image->clear();

        ui->question_text->setPlainText(questionText);
        ui->question_text->setHidden(false);

        if(!correctText.isEmpty()){
            ui->answerA->setHidden(false);
            ui->answerA->setPlainText(correctText);
            ui->label->setHidden(false);

        } else{
            ui->answerA->setHidden(true);
            ui->label->setHidden(true);
        }

        if(!wrong1Text.isEmpty()){
            ui->answerB->setHidden(false);
            ui->answerB->setPlainText(wrong1Text);
            ui->label_2->setHidden(false);

        } else{
            ui->answerB->setHidden(true);
            ui->label_2->setHidden(true);
        }

        if(!wrong2Text.isEmpty()){
            ui->answerC->setHidden(false);
            ui->answerC->setPlainText(wrong2Text);
            ui->label_3->setHidden(false);

        } else{
            ui->answerC->setHidden(true);
            ui->label_3->setHidden(true);
        }

    } else if(questionType == 2){
        hideWidgets();

        ui->question_imageText->setPlainText(questionText);
        ui->question_imageText->setHidden(false);

        QString filePath = downloadFile(questionMedia, QString::number(questionTopicId), "1");

        QPixmap questionImage(filePath);
        ui->question_image->setPixmap(questionImage.scaled(width, height, Qt::KeepAspectRatio));
        ui->question_image->setHidden(false);

        ui->question_text->setHidden(true);
        ui->question_text->clear();

        if(!correctText.isEmpty()){
            ui->answerA->setHidden(false);
            ui->answerA->setPlainText(correctText);
            ui->label->setHidden(false);

        } else{
            ui->answerA->setHidden(true);
            ui->label->setHidden(true);
        }

        if(!wrong1Text.isEmpty()){
            ui->answerB->setHidden(false);
            ui->answerB->setPlainText(wrong1Text);
            ui->label_2->setHidden(false);

        } else{
            ui->answerB->setHidden(true);
            ui->label_2->setHidden(true);
        }

        if(!wrong2Text.isEmpty()){
            ui->answerC->setHidden(false);
            ui->answerC->setPlainText(wrong2Text);
            ui->label_3->setHidden(false);

        } else{
            ui->answerC->setHidden(true);
            ui->label_3->setHidden(true);
        }

    } else if(questionType == 3){
        //hideWidgets();

        qInfo() << "type 3";


    } else{
        QMessageBox::critical(this, "Chyba", "Nastala neznámá chyba! Výstup byl uložen do log souboru");
        return;
    }


    /*
    } else{
        ui->question_imageText->setHidden(false);
        ui->question_imageText->setPlainText(questionData["question_text"].toString());
        ui->question_image->setText("[zde má být obrázek]");
        ui->question_text->setHidden(true);
    }

    ui->answerA->setPlainText(questionData["correct_text"].toString());
    ui->answerB->setPlainText(questionData["wrong1_text"].toString());
    ui->answerC->setPlainText(questionData["wrong2_text"].toString());
    */

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
    request.setRawHeader("Referer", (url + QString::number(randomTopicId)).toUtf8());

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

    QuestionsDialog::questionCount += 1;

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
    question["topic_id"] = randomTopicId;
    question["points"] = points;

    QuestionsDialog::hideWidgets(false);

    return question;
}

QString QuestionsDialog::downloadFile(QString url, QString topicId, QString fileOrder)
{
    // download image

    if(url.contains(".mp4")){
        return QString();
    }

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);
    request.setRawHeader("Referer", (url + topicId).toUtf8());

    QNetworkReply *replyGet = manager.get(request);

    // wait for completed
    QEventLoop loop;
    connect(replyGet, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QNetworkReply::NetworkError error = replyGet->error();

    if(error != QNetworkReply::NoError){
        // any error occured

        QString errortext = replyGet->errorString();
        QMessageBox::critical(this, "Nastala chyba při stahování obrázku", errortext);

        QuestionsDialog::hideWidgets(false);
        return QString();
    }

    QString questionCountStr = QString::number(QuestionsDialog::questionCount);

    QDir directory(QDir::currentPath());
    directory.mkpath(QDir::currentPath() + "/Data/Temp/" + questionCountStr);

    QFile downloadedFile(QDir::currentPath() + "/Data/Temp/" + questionCountStr + '/' + fileOrder + '.' + url.split('.').last());

    downloadedFile.open(QIODevice::WriteOnly);
    downloadedFile.write(replyGet->readAll());
    downloadedFile.close();

    QString fileName = downloadedFile.fileName();

    return fileName;
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

