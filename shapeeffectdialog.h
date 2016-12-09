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
    void on_pushButton_up_clicked();
    void on_pushButton_down_clicked();
    void on_pushButton_left_clicked();
    void on_pushButton_right_clicked();
    void on_pushButton_color_clicked();
    void on_comboBox_activated(int index);
    void on_pushButton_clicked();
    void on_comboBox_2_activated(int index);


    void on_pushButton_color_2_clicked();

private:
    Ui::shapeEffectDialog *ui;
    effect* retEffect;

    int offsetX;
    int offsetY;
    bool effectSelected;
    bool circleSelected;
    bool squareSelected;
    bool verRecSelected;
    bool horRecSelected;

    QColor effectFillColor;
    QColor effectBorderColor;

    void clearGrid();

    void updateGUI();
    bool isTouchingXBoundaries();
    bool isTouchingYBoundaries();
    void createCircle();
    void createSquare();
    void createVerticalRectangle();
    void createHorizontalRectangle();
    void createL_Shape();
    void createMirroredL_Shape();
    void createS_Shape();
    void createZ_Shape();
    void createT_Shape();
    void createBoxShape();
    void createLineShape();

};

#endif // shapeEFFECTDIALOG_H
