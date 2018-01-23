#include "sudoku_window.h"
#include "ui_sudoku_window.h"
#include "tabelanumerica.h"
#include <QLabel>


sudoku_window::sudoku_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sudoku_window),
    marcadores(false),
    Avisos(this)
{
    ui->setupUi(this);

    ui->tabuleiro->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tabuleiro->setTabKeyNavigation(false);

    QLabel *prov;

    for(int i =0 ;i < 9; i++)for(int j =0 ;j < 9; j++)
    {
        ui->tabuleiro->setCellWidget(i,j, new QLabel);
        prov = (QLabel*)ui->tabuleiro->cellWidget(i,j);

        prov->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        prov->setFrameStyle(QFrame::StyledPanel);
        prov->setFont( QFont( "Times", 15, QFont::Bold ) );
    }
    formatar();
    novo_jogo();
}

/*
 *cores background:
 *  #fff2e7
 *  #c7fffe
 *  #90baba
 */
void sudoku_window::formatar()
{

    QLabel *prov;


    for(int i =0 ;i < 9; i++)for(int j =0 ;j < 9; j++)
    {

        prov = (QLabel*)ui->tabuleiro->cellWidget(i,j);
        if(i < 3 || i > 5)
            if(j < 3 || j > 5)
                prov->setStyleSheet( "QLabel{background : white }" );
            else
                prov->setStyleSheet( "QLabel{background : #90baba }" );
        else
            if(j < 3 || j > 5)
                prov->setStyleSheet( "QLabel{background : #90baba }" );
            else
                prov->setStyleSheet( "QLabel{background : white }" );
    }

}


void sudoku_window::novo_jogo()
{
    Tab.novo_jogo();
    imprimir_tabuleiro();
}

void sudoku_window::atualiza_tabuleiro(int i,int j)
{
    QLabel *prov = (QLabel*)ui->tabuleiro->cellWidget(i,j);
    prov->setStyleSheet("QLabel{color: blue}" + prov->styleSheet());

    if(Tab(i,j) != 0 )
        prov->setNum(Tab(i,j));
    else
        prov->clear();
}

void sudoku_window::imprimir_tabuleiro()
{
    for(int i =0 ;i < 9; i++)for(int j =0 ;j < 9; j++)
    {
        QLabel *prov = (QLabel*)ui->tabuleiro->cellWidget(i,j);

        if(Tab(i,j) != 0 )
        {
            prov->setNum(Tab(i,j));
            prov->setEnabled(false);
        }
        else
        {
            prov->setEnabled(true);
            prov->clear();
        }

    }
}

sudoku_window::~sudoku_window()
{
    delete ui;
}

void sudoku_window::on_tabuleiro_cellClicked(int row, int column)
{
    if(ui->tabuleiro->cellWidget(row,column)->isEnabled() == false) return;

    TabelaNumerica num_tab(this);
    num_tab.setWindowTitle( "Escolha um número ");
    num_tab.exec();

    if(!Tab.jogada_valida( Jogada(row,column,num_tab.Num()) )) return;
    if(num_tab.Num() == -1) return;

    Tab.fazer_jogada( Jogada(row,column,num_tab.Num()));
    atualiza_tabuleiro(row,column);
}

void sudoku_window::on_Novo_Button_clicked()
{
    novo_jogo();
}


void sudoku_window::on_Resolver_Button_clicked()
{
    int gerados = Tab.resolver();
    imprimir_tabuleiro();
    if(Tab.num_casas_vazias() != 0)
        Avisos.setInformativeText("Sudoku sem solução");
    else
        Avisos.setInformativeText("Sudoku Resolvido");
    Avisos.setText("Nós Gerados");
    Avisos.setInformativeText(QString::number(gerados));
    Avisos.exec();
}

void sudoku_window::on_marcadores_button_clicked()
{
    marcadores = !marcadores;
    if(marcadores)
        ui->marcadores_button->setText( "Esconder Marcadores" );
    else
        ui->marcadores_button->setText( "Marcadores");
}
