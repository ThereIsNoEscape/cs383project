#include "symboleffectdialog.h"
#include "ui_symboleffectdialog.h"

symbolEffectDialog::symbolEffectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::symbolEffectDialog)
{
    ui->setupUi(this);
    retEffect = new effect;
    for (int x = 0; x < TAN_DEFAULT_ROWS; x++)
        for (int y = 0; y < TAN_DEFAULT_COLS; y++)
            retEffect->pixels[y][x] = QColor(0,0,0,0);
    retEffect->primary = QColor(0,0,0,0);
    retEffect->secondary = QColor(0,0,0,0);
}

symbolEffectDialog::~symbolEffectDialog()
{
    delete ui;
}

void symbolEffectDialog::on_buttonBox_accepted()
{
    emit accepted(retEffect);
}
