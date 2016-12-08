#include "infodialog.h"
#include "ui_infodialog.h"

infoDialog::infoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::infoDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Help");
}

infoDialog::~infoDialog()
{
    delete ui;
}

void infoDialog::on_pushButton_close_clicked()
{
    close();
}
