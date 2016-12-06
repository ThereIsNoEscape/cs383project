#ifndef SHAPEEFFECTDIALOG_H
#define SHAPEEFFECTDIALOG_H

#include <QDialog>
#include "effect.h"
#include "config.h"

namespace Ui {
class shapeEffectDialog;
}

class shapeEffectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit shapeEffectDialog(QWidget *parent = 0);
    ~shapeEffectDialog();

signals:
    void accepted(const effect*);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::shapeEffectDialog *ui;
    effect* retEffect;
};

#endif // shapeEFFECTDIALOG_H
