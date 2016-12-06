#include "shapeeffectdialog.h"
#include "ui_shapeeffectdialog.h"

shapeEffectDialog::shapeEffectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::shapeEffectDialog)
{
    ui->setupUi(this);
    retEffect = new effect;
    for (int x = 0; x < TAN_DEFAULT_ROWS; x++)
        for (int y = 0; y < TAN_DEFAULT_COLS; y++)
            retEffect->pixels[y][x] = QColor(0,0,0,0);
    retEffect->primary = QColor(0,0,0,0);
    retEffect->secondary = QColor(0,0,0,0);
}

shapeEffectDialog::~shapeEffectDialog()
{
    delete ui;
}

void shapeEffectDialog::on_buttonBox_accepted()
{
    emit accepted(retEffect);
}
