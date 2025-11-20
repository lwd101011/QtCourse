/********************************************************************************
** Form generated from reading UI file 'replacedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPLACEDIALOG_H
#define UI_REPLACEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ReplaceDialog
{
public:
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *searchText;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *targetText;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *cbCaseSensetive;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *rbUp;
    QRadioButton *rbDown;
    QVBoxLayout *verticalLayout;
    QPushButton *btFindNext;
    QPushButton *btReplace;
    QPushButton *btReplaceAll;
    QPushButton *btCancel;

    void setupUi(QDialog *ReplaceDialog)
    {
        if (ReplaceDialog->objectName().isEmpty())
            ReplaceDialog->setObjectName("ReplaceDialog");
        ReplaceDialog->resize(365, 148);
        horizontalLayout_5 = new QHBoxLayout(ReplaceDialog);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(ReplaceDialog);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(60, 0));
        label->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(label);

        searchText = new QLineEdit(ReplaceDialog);
        searchText->setObjectName("searchText");
        searchText->setMaximumSize(QSize(300, 16777215));

        horizontalLayout->addWidget(searchText);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(ReplaceDialog);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(60, 0));
        label_2->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_2->addWidget(label_2);

        targetText = new QLineEdit(ReplaceDialog);
        targetText->setObjectName("targetText");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(targetText->sizePolicy().hasHeightForWidth());
        targetText->setSizePolicy(sizePolicy1);
        targetText->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_2->addWidget(targetText);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        cbCaseSensetive = new QCheckBox(ReplaceDialog);
        cbCaseSensetive->setObjectName("cbCaseSensetive");

        horizontalLayout_4->addWidget(cbCaseSensetive);

        groupBox = new QGroupBox(ReplaceDialog);
        groupBox->setObjectName("groupBox");
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        rbUp = new QRadioButton(groupBox);
        rbUp->setObjectName("rbUp");

        horizontalLayout_3->addWidget(rbUp);

        rbDown = new QRadioButton(groupBox);
        rbDown->setObjectName("rbDown");

        horizontalLayout_3->addWidget(rbDown);


        horizontalLayout_4->addWidget(groupBox);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        btFindNext = new QPushButton(ReplaceDialog);
        btFindNext->setObjectName("btFindNext");
        btFindNext->setMaximumSize(QSize(82, 16777215));

        verticalLayout->addWidget(btFindNext);

        btReplace = new QPushButton(ReplaceDialog);
        btReplace->setObjectName("btReplace");
        btReplace->setMaximumSize(QSize(82, 16777215));

        verticalLayout->addWidget(btReplace);

        btReplaceAll = new QPushButton(ReplaceDialog);
        btReplaceAll->setObjectName("btReplaceAll");
        btReplaceAll->setMaximumSize(QSize(82, 16777215));

        verticalLayout->addWidget(btReplaceAll);

        btCancel = new QPushButton(ReplaceDialog);
        btCancel->setObjectName("btCancel");
        btCancel->setMaximumSize(QSize(82, 16777215));

        verticalLayout->addWidget(btCancel);


        horizontalLayout_5->addLayout(verticalLayout);


        retranslateUi(ReplaceDialog);

        QMetaObject::connectSlotsByName(ReplaceDialog);
    } // setupUi

    void retranslateUi(QDialog *ReplaceDialog)
    {
        ReplaceDialog->setWindowTitle(QCoreApplication::translate("ReplaceDialog", "\346\233\277\346\215\242", nullptr));
        label->setText(QCoreApplication::translate("ReplaceDialog", "\346\237\245\346\211\276\347\233\256\346\240\207\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("ReplaceDialog", "\346\233\277\346\215\242\344\270\272\357\274\232", nullptr));
        cbCaseSensetive->setText(QCoreApplication::translate("ReplaceDialog", "\345\214\272\345\210\206\345\244\247\345\260\217\345\206\231", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ReplaceDialog", "\346\226\271\345\220\221", nullptr));
        rbUp->setText(QCoreApplication::translate("ReplaceDialog", "\345\220\221\344\270\212(&U)", nullptr));
        rbDown->setText(QCoreApplication::translate("ReplaceDialog", "\345\220\221\344\270\213(&D)", nullptr));
        btFindNext->setText(QCoreApplication::translate("ReplaceDialog", "\346\237\245\346\211\276\344\270\213\344\270\200\344\270\252(&F)", nullptr));
        btReplace->setText(QCoreApplication::translate("ReplaceDialog", "\346\233\277\346\215\242(&R)", nullptr));
        btReplaceAll->setText(QCoreApplication::translate("ReplaceDialog", "\345\205\250\351\203\250\346\233\277\346\215\242(&A)", nullptr));
        btCancel->setText(QCoreApplication::translate("ReplaceDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReplaceDialog: public Ui_ReplaceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPLACEDIALOG_H
