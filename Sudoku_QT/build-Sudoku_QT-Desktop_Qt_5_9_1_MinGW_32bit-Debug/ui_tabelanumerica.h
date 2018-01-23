/********************************************************************************
** Form generated from reading UI file 'tabelanumerica.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABELANUMERICA_H
#define UI_TABELANUMERICA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TabelaNumerica
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tabela_numerica;
    QPushButton *limpar_Button;

    void setupUi(QDialog *TabelaNumerica)
    {
        if (TabelaNumerica->objectName().isEmpty())
            TabelaNumerica->setObjectName(QStringLiteral("TabelaNumerica"));
        TabelaNumerica->resize(105, 127);
        TabelaNumerica->setMinimumSize(QSize(105, 127));
        TabelaNumerica->setMaximumSize(QSize(105, 127));
        TabelaNumerica->setBaseSize(QSize(105, 127));
        TabelaNumerica->setLayoutDirection(Qt::LeftToRight);
        verticalLayout = new QVBoxLayout(TabelaNumerica);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        tabela_numerica = new QTableWidget(TabelaNumerica);
        if (tabela_numerica->columnCount() < 3)
            tabela_numerica->setColumnCount(3);
        if (tabela_numerica->rowCount() < 3)
            tabela_numerica->setRowCount(3);
        tabela_numerica->setObjectName(QStringLiteral("tabela_numerica"));
        tabela_numerica->setFrameShape(QFrame::Box);
        tabela_numerica->setFrameShadow(QFrame::Raised);
        tabela_numerica->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tabela_numerica->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tabela_numerica->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tabela_numerica->setRowCount(3);
        tabela_numerica->setColumnCount(3);
        tabela_numerica->horizontalHeader()->setVisible(false);
        tabela_numerica->horizontalHeader()->setDefaultSectionSize(30);
        tabela_numerica->horizontalHeader()->setHighlightSections(true);
        tabela_numerica->horizontalHeader()->setMinimumSectionSize(30);
        tabela_numerica->verticalHeader()->setVisible(false);
        tabela_numerica->verticalHeader()->setDefaultSectionSize(30);
        tabela_numerica->verticalHeader()->setMinimumSectionSize(30);

        verticalLayout->addWidget(tabela_numerica);

        limpar_Button = new QPushButton(TabelaNumerica);
        limpar_Button->setObjectName(QStringLiteral("limpar_Button"));
        limpar_Button->setFocusPolicy(Qt::NoFocus);

        verticalLayout->addWidget(limpar_Button);


        retranslateUi(TabelaNumerica);

        QMetaObject::connectSlotsByName(TabelaNumerica);
    } // setupUi

    void retranslateUi(QDialog *TabelaNumerica)
    {
        TabelaNumerica->setWindowTitle(QString());
        limpar_Button->setText(QApplication::translate("TabelaNumerica", "limpar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TabelaNumerica: public Ui_TabelaNumerica {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABELANUMERICA_H
