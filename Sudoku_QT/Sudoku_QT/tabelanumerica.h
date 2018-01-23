#ifndef TABELANUMERICA_H
#define TABELANUMERICA_H

#include <QDialog>

namespace Ui {
class TabelaNumerica;
}

class TabelaNumerica : public QDialog
{
    Q_OBJECT

public:
    explicit TabelaNumerica(QWidget *parent = 0);
    ~TabelaNumerica();
    int Num()const { return num; }
private slots:
    void on_tabela_numerica_cellClicked(int row, int column);

    void on_limpar_Button_clicked();

private:
    Ui::TabelaNumerica *ui;
    int num;
};

#endif // TABELANUMERICA_H
