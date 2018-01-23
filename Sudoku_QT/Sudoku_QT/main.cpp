#include "sudoku_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sudoku_window w;
    w.setWindowTitle(" Sudoku ");
    w.show();

    return a.exec();
}
