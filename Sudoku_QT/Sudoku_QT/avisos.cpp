#include "avisos.h"
#include "ui_avisos.h"

Avisos::Avisos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Avisos)
{
    ui->setupUi(this);
}

Avisos::~Avisos()
{
    delete ui;
}
