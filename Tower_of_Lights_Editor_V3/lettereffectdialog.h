#ifndef LETTEREFFECTDIALOG_H
#define LETTEREFFECTDIALOG_H

#include <QDialog>
#include "effect.h"
#include "config.h"

namespace Ui {
class letterEffectDialog;
}

class letterEffectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit letterEffectDialog(QWidget *parent = 0);
    ~letterEffectDialog();

signals:
    void accepted(const effect*);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::letterEffectDialog *ui;
    effect* retEffect;
};

#endif // LETTEREFFECTDIALOG_H
