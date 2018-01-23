#ifndef SUDOKU_WINDOW_H
#define SUDOKU_WINDOW_H

#include <QMainWindow>
#include <sudoku.h>
#include <stack>
#include <QMessageBox>

namespace Ui {
class sudoku_window;
}

class sudoku_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit sudoku_window(QWidget *parent = 0);
    ~sudoku_window();
    void novo_jogo();
    void atualiza_tabuleiro(int i, int j);
    void imprimir_tabuleiro();
    void formatar();

private slots:
    void on_tabuleiro_cellClicked(int row, int column);

    void on_Novo_Button_clicked();

    void on_Resolver_Button_clicked();

    void on_marcadores_button_clicked();

private:
    Ui::sudoku_window *ui;
    Sudoku Tab;
    bool marcadores;
    QMessageBox Avisos;
};

#endif // SUDOKU_WINDOW_H
