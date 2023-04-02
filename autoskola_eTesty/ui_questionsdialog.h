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
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QLabel *image_label;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    ClickableTextEdit *plainTextEdit;
    QSpacerItem *horizontalSpacer;
    ClickableTextEdit *plainTextEdit_2;
    QSpacerItem *horizontalSpacer_2;
    ClickableTextEdit *plainTextEdit_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QDialog *QuestionsDialog)
    {
        if (QuestionsDialog->objectName().isEmpty())
            QuestionsDialog->setObjectName("QuestionsDialog");
        QuestionsDialog->resize(854, 612);
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

        label = new QLabel(QuestionsDialog);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(11);
        label->setFont(font);

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        image_label = new QLabel(QuestionsDialog);
        image_label->setObjectName("image_label");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(image_label->sizePolicy().hasHeightForWidth());
        image_label->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(image_label);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        plainTextEdit = new ClickableTextEdit(QuestionsDialog);
        plainTextEdit->setObjectName("plainTextEdit");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(plainTextEdit->sizePolicy().hasHeightForWidth());
        plainTextEdit->setSizePolicy(sizePolicy2);
        plainTextEdit->setMinimumSize(QSize(0, 0));
        plainTextEdit->setMaximumSize(QSize(16777215, 200));
        QFont font1;
        font1.setPointSize(10);
        plainTextEdit->setFont(font1);
        plainTextEdit->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        plainTextEdit->setFocusPolicy(Qt::NoFocus);
        plainTextEdit->setReadOnly(true);

        horizontalLayout->addWidget(plainTextEdit);

        horizontalSpacer = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        plainTextEdit_2 = new ClickableTextEdit(QuestionsDialog);
        plainTextEdit_2->setObjectName("plainTextEdit_2");
        sizePolicy2.setHeightForWidth(plainTextEdit_2->sizePolicy().hasHeightForWidth());
        plainTextEdit_2->setSizePolicy(sizePolicy2);
        plainTextEdit_2->setMinimumSize(QSize(0, 0));
        plainTextEdit_2->setMaximumSize(QSize(16777215, 200));
        plainTextEdit_2->setFont(font1);
        plainTextEdit_2->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        plainTextEdit_2->setFocusPolicy(Qt::NoFocus);
        plainTextEdit_2->setReadOnly(true);

        horizontalLayout->addWidget(plainTextEdit_2);

        horizontalSpacer_2 = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        plainTextEdit_3 = new ClickableTextEdit(QuestionsDialog);
        plainTextEdit_3->setObjectName("plainTextEdit_3");
        sizePolicy2.setHeightForWidth(plainTextEdit_3->sizePolicy().hasHeightForWidth());
        plainTextEdit_3->setSizePolicy(sizePolicy2);
        plainTextEdit_3->setMaximumSize(QSize(16777215, 200));
        plainTextEdit_3->setFont(font1);
        plainTextEdit_3->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        plainTextEdit_3->setFocusPolicy(Qt::NoFocus);
        plainTextEdit_3->setReadOnly(true);

        horizontalLayout->addWidget(plainTextEdit_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 12, QSizePolicy::Minimum, QSizePolicy::Fixed);

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
        label->setText(QCoreApplication::translate("QuestionsDialog", "question", nullptr));
        image_label->setText(QCoreApplication::translate("QuestionsDialog", "question image", nullptr));
        plainTextEdit->setPlainText(QString());
    } // retranslateUi

};

namespace Ui {
    class QuestionsDialog: public Ui_QuestionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUESTIONSDIALOG_H
