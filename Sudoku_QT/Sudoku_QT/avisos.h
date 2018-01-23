#ifndef AVISOS_H
#define AVISOS_H

#include <QDialog>

namespace Ui {
class Avisos;
}

class Avisos : public QDialog
{
    Q_OBJECT

public:
    explicit Avisos(QWidget *parent = 0);
    ~Avisos();

private:
    Ui::Avisos *ui;
};

#endif // AVISOS_H
