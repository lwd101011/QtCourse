/********************************************************************************
** Form generated from reading UI file 'aboutdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_6;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_4;

    void setupUi(QDialog *AboutDialog)
    {
        if (AboutDialog->objectName().isEmpty())
            AboutDialog->setObjectName("AboutDialog");
        AboutDialog->resize(358, 281);
        buttonBox = new QDialogButtonBox(AboutDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(-20, 230, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Ok);
        label = new QLabel(AboutDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 20, 261, 51));
        QFont font;
        font.setPointSize(28);
        label->setFont(font);
        label_6 = new QLabel(AboutDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(30, 100, 121, 121));
        label_6->setStyleSheet(QString::fromUtf8("border-image: url(:/img/Write.png);"));
        layoutWidget = new QWidget(AboutDialog);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(170, 110, 171, 91));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName("label_5");

        verticalLayout->addWidget(label_5);

        label_4 = new QLabel(AboutDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 240, 121, 20));

        retranslateUi(AboutDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, AboutDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, AboutDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(AboutDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDialog)
    {
        AboutDialog->setWindowTitle(QCoreApplication::translate("AboutDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AboutDialog", "\345\260\217\344\271\235\346\226\207\346\234\254\347\274\226\350\276\221\345\231\250", nullptr));
        label_6->setText(QString());
        label_2->setText(QCoreApplication::translate("AboutDialog", "\345\274\200\345\217\221\350\200\205\357\274\232\345\210\230\347\202\234\344\270\234", nullptr));
        label_3->setText(QCoreApplication::translate("AboutDialog", "\345\255\246\345\217\267\357\274\2322023414300213", nullptr));
        label_5->setText(QCoreApplication::translate("AboutDialog", "email:466712445@qq.com", nullptr));
        label_4->setText(QCoreApplication::translate("AboutDialog", "v1.0 build 20251120", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutDialog: public Ui_AboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H
