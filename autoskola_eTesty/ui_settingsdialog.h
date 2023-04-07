/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_5;
    QCheckBox *checkBox;
    QToolButton *toolButton;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName("SettingsDialog");
        SettingsDialog->resize(393, 255);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/settings.ico"), QSize(), QIcon::Normal, QIcon::Off);
        SettingsDialog->setWindowIcon(icon);
        horizontalLayout_2 = new QHBoxLayout(SettingsDialog);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_3 = new QSpacerItem(8, 8, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 1, 1, 1);

        checkBox = new QCheckBox(SettingsDialog);
        checkBox->setObjectName("checkBox");
        checkBox->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);

        toolButton = new QToolButton(SettingsDialog);
        toolButton->setObjectName("toolButton");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toolButton->sizePolicy().hasHeightForWidth());
        toolButton->setSizePolicy(sizePolicy);
        toolButton->setMinimumSize(QSize(30, 28));
        toolButton->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(toolButton, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton = new QPushButton(SettingsDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(150, 28));
        pushButton->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(SettingsDialog);
        label->setObjectName("label");
        label->setMinimumSize(QSize(120, 28));

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(30, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        label_2 = new QLabel(SettingsDialog);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(-1, 0, -1, -1);
        pushButton_2 = new QPushButton(SettingsDialog);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_3->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(SettingsDialog);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_3->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(SettingsDialog);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_3->addWidget(pushButton_4);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_4 = new QSpacerItem(8, 8, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        retranslateUi(SettingsDialog);

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QCoreApplication::translate("SettingsDialog", "Nastaven\303\255", nullptr));
        checkBox->setText(QCoreApplication::translate("SettingsDialog", "Kontrolovat aktualizace", nullptr));
        toolButton->setText(QCoreApplication::translate("SettingsDialog", "?", nullptr));
        pushButton->setText(QCoreApplication::translate("SettingsDialog", "Zkontrolovat aktualizace", nullptr));
        label->setText(QCoreApplication::translate("SettingsDialog", "Aktu\303\241ln\303\255 verze", nullptr));
        label_2->setText(QCoreApplication::translate("SettingsDialog", "Nastaven\303\255 nen\303\255 ulo\305\276eno", nullptr));
        pushButton_2->setText(QCoreApplication::translate("SettingsDialog", "Defaultn\303\255", nullptr));
        pushButton_3->setText(QCoreApplication::translate("SettingsDialog", "Zru\305\241it", nullptr));
        pushButton_4->setText(QCoreApplication::translate("SettingsDialog", "Ulo\305\276it", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
