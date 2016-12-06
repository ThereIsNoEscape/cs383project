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
    void on_pushButton_test_clicked();
    void on_pushButton_up_clicked();
    void on_pushButton_down_clicked();
    void on_pushButton_left_clicked();
    void on_pushButton_right_clicked();

private:
    Ui::shapeEffectDialog *ui;
    effect* retEffect;
    int offsetX;
    int offsetY;
    bool effectSelected;
    void updateGUI();
};

#endif // shapeEFFECTDIALOG_H
