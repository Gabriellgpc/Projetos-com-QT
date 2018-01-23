/********************************************************************************
** Form generated from reading UI file 'newcontatodialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWCONTATODIALOG_H
#define UI_NEWCONTATODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewContatoDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *Dest_lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewContatoDialog)
    {
        if (NewContatoDialog->objectName().isEmpty())
            NewContatoDialog->setObjectName(QStringLiteral("NewContatoDialog"));
        NewContatoDialog->resize(400, 135);
        verticalLayout = new QVBoxLayout(NewContatoDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(NewContatoDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        Dest_lineEdit = new QLineEdit(NewContatoDialog);
        Dest_lineEdit->setObjectName(QStringLiteral("Dest_lineEdit"));

        horizontalLayout->addWidget(Dest_lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(NewContatoDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(NewContatoDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewContatoDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewContatoDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewContatoDialog);
    } // setupUi

    void retranslateUi(QDialog *NewContatoDialog)
    {
        NewContatoDialog->setWindowTitle(QApplication::translate("NewContatoDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("NewContatoDialog", "Destinatario", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NewContatoDialog: public Ui_NewContatoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWCONTATODIALOG_H
