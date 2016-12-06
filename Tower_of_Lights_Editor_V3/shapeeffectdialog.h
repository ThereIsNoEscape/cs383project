#ifndef SHAPEEFFECTDIALOG_H
#define SHAPEEFFECTDIALOG_H

#include <QDialog>
#include <QColor>
#include <QColorDialog>
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
    void on_pushButton_color_clicked();

private:
    Ui::shapeEffectDialog *ui;
    effect* retEffect;
    int offsetX;
    int offsetY;
    bool effectSelected;
    QColor effectColor;
    void updateGUI();
    bool isTouchingXBoundaries();
    bool isTouchingYBoundaries();

};

#endif // shapeEFFECTDIALOG_H