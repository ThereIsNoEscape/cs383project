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
    explicit shapeEffectDialog(QColor frame[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS], QWidget *parent = 0);
    ~shapeEffectDialog();

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
    void on_pushButton_color_2_clicked();
    void on_noFill_stateChanged(int state);

private:
    Ui::shapeEffectDialog *ui;
    effect* retEffect;
    int offsetX;
    int offsetY;
    bool effectSelected;
    QColor backgroundFrame[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS];
    void updateGUI();
    bool isTouchingXBoundaries();
    bool isTouchingYBoundaries();

    void clearGrid();
    void createCircle();
    void createCircleFill();
    void removeCircleFill();
    void createSquare();
    void createSquareFill();
    void removeSquareFill();
    void createVerticalRectangle();
    void createVerticalRectangleFill();
    void removeVerticalRectangleFill();
    void createHorizontalRectangle();
    void createHorizontalRectangleFill();
    void removeHorizontalRectangleFill();
    void createL_Shape();
    void createMirroredL_Shape();
    void createS_Shape();
    void createZ_Shape();
    void createT_Shape();
    void createBoxShape();
    void createLineShape();

    QColor effectFillColor;
    QColor effectBorderColor;

    bool noFill, fillable;
};

#endif // shapeEFFECTDIALOG_H
