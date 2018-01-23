#include "tabelanumerica.h"
#include "ui_tabelanumerica.h"
#include <QLabel>


TabelaNumerica::TabelaNumerica(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TabelaNumerica),
    num(-1)
{
    ui->setupUi(this);

    QLabel *prov;
    int qtd = 1;
    setWindowTitle(" ");
    ui->tabela_numerica->setStyleSheet("*{ background: #cbf6ff }");

    for(int i = 0; i < 3; i++)for(int j = 0; j < 3; j++)
    {
        ui->tabela_numerica->setCellWidget(i,j, new QLabel);
        prov = (QLabel*)ui->tabela_numerica->cellWidget(i,j);
        prov->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        prov->setFrameStyle(QFrame::StyledPanel);
        prov->setFont( QFont( "Times", 8, QFont::Bold) );
        prov->setNum(qtd++);

        prov->setStyleSheet("QLabel:hover{ background: yellow}");
    }
}

TabelaNumerica::~TabelaNumerica()
{
    delete ui;
}

void TabelaNumerica::on_tabela_numerica_cellClicked(int row, int column)
{
    QLabel *prov = (QLabel*)ui->tabela_numerica->cellWidget(row,column);
    num = prov->text().toInt();
    close();
}

void TabelaNumerica::on_limpar_Button_clicked()
{
    num = 0;
    close();
}
