/********************************************************************************
** Form generated from reading UI file 'questionsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUESTIONSDIALOG_H
#define UI_QUESTIONSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "clickabletextedit.h"

QT_BEGIN_NAMESPACE

class Ui_QuestionsDialog
{
public:
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QPlainTextEdit *question_imageText;
    QSpacerItem *verticalSpacer;
    QPlainTextEdit *question_text;
    QLabel *question_image;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    ClickableTextEdit *answerA;
    QSpacerItem *horizontalSpacer;
    ClickableTextEdit *answerB;
    QSpacerItem *horizontalSpacer_2;
    ClickableTextEdit *answerC;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QDialog *QuestionsDialog)
    {
        if (QuestionsDialog->objectName().isEmpty())
            QuestionsDialog->setObjectName("QuestionsDialog");
        QuestionsDialog->resize(854, 577);
        horizontalLayout_2 = new QHBoxLayout(QuestionsDialog);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, 0, -1, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        question_imageText = new QPlainTextEdit(QuestionsDialog);
        question_imageText->setObjectName("question_imageText");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(question_imageText->sizePolicy().hasHeightForWidth());
        question_imageText->setSizePolicy(sizePolicy);
        question_imageText->setMinimumSize(QSize(0, 0));
        question_imageText->setMaximumSize(QSize(16777215, 45));
        question_imageText->setBaseSize(QSize(0, 0));
        QFont font;
        font.setPointSize(11);
        question_imageText->setFont(font);
        question_imageText->setFocusPolicy(Qt::NoFocus);
        question_imageText->setReadOnly(true);

        verticalLayout->addWidget(question_imageText);

        verticalSpacer = new QSpacerItem(20, 8, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        question_text = new QPlainTextEdit(QuestionsDialog);
        question_text->setObjectName("question_text");
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(question_text->sizePolicy().hasHeightForWidth());
        question_text->setSizePolicy(sizePolicy1);
        question_text->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setPointSize(13);
        question_text->setFont(font1);
        question_text->setFocusPolicy(Qt::NoFocus);
        question_text->setReadOnly(true);

        verticalLayout->addWidget(question_text);

        question_image = new QLabel(QuestionsDialog);
        question_image->setObjectName("question_image");

        verticalLayout->addWidget(question_image);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        answerA = new ClickableTextEdit(QuestionsDialog);
        answerA->setObjectName("answerA");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(answerA->sizePolicy().hasHeightForWidth());
        answerA->setSizePolicy(sizePolicy2);
        answerA->setMinimumSize(QSize(0, 0));
        answerA->setMaximumSize(QSize(16777215, 200));
        answerA->setFont(font);
        answerA->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        answerA->setFocusPolicy(Qt::NoFocus);
        answerA->setReadOnly(true);

        horizontalLayout->addWidget(answerA);

        horizontalSpacer = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        answerB = new ClickableTextEdit(QuestionsDialog);
        answerB->setObjectName("answerB");
        sizePolicy2.setHeightForWidth(answerB->sizePolicy().hasHeightForWidth());
        answerB->setSizePolicy(sizePolicy2);
        answerB->setMinimumSize(QSize(0, 0));
        answerB->setMaximumSize(QSize(16777215, 200));
        answerB->setFont(font);
        answerB->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        answerB->setFocusPolicy(Qt::NoFocus);
        answerB->setReadOnly(true);

        horizontalLayout->addWidget(answerB);

        horizontalSpacer_2 = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        answerC = new ClickableTextEdit(QuestionsDialog);
        answerC->setObjectName("answerC");
        sizePolicy2.setHeightForWidth(answerC->sizePolicy().hasHeightForWidth());
        answerC->setSizePolicy(sizePolicy2);
        answerC->setMaximumSize(QSize(16777215, 200));
        answerC->setFont(font);
        answerC->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        answerC->setFocusPolicy(Qt::NoFocus);
        answerC->setReadOnly(true);

        horizontalLayout->addWidget(answerC);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_4);


        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        retranslateUi(QuestionsDialog);

        QMetaObject::connectSlotsByName(QuestionsDialog);
    } // setupUi

    void retranslateUi(QDialog *QuestionsDialog)
    {
        QuestionsDialog->setWindowTitle(QCoreApplication::translate("QuestionsDialog", "Dialog", nullptr));
        question_image->setText(QCoreApplication::translate("QuestionsDialog", "image", nullptr));
        answerA->setPlainText(QString());
    } // retranslateUi

};

namespace Ui {
    class QuestionsDialog: public Ui_QuestionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUESTIONSDIALOG_H
