/********************************************************************************
** Form generated from reading UI file 'avisos.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AVISOS_H
#define UI_AVISOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Avisos
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *Avisos)
    {
        if (Avisos->objectName().isEmpty())
            Avisos->setObjectName(QStringLiteral("Avisos"));
        Avisos->resize(227, 160);
        Avisos->setMaximumSize(QSize(227, 160));
        verticalLayout = new QVBoxLayout(Avisos);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        retranslateUi(Avisos);

        QMetaObject::connectSlotsByName(Avisos);
    } // setupUi

    void retranslateUi(QDialog *Avisos)
    {
        Avisos->setWindowTitle(QApplication::translate("Avisos", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Avisos: public Ui_Avisos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AVISOS_H
