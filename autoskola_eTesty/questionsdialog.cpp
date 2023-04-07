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
#include <QElapsedTimer>


QuestionsDialog::QuestionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionsDialog)
{
    ui->setupUi(this);

    ui->question_image->setAlignment(Qt::AlignCenter);
    ui->label_5->setHidden(true);

    this->show();
    width = ui->question_text->width();
    height = ui->question_text->height()+(width/8);

    ui->question_image->setFixedSize(width, height);

    elapsedTime.restart();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QuestionsDialog::updateTimeLabel);
    timer->start(100);
}


QuestionsDialog::~QuestionsDialog()
{
    delete ui;
}

void QuestionsDialog::closeEvent(QCloseEvent *bar)
{
    // before window close

    QDir tempDirectory(QDir::currentPath() + "/Data/Temp");
    tempDirectory.removeRecursively();

    if(bar != nullptr){
        bar->accept();
    }
}

void QuestionsDialog::updateTimeLabel()
{
    QTime time(0,0,0,0);
    time = time.addMSecs(elapsedTime.elapsed());

    if(!ui->pushButton->text().contains("Nová otázka")){
        ui->label_4->setText(time.toString("hh:mm:ss"));
    }
}

QStringList QuestionsDialog::getQuestionsUrls(int topicId)
{
    // get questions urls based on topic id (1-7)

    QStringList foundUrls = QStringList();

    if(topicId < 1 || topicId > 7){
        // should never happen

        QMessageBox::critical(this, "Nastala chyba", "Číslo okruhu musí být mezi 1 a 7!");

        QuestionsDialog::hideWidgets(false);
        return QStringList();
    }


    QNetworkRequest request;
    request.setUrl(QUrl(urlTopic + QString::number(topicId)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/html; charset=utf-8");
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);
    request.setRawHeader("Referer", "https://www.autoskola-testy.cz/prohlizeni_otazek.php");

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
        return QStringList();
    }


    QByteArray responseHtml = replyGet->readAll();

    if(responseHtml.isEmpty()){
        // no HTML returned

        QMessageBox::critical(this, "Nastala chyba", "Server nic nevrátil!");

        QuestionsDialog::hideWidgets(false);
        return QStringList();
    }


    QRegularExpression rx = QRegularExpression(patternQuestionsUrls);
    QRegularExpressionMatchIterator iterator = rx.globalMatch(responseHtml);

    while (iterator.hasNext()){
        QRegularExpressionMatch match = iterator.next();
        foundUrls.append(match.captured(2).trimmed());
    }

    return foundUrls;
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

    ui->checkBox->setHidden(hide);

    if((correctNum + wrongNum) > 0){
        ui->label_5->setHidden(hide);
    }

    ui->question_imageText->setHidden(hide);
    ui->question_text->setHidden(hide);
    ui->question_image->setHidden(hide);

    ui->pushButton->setHidden(hide);
    ui->pushButton_2->setHidden(hide);
}

void QuestionsDialog::disableWidgets(bool disable)
{
    // disable widgets

    ui->answerA->setDisabled(disable);
    ui->answerB->setDisabled(disable);
    ui->answerC->setDisabled(disable);

    ui->question_imageText->setDisabled(disable);
    ui->question_text->setDisabled(disable);
    ui->question_image->setDisabled(disable);

    ui->pushButton->setDisabled(disable);
    ui->pushButton_2->setDisabled(disable);

    ui->checkBox->setDisabled(disable);
}

void QuestionsDialog::correct()
{
    // increase correct number in stats file

    if(wrongLock){
        QuestionsDialog::wrongLock = false;
        return;
    }

    QuestionsDialog::correctNum += 1;

    if(correctNum == (correctNum + wrongNum)){
        ui->label_5->setText("Úspěšnost: 100% " + QString("(%1 z %2)").arg(QString::number(correctNum), QString::number(correctNum + wrongNum)));

    } else{
        ui->label_5->setText(QString("Úspěšnost: %1").arg((qint64)((float)QuestionsDialog::correctNum/(((float)(correctNum + wrongNum))/100))) + "% " + QString("(%1 z %2)").arg(QString::number(correctNum), QString::number(correctNum + wrongNum)));
    }
    ui->label_5->setHidden(false);

    QFile statsFile(QDir::currentPath() + "/Data/stats.json");

    if (statsFile.exists()){
        statsFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QByteArray fileContent = statsFile.readAll();
        statsFile.close();


        if(!fileContent.isEmpty()){

            QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

            if(!loadedJson.isEmpty()){
                // everything OK

                qint64 correctNumHistory = loadedJson["correct"].toInteger();
                qint64 averageTime = loadedJson["question_average_time"].toInteger();
                loadedJson["correct"] = correctNumHistory + 1;

                if(averageTime == 0){
                    loadedJson["question_average_time"] = elapsedTime.elapsed()/1000;

                } else{
                    loadedJson["question_average_time"] = (averageTime + (elapsedTime.elapsed()/1000))/2;
                }

                QJsonDocument docData(loadedJson);

                statsFile.open(QIODevice::WriteOnly | QIODevice::Text);
                statsFile.write(docData.toJson());
                statsFile.close();
            }
        }

    } else{
        return;
    }
}

void QuestionsDialog::wrong()
{
    // increase wrong number in stats file

    if(!wrongLock){
        QuestionsDialog::wrongLock = true;
        QuestionsDialog::wrongNum += 1;

        if(correctNum == 0){
            ui->label_5->setText(QString("Úspěšnost: 0% ") + QString("(%1 z %2)").arg(QString::number(correctNum), QString::number(correctNum + wrongNum)));
        } else{

            if(correctNum == (correctNum + wrongNum)){
                ui->label_5->setText("Úspěšnost: 100% " + QString("(%1 z %2)").arg(QString::number(correctNum), QString::number(correctNum + wrongNum)));

            } else{
                ui->label_5->setText(QString("Úspěšnost: %1").arg((qint64)((float)QuestionsDialog::correctNum/(((float)(correctNum + wrongNum))/100))) + "% " + QString("(%1 z %2)").arg(QString::number(correctNum), QString::number(correctNum + wrongNum)));
            }
        }
        ui->label_5->setHidden(false);


        QFile statsFile(QDir::currentPath() + "/Data/stats.json");

        if (statsFile.exists()){
            statsFile.open(QIODevice::ReadOnly | QIODevice::Text);

            QByteArray fileContent = statsFile.readAll();
            statsFile.close();


            if(!fileContent.isEmpty()){

                QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

                if(!loadedJson.isEmpty()){
                    // everything OK

                    qint64 wrongNumHistory = loadedJson["wrong"].toInteger();
                    loadedJson["wrong"] = wrongNumHistory + 1;

                    QJsonDocument docData(loadedJson);

                    statsFile.open(QIODevice::WriteOnly | QIODevice::Text);
                    statsFile.write(docData.toJson());
                    statsFile.close();
                }
            }
        }
    }

}

void QuestionsDialog::loadSettings()
{
    // load settings from file

    ui->checkBox->setChecked(QuestionsDialog::automaticNewQuestion);

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
                QuestionsDialog::waitIntervalMs = loadedJson["waiting_interval_miliseconds"].toInteger();
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

void QuestionsDialog::loadQuestions()
{
    // load all questions urls

    int i;
    for(i=1; i<8; i++){
        QuestionsDialog::topicsQuestionsUrls.append(QuestionsDialog::getQuestionsUrls(i));
    }

}

void QuestionsDialog::newQuestion()
{
    // set new question

    ui->label_4->clear();
    ui->pushButton->setText("Přeskočit");

    QJsonObject questionData = QuestionsDialog::getRandomQuestion();

    if(questionData.isEmpty()){

        return;
    }

    QuestionsDialog::correctLetter = questionData["letter_correct"].toString();
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
        !questionMedia.isEmpty() &&
        correctText.isEmpty() &&
        !correctMedia.isEmpty() &&
        wrong1Text.isEmpty() &&
        !wrong1Media.isEmpty()
    ){
        questionType = 4;

    } else if (
        !questionText.isEmpty() &&
        questionMedia.isEmpty() &&
        correctText.isEmpty() &&
        !correctMedia.isEmpty() &&
        wrong1Text.isEmpty() &&
        !wrong1Media.isEmpty()
    ){
        questionType = 3;

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
        !correctText.isEmpty() &&
        correctMedia.isEmpty() &&
        !wrong1Text.isEmpty() &&
        wrong1Media.isEmpty()
    ){
        questionType = 1;

    } else{
        // an unknown error occured

        QFile logFile = QFile(QDir::currentPath() + "/logs.txt");
        QJsonDocument docData(questionData);

        logFile.open(QIODevice::WriteOnly | QIODevice::Append);
        logFile.write(docData.toJson());
        logFile.write("\n\n");
        logFile.close();

        QMessageBox::critical(this, "Chyba", "Nastala neznámá chyba! Výstup byl uložen do log souboru");
        return;
    }


    ui->answerA->clear();
    ui->answerB->clear();
    ui->answerC->clear();

    ui->answerA->setStyleSheet("");
    ui->answerB->setStyleSheet("");
    ui->answerC->setStyleSheet("");

    ui->question_imageText->clear();
    ui->question_image->clear();
    ui->question_text->clear();

    ui->question_imageText->setStyleSheet("");
    ui->question_image->setStyleSheet("");
    ui->question_text->setStyleSheet("");

    ui->label->setStyleSheet("");
    ui->label_2->setStyleSheet("");
    ui->label_3->setStyleSheet("");


    if(questionType == 1){
        QuestionsDialog::hideWidgets();

        ui->question_imageText->setHidden(true);
        ui->question_image->setHidden(true);

        ui->question_text->setPlainText(questionText);
        ui->question_text->setHidden(false);

        if(correctLetter == 'A'){

            if(!correctText.isEmpty()){
                ui->answerA->setPlainText(correctText);
                ui->answerA->setHidden(false);
                ui->label->setHidden(false);

            } else{
                ui->answerA->setHidden(true);
                ui->label->setHidden(true);
            }

            if(!wrong1Text.isEmpty()){
                ui->answerB->setPlainText(wrong1Text);
                ui->answerB->setHidden(false);
                ui->label_2->setHidden(false);

            } else{
                ui->answerB->setHidden(true);
                ui->label_2->setHidden(true);
            }

            if(!wrong2Text.isEmpty()){
                ui->answerC->setPlainText(wrong2Text);
                ui->answerC->setHidden(false);
                ui->label_3->setHidden(false);

            } else{
                ui->answerC->setHidden(true);
                ui->label_3->setHidden(true);
            }

        } else if(correctLetter == 'B'){

            if(!correctText.isEmpty()){
                ui->answerB->setPlainText(correctText);
                ui->answerB->setHidden(false);
                ui->label_2->setHidden(false);

            } else{
                ui->answerB->setHidden(true);
                ui->label_2->setHidden(true);
            }

            if(!wrong1Text.isEmpty()){
                ui->answerA->setPlainText(wrong1Text);
                ui->answerA->setHidden(false);
                ui->label->setHidden(false);

            } else{
                ui->answerA->setHidden(true);
                ui->label->setHidden(true);
            }

            if(!wrong2Text.isEmpty()){
                ui->answerC->setPlainText(wrong2Text);
                ui->answerC->setHidden(false);
                ui->label_3->setHidden(false);

            } else{
                ui->answerC->setHidden(true);
                ui->label_3->setHidden(true);
            }

        } else if(correctLetter == 'C'){

            if(!correctText.isEmpty()){
                ui->answerC->setPlainText(correctText);
                ui->answerC->setHidden(false);
                ui->label_3->setHidden(false);

            } else{
                ui->answerC->setHidden(true);
                ui->label_3->setHidden(true);
            }

            if(!wrong1Text.isEmpty()){
                ui->answerA->setPlainText(wrong1Text);
                ui->answerA->setHidden(false);
                ui->label->setHidden(false);

            } else{
                ui->answerA->setHidden(true);
                ui->label->setHidden(true);
            }

            if(!wrong2Text.isEmpty()){
                ui->answerB->setPlainText(wrong2Text);
                ui->answerB->setHidden(false);
                ui->label_2->setHidden(false);

            } else{
                ui->answerB->setHidden(true);
                ui->label_2->setHidden(true);
            }
        }


    } else if(questionType == 2){
        QuestionsDialog::hideWidgets();
        QuestionsDialog::questionImagePath = QString();

        if(questionMedia.contains(".mp4")){
            ui->question_image->setText("Stahuji video");
            ui->question_image->setHidden(false);

        } else{
            ui->question_image->setText("Načítám otázku");
            ui->question_image->setHidden(false);
        }

        QuestionsDialog::questionImagePath = downloadFile(questionMedia, QString::number(questionTopicId), "1");

        if(!questionImagePath.isEmpty() && !questionImagePath.contains(".mp4")){
            QPixmap *questionImage = new QPixmap(questionImagePath);
            ui->question_image->clear();
            ui->question_image->setPixmap(questionImage->scaled(width, height, Qt::KeepAspectRatio));
            delete(questionImage);

        } else{
            ui->question_image->setText("Spustit video");
            ui->question_image->setStyleSheet("color: blue; text-decoration: underline;");
        }
        ui->question_image->setHidden(false);

        ui->question_imageText->setPlainText(questionText);
        ui->question_imageText->setHidden(false);

        ui->question_text->setHidden(true);

        if(correctLetter == 'A'){

            if(!correctText.isEmpty()){
                ui->answerA->setPlainText(correctText);
                ui->answerA->setHidden(false);
                ui->label->setHidden(false);

            } else{
                ui->answerA->setHidden(true);
                ui->label->setHidden(true);
            }

            if(!wrong1Text.isEmpty()){
                ui->answerB->setPlainText(wrong1Text);
                ui->answerB->setHidden(false);
                ui->label_2->setHidden(false);

            } else{
                ui->answerB->setHidden(true);
                ui->label_2->setHidden(true);
            }

            if(!wrong2Text.isEmpty()){
                ui->answerC->setPlainText(wrong2Text);
                ui->answerC->setHidden(false);
                ui->label_3->setHidden(false);

            } else{
                ui->answerC->setHidden(true);
                ui->label_3->setHidden(true);
            }

        } else if(correctLetter == 'B'){

            if(!correctText.isEmpty()){
                ui->answerB->setPlainText(correctText);
                ui->answerB->setHidden(false);
                ui->label_2->setHidden(false);

            } else{
                ui->answerB->setHidden(true);
                ui->label_2->setHidden(true);
            }

            if(!wrong1Text.isEmpty()){
                ui->answerA->setPlainText(wrong1Text);
                ui->answerA->setHidden(false);
                ui->label->setHidden(false);

            } else{
                ui->answerA->setHidden(true);
                ui->label->setHidden(true);
            }

            if(!wrong2Text.isEmpty()){
                ui->answerC->setPlainText(wrong2Text);
                ui->answerC->setHidden(false);
                ui->label_3->setHidden(false);

            } else{
                ui->answerC->setHidden(true);
                ui->label_3->setHidden(true);
            }

        } else if(correctLetter == 'C'){

            if(!correctText.isEmpty()){
                ui->answerC->setPlainText(correctText);
                ui->answerC->setHidden(false);
                ui->label_3->setHidden(false);

            } else{
                ui->answerC->setHidden(true);
                ui->label_3->setHidden(true);
            }

            if(!wrong1Text.isEmpty()){
                ui->answerA->setPlainText(wrong1Text);
                ui->answerA->setHidden(false);
                ui->label->setHidden(false);

            } else{
                ui->answerA->setHidden(true);
                ui->label->setHidden(true);
            }

            if(!wrong2Text.isEmpty()){
                ui->answerB->setPlainText(wrong2Text);
                ui->answerB->setHidden(false);
                ui->label_2->setHidden(false);

            } else{
                ui->answerB->setHidden(true);
                ui->label_2->setHidden(true);
            }
        }


    } else if(questionType == 3){
        QuestionsDialog::hideWidgets();

        ui->question_image->setText("Načítám otázku");
        ui->question_image->setHidden(false);

        // download images
        correctMedia = downloadFile(correctMedia, QString::number(questionTopicId), "1");
        wrong1Media = downloadFile(wrong1Media, QString::number(questionTopicId), "2");
        wrong2Media = downloadFile(wrong2Media, QString::number(questionTopicId), "3");

        ui->question_image->setHidden(true);
        ui->question_imageText->setHidden(true);

        ui->question_text->setPlainText(questionText);
        ui->question_text->setHidden(false);

        if(correctLetter == 'A'){

            if(!correctMedia.isEmpty()){
                ui->answerA->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(correctMedia));
                ui->answerA->setHidden(false);
                ui->label->setHidden(false);

            } else{
                ui->answerA->setHidden(true);
                ui->label->setHidden(true);
            }

            if(!wrong1Media.isEmpty()){
                ui->answerB->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(wrong1Media));
                ui->answerB->setHidden(false);
                ui->label_2->setHidden(false);

            } else{
                ui->answerB->setHidden(true);
                ui->label_2->setHidden(true);
            }

            if(!wrong2Media.isEmpty()){
                ui->answerC->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(wrong2Media));
                ui->answerC->setHidden(false);
                ui->label_3->setHidden(false);
            } else{
                ui->answerC->setHidden(true);
                ui->label_3->setHidden(true);
            }

        } else if(correctLetter == 'B'){

            if(!correctMedia.isEmpty()){
                ui->answerB->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(correctMedia));
                ui->answerB->setHidden(false);
                ui->label_2->setHidden(false);

            } else{
                ui->answerB->setHidden(true);
                ui->label_2->setHidden(true);
            }

            if(!wrong1Media.isEmpty()){
                ui->answerA->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(wrong1Media));
                ui->answerA->setHidden(false);
                ui->label->setHidden(false);

            } else{
                ui->answerA->setHidden(true);
                ui->label->setHidden(true);
            }

            if(!wrong2Media.isEmpty()){
                ui->answerC->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(wrong2Media));
                ui->answerC->setHidden(false);
                ui->label_3->setHidden(false);
            } else{
                ui->answerC->setHidden(true);
                ui->label_3->setHidden(true);
            }

        } else if(correctLetter == 'C'){

            if(!correctMedia.isEmpty()){
                ui->answerC->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(correctMedia));
                ui->answerC->setHidden(false);
                ui->label_3->setHidden(false);

            } else{
                ui->answerC->setHidden(true);
                ui->label_3->setHidden(true);
            }

            if(!wrong1Media.isEmpty()){
                ui->answerA->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(wrong1Media));
                ui->answerA->setHidden(false);
                ui->label->setHidden(false);

            } else{
                ui->answerA->setHidden(true);
                ui->label->setHidden(true);
            }

            if(!wrong2Media.isEmpty()){
                ui->answerB->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(wrong2Media));
                ui->answerB->setHidden(false);
                ui->label_2->setHidden(false);
            } else{
                ui->answerB->setHidden(true);
                ui->label_2->setHidden(true);
            }

        }


    } else if(questionType == 4){
        QuestionsDialog::hideWidgets();

        QuestionsDialog::questionImagePath = QString();

        if(questionMedia.contains(".mp4")){
            ui->question_image->setText("Stahuji video");
            ui->question_image->setHidden(false);
        } else{
            ui->question_image->setText("Načítám otázku");
            ui->question_image->setHidden(false);
        }

        // download images
        QuestionsDialog::questionImagePath = downloadFile(questionMedia, QString::number(questionTopicId), "1");
        correctMedia = downloadFile(correctMedia, QString::number(questionTopicId), "2");
        wrong1Media = downloadFile(wrong1Media, QString::number(questionTopicId), "3");
        wrong2Media = downloadFile(wrong2Media, QString::number(questionTopicId), "4");


        if(!questionImagePath.isEmpty() && !questionImagePath.contains(".mp4")){
            QPixmap *questionImage = new QPixmap(questionImagePath);
            ui->question_image->clear();
            ui->question_image->setPixmap(questionImage->scaled(width, height, Qt::KeepAspectRatio));
            delete(questionImage);

        } else{
            ui->question_image->setText("Spustit video");
            ui->question_image->setStyleSheet("color: blue; text-decoration: underline;");
        }

        ui->question_imageText->setPlainText(questionText);

        ui->question_image->setHidden(false);
        ui->question_text->setHidden(true);
        ui->question_imageText->setHidden(false);

        if(correctLetter == 'A'){

            if(!correctMedia.isEmpty()){
                ui->answerA->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(correctMedia));
                ui->answerA->setHidden(false);
                ui->label->setHidden(false);
            } else{
                ui->answerA->setHidden(true);
                ui->label->setHidden(true);
            }

            if(!wrong1Media.isEmpty()){
                ui->answerB->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(wrong1Media));
                ui->answerB->setHidden(false);
                ui->label_2->setHidden(false);
            } else{
                ui->answerB->setHidden(true);
                ui->label_2->setHidden(true);
            }

            if(!wrong2Media.isEmpty()){
                ui->answerC->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(wrong2Media));
                ui->answerC->setHidden(false);
                ui->label_3->setHidden(false);
            } else{
                ui->answerC->setHidden(true);
                ui->label_3->setHidden(true);
            }

        } else if (correctLetter == 'B'){

            if(!correctMedia.isEmpty()){
                ui->answerB->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(correctMedia));
                ui->answerB->setHidden(false);
                ui->label_2->setHidden(false);
            } else{
                ui->answerB->setHidden(true);
                ui->label_2->setHidden(true);
            }

            if(!wrong1Media.isEmpty()){
                ui->answerA->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(wrong1Media));
                ui->answerA->setHidden(false);
                ui->label->setHidden(false);
            } else{
                ui->answerA->setHidden(true);
                ui->label->setHidden(true);
            }

            if(!wrong2Media.isEmpty()){
                ui->answerC->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(wrong2Media));
                ui->answerC->setHidden(false);
                ui->label_3->setHidden(false);
            } else{
                ui->answerC->setHidden(true);
                ui->label_3->setHidden(true);
            }

        } else if (correctLetter == 'C'){

            if(!correctMedia.isEmpty()){
                ui->answerC->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(correctMedia));
                ui->answerC->setHidden(false);
                ui->label_3->setHidden(false);
            } else{
                ui->answerC->setHidden(true);
                ui->label_3->setHidden(true);
            }

            if(!wrong1Media.isEmpty()){
                ui->answerA->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(wrong1Media));
                ui->answerA->setHidden(false);
                ui->label->setHidden(false);
            } else{
                ui->answerA->setHidden(true);
                ui->label->setHidden(true);
            }

            if(!wrong2Media.isEmpty()){
                ui->answerB->setStyleSheet(QString("background-image: url(%1); background-position: center center; background-repeat: no-repeat").arg(wrong2Media));
                ui->answerB->setHidden(false);
                ui->label_2->setHidden(false);
            } else{
                ui->answerB->setHidden(true);
                ui->label_2->setHidden(true);
            }
        }


    } else{
        // an unknown error occured

        return;
    }

    elapsedTime.restart();
    ui->label_4->setHidden(false);

    if((correctNum + wrongNum) > 1){
        ui->label_5->setHidden(false);
    }

    ui->pushButton->setHidden(false);
    ui->pushButton_2->setHidden(false);
    ui->checkBox->setHidden(false);

    ui->question_image->setAlignment(Qt::AlignCenter);


    QuestionsDialog::disableWidgets(false);
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
        return QJsonObject();
    }


    while(randomTopicId == QuestionsDialog::previousQuestionTopic){
        // generate new topic number

        randomTopicId = QRandomGenerator::global()->bounded(1,8);
    }

    QuestionsDialog::previousQuestionTopic = randomTopicId;

    int k = 0;

    // if list of all questions will be empty
    for(k=0; k<8 && topicsQuestionsUrls[k].isEmpty(); k++){

        if(k == 7){
            QMessageBox::critical(this, "Gratulace", "Všechny otázky byly vyčerpány! Restartujte program pro znovunačtení otázek.");

            QuestionsDialog::hideWidgets(true);
            return QJsonObject();

        } else{
            randomTopicId = k+1;
        }
    }


    int randomIndex;
    QString url;

    randomIndex = QRandomGenerator::global()->bounded(0, topicsQuestionsUrls[randomTopicId-1].length());
    url = "https://www.autoskola-testy.cz/prohlizeni_otazek.php" + topicsQuestionsUrls[randomTopicId-1][randomIndex];

    if(url.isEmpty()){
        QMessageBox::critical(this, "Nastala chyba", "Nepodařilo se získat URL adresu!");

        QuestionsDialog::hideWidgets(false);
        return QJsonObject();
    }

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/html; charset=utf-8");
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);

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
        return QJsonObject();
    }

    QuestionsDialog::questionCount += 1;

    QByteArray responseHtml = replyGet->readAll();


    if(responseHtml.isEmpty()){
        // no HTML returned

        QMessageBox::critical(this, "Nastala chyba", "Server nic nevrátil!");

        QuestionsDialog::hideWidgets(false);
        return QJsonObject();
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

    // regex search

    if(responseHtml.contains("/img/single") && responseHtml.contains("/img/tripple")){
        // image question and image answers

        // QUESTION TEXT
        rx = QRegularExpression(patternQuestionText);
        questionText = rx.match(responseHtml).captured(1).trimmed();

        // QUESTION MEDIA
        rx = QRegularExpression(patternQuestionMedia);
        questionMedia = rx.match(responseHtml).captured(1).trimmed();

        if(!questionMedia.isEmpty()){
            questionMedia = "https://www.autoskola-testy.cz" + questionMedia;
        }

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

        if(iterator.hasNext()){
            match = iterator.next();
            wrong1Media = match.captured(1).trimmed();

            if(!wrong1Media.isEmpty()){
                wrong1Media.replace("<img src=\"", "");
                wrong1Media.replace("\">", "");

                wrong1Media = "https://www.autoskola-testy.cz" + wrong1Media;
            }

        } else{
            wrong1Media = QString();
        }


        if(iterator.hasNext()){
            match = iterator.next();
            wrong2Media = match.captured(1).trimmed();

            if(!wrong2Media.isEmpty()){
                wrong2Media.replace("<img src=\"", "");
                wrong2Media.replace("\">", "");

                wrong2Media = "https://www.autoskola-testy.cz" + wrong2Media;
            }

        } else{
            wrong2Media = QString();
        }

    } else if(responseHtml.contains("/img/single")){
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

        if(iterator.hasNext()){
            match = iterator.next();
            wrong1Text = match.captured(1).trimmed();

        } else{
            wrong1Text = QString();
        }


        if(iterator.hasNext()){
            match = iterator.next();
            wrong2Text = match.captured(1).trimmed();

        } else{
            wrong2Text = QString();
        }


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

        if(iterator.hasNext()){
            match = iterator.next();
            wrong1Media = match.captured(1).trimmed();

            if(!wrong1Media.isEmpty()){
                wrong1Media.replace("<img src=\"", "");
                wrong1Media.replace("\">", "");

                wrong1Media = "https://www.autoskola-testy.cz" + wrong1Media;
            }

        } else{
            wrong1Media = QString();
        }


        if(iterator.hasNext()){
            match = iterator.next();
            wrong2Media = match.captured(1).trimmed();

            if(!wrong2Media.isEmpty()){
                wrong2Media.replace("<img src=\"", "");
                wrong2Media.replace("\">", "");

                wrong2Media = "https://www.autoskola-testy.cz" + wrong2Media;
            }

        } else{
            wrong2Media = QString();
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

        if(iterator.hasNext()){
            match = iterator.next();
            wrong1Text = match.captured(1).trimmed();

        } else{
            wrong1Text = QString();
        }


        if(iterator.hasNext()){
            match = iterator.next();
            wrong2Text = match.captured(1).trimmed();

        } else{
            wrong2Text = QString();
        }

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


    QStringList indexes;
    int correctIndex = responseHtml.indexOf("answer otazka_spravne");
    int wrong1Index = responseHtml.indexOf("answer otazka_spatne");
    int wrong2Index = responseHtml.indexOf("answer otazka_spatne", wrong1Index+1);

    if(correctIndex != -1){
        indexes.append(QString::number(correctIndex));

    } else{
        QMessageBox::critical(this, "Nastala chyba", "Nepodařilo se vyhledat správnou odpověď v HTML!");

        replyGet->deleteLater();
        responseHtml.clear();

        return QJsonObject();
    }

    if(wrong1Index != -1){
        indexes.append(QString::number(wrong1Index));
    }

    if(wrong2Index != -1){
        indexes.append(QString::number(wrong2Index));
    }

    indexes.sort();


    int i;

    // find letter for correct answer
    for(i=0; i<indexes.length(); i++){

        if (indexes[i] == QString::number(correctIndex)){

            switch(i){
                case 0:
                    question["letter_correct"] = "A";
                    break;
                case 1:
                    question["letter_correct"] = "B";
                    break;
                case 2:
                    question["letter_correct"] = "C";
                    break;

                default:
                    question["letter_correct"];
                    break;
            }

            break;
        }
    }

    QuestionsDialog::hideWidgets(false);

    replyGet->deleteLater();
    responseHtml.clear();


    QuestionsDialog::topicsQuestionsUrls[randomTopicId-1].removeAt(randomIndex);

    return question;
}

QString QuestionsDialog::downloadFile(QString url, QString topicId, QString fileOrder)
{
    // download image

    if(url.isEmpty() || topicId.isEmpty() || fileOrder.isEmpty()){
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

    QFile *downloadedFile = new QFile(QDir::currentPath() + "/Data/Temp/" + questionCountStr + '/' + fileOrder + '.' + url.split('.').last());

    downloadedFile->open(QIODevice::WriteOnly);
    downloadedFile->write(replyGet->readAll());
    downloadedFile->close();

    QString fileName = downloadedFile->fileName();

    downloadedFile->deleteLater();
    replyGet->deleteLater();

    return fileName;
}


void QuestionsDialog::on_answerA_clicked()
{
    // if correct
    if(QuestionsDialog::correctLetter == "A"){

        QuestionsDialog::disableWidgets(true);
        ui->label->setStyleSheet("background-color: green");

        QuestionsDialog::correct();

        if(automaticNewQuestion){
            QTimer::singleShot(QuestionsDialog::waitIntervalMs, this, &QuestionsDialog::newQuestion);

        } else{
            ui->pushButton->setText(" Nová otázka ");
            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            ui->checkBox->setEnabled(true);
        }

        return;

    } else{
        ui->label->setStyleSheet("background-color: red");

        QuestionsDialog::wrong();
    }
}


void QuestionsDialog::on_answerB_clicked()
{
    // if correct
    if(QuestionsDialog::correctLetter == "B"){

        QuestionsDialog::disableWidgets(true);
        ui->label_2->setStyleSheet("background-color: green");

        QuestionsDialog::correct();

        if(automaticNewQuestion){
            QTimer::singleShot(QuestionsDialog::waitIntervalMs, this, &QuestionsDialog::newQuestion);

        } else{
            ui->pushButton->setText(" Nová otázka ");
            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            ui->checkBox->setEnabled(true);
        }

        return;

    } else{
        ui->label_2->setStyleSheet("background-color: red");

        QuestionsDialog::wrong();
    }
}


void QuestionsDialog::on_answerC_clicked()
{
    // if correct
    if(QuestionsDialog::correctLetter == "C"){

        QuestionsDialog::disableWidgets(true);
        ui->label_3->setStyleSheet("background-color: green");

        QuestionsDialog::correct();

        if(automaticNewQuestion){
            QTimer::singleShot(QuestionsDialog::waitIntervalMs, this, &QuestionsDialog::newQuestion);

        } else{
            ui->pushButton->setText(" Nová otázka ");
            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            ui->checkBox->setEnabled(true);
        }

        return;

    } else{
        ui->label_3->setStyleSheet("background-color: red");

        QuestionsDialog::wrong();
    }

}

void QuestionsDialog::on_question_image_clicked()
{
    // open image/video

    QStringList arguments;
    arguments << "/C";
    arguments << questionImagePath;

    QProcess::startDetached("cmd", arguments);

}

void QuestionsDialog::on_pushButton_clicked()
{
    // skip question

    QuestionsDialog::disableWidgets(true);

    if(QuestionsDialog::correctLetter == "A"){
        ui->label->setStyleSheet("background-color: green");

    } else if(QuestionsDialog::correctLetter == "B"){
        ui->label_2->setStyleSheet("background-color: green");

    } else if(QuestionsDialog::correctLetter == "C"){
        ui->label_3->setStyleSheet("background-color: green");
    }

    if(ui->pushButton->text().contains("Nová otázka")){
        QuestionsDialog::newQuestion();

    } else if (ui->checkBox->isChecked()){
        QTimer::singleShot(QuestionsDialog::waitIntervalMs * 3, this, &QuestionsDialog::newQuestion);

    } else{
        ui->pushButton->setText(" Nová otázka ");
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        ui->checkBox->setEnabled(true);
    }
}

void QuestionsDialog::on_pushButton_2_clicked()
{
    // close window

    QuestionsDialog::exitApp = false;

    this->close();
}

void QuestionsDialog::on_checkBox_clicked()
{
    // automatic new question setting

    QuestionsDialog::automaticNewQuestion = ui->checkBox->isChecked();
}

