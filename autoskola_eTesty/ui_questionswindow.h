/********************************************************************************
** Form generated from reading UI file 'questionswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUESTIONSWINDOW_H
#define UI_QUESTIONSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuestionsWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QLabel *image_label;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPlainTextEdit *plainTextEdit;
    QSpacerItem *horizontalSpacer;
    QPlainTextEdit *plainTextEdit_2;
    QSpacerItem *horizontalSpacer_2;
    QPlainTextEdit *plainTextEdit_3;
    QSpacerItem *horizontalSpacer_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QuestionsWindow)
    {
        if (QuestionsWindow->objectName().isEmpty())
            QuestionsWindow->setObjectName("QuestionsWindow");
        QuestionsWindow->resize(949, 609);
        centralwidget = new QWidget(QuestionsWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, 0, -1, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        label = new QLabel(centralwidget);
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

        image_label = new QLabel(centralwidget);
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

        plainTextEdit = new QPlainTextEdit(centralwidget);
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

        plainTextEdit_2 = new QPlainTextEdit(centralwidget);
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

        plainTextEdit_3 = new QPlainTextEdit(centralwidget);
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


        horizontalLayout_2->addLayout(verticalLayout_2);

        QuestionsWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QuestionsWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 949, 21));
        QuestionsWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(QuestionsWindow);
        statusbar->setObjectName("statusbar");
        QuestionsWindow->setStatusBar(statusbar);

        retranslateUi(QuestionsWindow);

        QMetaObject::connectSlotsByName(QuestionsWindow);
    } // setupUi

    void retranslateUi(QMainWindow *QuestionsWindow)
    {
        QuestionsWindow->setWindowTitle(QCoreApplication::translate("QuestionsWindow", "Ot\303\241zky", nullptr));
        label->setText(QCoreApplication::translate("QuestionsWindow", "question", nullptr));
        image_label->setText(QCoreApplication::translate("QuestionsWindow", "question image", nullptr));
        plainTextEdit->setPlainText(QString());
    } // retranslateUi

};

namespace Ui {
    class QuestionsWindow: public Ui_QuestionsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUESTIONSWINDOW_H
