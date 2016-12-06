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
    void on_pushButton_test_clicked();
    void on_pushButton_up_clicked();
    void on_pushButton_down_clicked();
    void on_pushButton_left_clicked();
    void on_pushButton_right_clicked();

private:
    Ui::symbolEffectDialog *ui;
    effect* retEffect;
    int offsetX;
    int offsetY;
    bool effectSelected;
    void updateGUI();
};

#endif // symbolEFFECTDIALOG_H
