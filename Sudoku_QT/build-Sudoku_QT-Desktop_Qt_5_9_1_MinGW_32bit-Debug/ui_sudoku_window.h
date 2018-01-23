/********************************************************************************
** Form generated from reading UI file 'sudoku_window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUDOKU_WINDOW_H
#define UI_SUDOKU_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sudoku_window
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTableWidget *tabuleiro;
    QGridLayout *gridLayout;
    QPushButton *marcadores_button;
    QPushButton *Resolver_Button;
    QPushButton *Novo_Button;
    QMenuBar *menuBar;
    QMenu *menuAjuda;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *sudoku_window)
    {
        if (sudoku_window->objectName().isEmpty())
            sudoku_window->setObjectName(QStringLiteral("sudoku_window"));
        sudoku_window->resize(387, 468);
        sudoku_window->setMinimumSize(QSize(387, 468));
        sudoku_window->setMaximumSize(QSize(387, 468));
        centralWidget = new QWidget(sudoku_window);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabuleiro = new QTableWidget(centralWidget);
        if (tabuleiro->columnCount() < 9)
            tabuleiro->setColumnCount(9);
        if (tabuleiro->rowCount() < 9)
            tabuleiro->setRowCount(9);
        tabuleiro->setObjectName(QStringLiteral("tabuleiro"));
        tabuleiro->setEnabled(true);
        tabuleiro->setFrameShape(QFrame::Box);
        tabuleiro->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tabuleiro->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tabuleiro->setEditTriggers(QAbstractItemView::AnyKeyPressed);
        tabuleiro->setTabKeyNavigation(false);
        tabuleiro->setProperty("showDropIndicator", QVariant(false));
        tabuleiro->setSelectionMode(QAbstractItemView::SingleSelection);
        tabuleiro->setTextElideMode(Qt::ElideMiddle);
        tabuleiro->setGridStyle(Qt::NoPen);
        tabuleiro->setCornerButtonEnabled(false);
        tabuleiro->setRowCount(9);
        tabuleiro->setColumnCount(9);
        tabuleiro->horizontalHeader()->setVisible(false);
        tabuleiro->horizontalHeader()->setDefaultSectionSize(40);
        tabuleiro->horizontalHeader()->setMinimumSectionSize(40);
        tabuleiro->verticalHeader()->setVisible(false);
        tabuleiro->verticalHeader()->setDefaultSectionSize(40);
        tabuleiro->verticalHeader()->setMinimumSectionSize(40);

        verticalLayout->addWidget(tabuleiro);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        marcadores_button = new QPushButton(centralWidget);
        marcadores_button->setObjectName(QStringLiteral("marcadores_button"));

        gridLayout->addWidget(marcadores_button, 0, 2, 1, 1);

        Resolver_Button = new QPushButton(centralWidget);
        Resolver_Button->setObjectName(QStringLiteral("Resolver_Button"));

        gridLayout->addWidget(Resolver_Button, 0, 0, 1, 1);

        Novo_Button = new QPushButton(centralWidget);
        Novo_Button->setObjectName(QStringLiteral("Novo_Button"));

        gridLayout->addWidget(Novo_Button, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        sudoku_window->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(sudoku_window);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 387, 21));
        menuAjuda = new QMenu(menuBar);
        menuAjuda->setObjectName(QStringLiteral("menuAjuda"));
        sudoku_window->setMenuBar(menuBar);
        mainToolBar = new QToolBar(sudoku_window);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        sudoku_window->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(sudoku_window);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setSizeGripEnabled(true);
        sudoku_window->setStatusBar(statusBar);

        menuBar->addAction(menuAjuda->menuAction());

        retranslateUi(sudoku_window);

        QMetaObject::connectSlotsByName(sudoku_window);
    } // setupUi

    void retranslateUi(QMainWindow *sudoku_window)
    {
        sudoku_window->setWindowTitle(QApplication::translate("sudoku_window", "sudoku_window", Q_NULLPTR));
        marcadores_button->setText(QApplication::translate("sudoku_window", "Marcadores", Q_NULLPTR));
        Resolver_Button->setText(QApplication::translate("sudoku_window", "Resolver", Q_NULLPTR));
        Novo_Button->setText(QApplication::translate("sudoku_window", "Novo", Q_NULLPTR));
        menuAjuda->setTitle(QApplication::translate("sudoku_window", "Ajuda", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class sudoku_window: public Ui_sudoku_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUDOKU_WINDOW_H
