#ifndef SYMBOLEFFECTDIALOG_H
#define SYMBOLEFFECTDIALOG_H

#include <QDialog>
#include "effect.h"
#include "config.h"

namespace Ui {
class symbolEffectDialog;
}

class symbolEffectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit symbolEffectDialog(QWidget *parent = 0);
    ~symbolEffectDialog();

signals:
    void accepted(const effect*);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::symbolEffectDialog *ui;
    effect* retEffect;
};

#endif // symbolEFFECTDIALOG_H
