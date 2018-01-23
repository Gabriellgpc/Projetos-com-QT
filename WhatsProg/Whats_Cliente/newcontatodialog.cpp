#include "newcontatodialog.h"
#include "ui_newcontatodialog.h"

NewContatoDialog::NewContatoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewContatoDialog)
{
    ui->setupUi(this);
}

NewContatoDialog::~NewContatoDialog()
{
    delete ui;
}


void NewContatoDialog::on_buttonBox_accepted()
{
    string Dest = ui->Dest_lineEdit->text().toStdString();
    emit NovoContato(Dest);
}
