#ifndef NEWCONTATODIALOG_H
#define NEWCONTATODIALOG_H

#include <QDialog>
#include <string>

using namespace  std;

namespace Ui {
class NewContatoDialog;
}

class NewContatoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewContatoDialog(QWidget *parent = 0);
    ~NewContatoDialog();
signals:
    void NovoContato(const string &Destinatario);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::NewContatoDialog *ui;
};

#endif // NEWCONTATODIALOG_H
