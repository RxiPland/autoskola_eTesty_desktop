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

    ui->label->setAlignment(Qt::AlignCenter);
    ui->image_label->setAlignment(Qt::AlignCenter);
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

    ui->plainTextEdit->setHidden(hide);
    ui->plainTextEdit_2->setHidden(hide);
    ui->plainTextEdit_3->setHidden(hide);

    ui->label->setHidden(hide);
    ui->image_label->setHidden(hide);
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

    qInfo() << "new question";

    QJsonObject question = QuestionsDialog::getRandomQuestion();

    if(question.isEmpty()){

        //return;
    }

    ui->plainTextEdit->setStyleSheet("background-image: url(C:/Users/libor/Downloads/e8d.jpg); background-position: center center; background-repeat: no-repeat");
    ui->plainTextEdit_2->setStyleSheet("background-image: url(C:/Users/libor/Downloads/e8d.jpg); background-position: center center; background-repeat: no-repeat");
    ui->plainTextEdit_3->setStyleSheet("background-image: url(C:/Users/libor/Downloads/e8d.jpg); background-position: center center; background-repeat: no-repeat");

    ui->plainTextEdit->setText("ahoj");
    ui->plainTextEdit->setAlignment(Qt::AlignCenter);


    QPixmap questionImage("C:/Users/libor/Downloads/0447.jpg");
    ui->image_label->setPixmap(questionImage.scaled(ui->image_label->width(), ui->image_label->height(), Qt::KeepAspectRatio));
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


    if(responseHtml.contains("/img/single")){
        // image question and text answers

        // QUESTION TEXT
        QRegularExpression rx(patternQuestionText);
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
        QRegularExpressionMatch match;
        rx = QRegularExpression(patternWrong);

        QRegularExpressionMatchIterator iterator = rx.globalMatch(responseHtml);

        match = iterator.next();
        wrong1Text = match.captured(1).trimmed();
        match = iterator.next();
        wrong2Text = match.captured(1).trimmed();

        /*
        qInfo() << questionText;
        qInfo() << questionMedia;
        qInfo() << correctText;
        qInfo() << wrong1Text;
        qInfo() << wrong2Text;
        */


        /*
        question_text: list[str] = re.findall(PATTERN_QUESTION_TEXT, response_html)

        if len(question_text) > 0:
            question_text = question_text[0].strip()
        else:
            question_text = QString()

        question_media: list[str] = re.findall(PATTERN_QUESTION_MEDIA, response_html)

        if len(question_media) > 0:
            question_media = question_media[0].strip()
            question_media = "https://www.autoskola-testy.cz" + question_media
        else:
            question_media = QString()

        correct_text: list[str] = re.findall(PATTERN_CORRECT, response_html)

        if len(correct_text) > 0:
            correct_text = correct_text[0].strip()
        else:
            correct_text = QString()

        // WRONG ANSWER //1 TEXT
        wrong1_text: list[str] = re.findall(PATTERN_WRONG, response_html)

        if len(wrong1_text) > 0:
            wrong1_text = wrong1_text[0].strip()
        else:
            wrong1_text = QString()

        // WRONG ANSWER //2 TEXT
        wrong2_text: list[str] = re.findall(PATTERN_WRONG, response_html)

        if len(wrong2_text) > 1:
            wrong2_text = wrong2_text[1].strip()
        else:
            wrong2_text = QString()

        */

    } else if(responseHtml.contains("/img/triple")){
        // text question and image answers


    } else{
        // text question and text answers
    }


    /*

    elif "/img/tripple/" in response_html:

        // QUESTION TEXT
        question_text: list[str] = re.findall(PATTERN_QUESTION_TEXT, response_html)

        if len(question_text) > 0:
            question_text = question_text[0].strip()
        else:
            question_text = QString()

        // CORRECT ANSWER MEDIA
        correct_media: list[str] = re.findall(PATTERN_CORRECT, response_html)

        if len(correct_media) > 0:
            correct_media: str = correct_media[0].strip()
            correct_media = correct_media.lstrip("<img src=\"")
            correct_media = correct_media.rstrip("\">")
            correct_media = "https://www.autoskola-testy.cz" + correct_media

        else:
            correct_media = QString()

        // WRONG ANSWER //1 MEDIA
        wrong1_media: list[str] = re.findall(PATTERN_WRONG, response_html)

        if len(wrong1_media) > 0:
            wrong1_media: str = wrong1_media[0].strip()
            wrong1_media = wrong1_media.lstrip("<img src=\"")
            wrong1_media = wrong1_media.rstrip("\">")
            wrong1_media = "https://www.autoskola-testy.cz" + wrong1_media

        else:
            wrong1_media = QString()

        // WRONG ANSWER //2 MEDIA
        wrong2_media: list[str] = re.findall(PATTERN_WRONG, response_html)

        if len(wrong2_media) > 1:
            wrong2_media: str = wrong2_media[1].strip()
            wrong2_media = wrong2_media.lstrip("<img src=\"")
            wrong2_media = wrong2_media.rstrip("\">")
            wrong2_media = "https://www.autoskola-testy.cz" + wrong2_media

        else:
            wrong2_media = QString()

    else:

        // QUESTION TEXT
        question_text: list[str] = re.findall(PATTERN_QUESTION_TEXT, response_html)

        if len(question_text) > 0:
            question_text = question_text[0].strip()
        else:
            question_text = QString()

        // CORRECT ANSWER TEXT
        correct_text: list[str] = re.findall(PATTERN_CORRECT, response_html)

        if len(correct_text) > 0:
            correct_text = correct_text[0].strip()
        else:
            correct_text = QString()

        // WRONG ANSWER TEXT //1
        wrong1_text: list[str] = re.findall(PATTERN_WRONG, response_html)

        if len(wrong1_text) > 0:
            wrong1_text = wrong1_text[0].strip()
        else:
            wrong1_text = QString()

        // WRONG ANSWER TEXT //2
        wrong2_text: list[str] = re.findall(PATTERN_WRONG, response_html)

        if len(wrong2_text) > 1:
            wrong2_text = wrong2_text[1].strip()
        else:
            wrong2_text = QString()


        // QUESTION ID
        question_id: list[str] = re.findall(PATTER_QUESTION_ID, response_html)

        if len(question_id) > 0:
            question_id = question_id[0].strip()
        else:
            question_id = QString()

        // POINTS
        points: list[str] = re.findall(PATTER_POINTS, response_html)

        if len(points) > 0:
            points = points[0].strip()
        else:
            points = QString()


    */
    QuestionsDialog::previousTopicId = randomTopicId;
    QuestionsDialog::hideWidgets(false);

    return question;
}


void QuestionsDialog::on_plainTextEdit_clicked()
{
    qInfo() << "answer A";


    // if correct
    QTimer::singleShot(1000, this, &QuestionsDialog::newQuestion);
}

void QuestionsDialog::on_plainTextEdit_2_clicked()
{
    qInfo() << "answer B";

    // if correct
    QTimer::singleShot(1000, this, &QuestionsDialog::newQuestion);
}

void QuestionsDialog::on_plainTextEdit_3_clicked()
{
    qInfo() << "answer C";

    // if correct
    QTimer::singleShot(1000, this, &QuestionsDialog::newQuestion);
}

