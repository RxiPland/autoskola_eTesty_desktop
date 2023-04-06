/********************************************************************************
** Form generated from reading UI file 'startmenu.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTMENU_H
#define UI_STARTMENU_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartMenu
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QLabel *image_label;
    QLabel *image_label_2;

    void setupUi(QMainWindow *StartMenu)
    {
        if (StartMenu->objectName().isEmpty())
            StartMenu->setObjectName("StartMenu");
        StartMenu->resize(315, 303);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/etesty_logo.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        StartMenu->setWindowIcon(icon);
        centralwidget = new QWidget(StartMenu);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(-1, 0, -1, -1);
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setMinimumSize(QSize(0, 28));

        gridLayout->addWidget(pushButton_3, 5, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_4, 4, 1, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(160, 38));
        QFont font;
        font.setPointSize(10);
        pushButton->setFont(font);

        gridLayout->addWidget(pushButton, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalSpacer_5 = new QSpacerItem(15, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_5, 7, 1, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_6, 11, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(0, 25, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        gridLayout->addItem(verticalSpacer_2, 0, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        gridLayout->addItem(verticalSpacer_3, 13, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(0, 28));

        gridLayout->addWidget(pushButton_2, 3, 1, 1, 1);

        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(pushButton_5, 9, 1, 1, 1);

        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(pushButton_4, 12, 1, 1, 1);

        image_label = new QLabel(centralwidget);
        image_label->setObjectName("image_label");

        gridLayout->addWidget(image_label, 9, 0, 1, 1);

        image_label_2 = new QLabel(centralwidget);
        image_label_2->setObjectName("image_label_2");

        gridLayout->addWidget(image_label_2, 12, 0, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);

        StartMenu->setCentralWidget(centralwidget);

        retranslateUi(StartMenu);

        QMetaObject::connectSlotsByName(StartMenu);
    } // setupUi

    void retranslateUi(QMainWindow *StartMenu)
    {
        StartMenu->setWindowTitle(QCoreApplication::translate("StartMenu", "autoskola-eTesty", nullptr));
        pushButton_3->setText(QCoreApplication::translate("StartMenu", "Nastaven\303\255", nullptr));
        pushButton->setText(QCoreApplication::translate("StartMenu", "Spustit ot\303\241zky", nullptr));
        pushButton_2->setText(QCoreApplication::translate("StartMenu", "Zobrazit statistiky", nullptr));
        pushButton_5->setText(QCoreApplication::translate("StartMenu", "Zdrojov\303\275 k\303\263d", nullptr));
        pushButton_4->setText(QCoreApplication::translate("StartMenu", "autoskola-testy.cz", nullptr));
        image_label->setText(QString());
        image_label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class StartMenu: public Ui_StartMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTMENU_H
