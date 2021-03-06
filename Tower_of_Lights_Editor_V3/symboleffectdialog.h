#ifndef SYMBOLEFFECTDIALOG_H
#define SYMBOLEFFECTDIALOG_H

#include <QDialog>
#include <QColor>
#include <QColorDialog>
#include "effect.h"
#include "config.h"

namespace Ui {
class symbolEffectDialog;
}

class symbolEffectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit symbolEffectDialog(QColor frame[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS], QWidget *parent = 0);
    ~symbolEffectDialog();

signals:
    void accepted(const effect*);

private slots:
    void on_buttonBox_accepted();
    void on_pushButton_up_clicked();
    void on_pushButton_down_clicked();
    void on_pushButton_left_clicked();
    void on_pushButton_right_clicked();
    void on_pushButton_color_clicked();

    void on_pushButton_clear_clicked();
    void on_comboBox_activated(int index);

private:
    Ui::symbolEffectDialog *ui;
    effect* retEffect;
    int offsetX;
    int offsetY;
    bool effectSelected;
    QColor backgroundFrame[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS];
    QColor effectColor;
    void updateGUI();
    bool isTouchingXBoundaries();
    bool isTouchingYBoundaries();

    void clearGrid();
};

#endif // symbolEFFECTDIALOG_H
