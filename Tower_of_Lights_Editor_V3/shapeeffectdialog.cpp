#include "shapeeffectdialog.h"
#include "ui_shapeeffectdialog.h"
#include <QDebug>

shapeEffectDialog::shapeEffectDialog(QColor frame[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS], QWidget *parent) :
    QDialog(parent),
    ui(new Ui::shapeEffectDialog)
{
    ui->setupUi(this);
    ui->noFill->setVisible(false);
    ui->label_2->setVisible(false);
    ui->pushButton_color->setVisible(false);
    setWindowIcon(QIcon(":/resources/icon.png"));
    retEffect = new effect;
    for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
        for (int x = 0; x < TAN_DEFAULT_COLS; x++)
            retEffect->pixels[x][y] = QColor(0,0,0,0);
    retEffect->primary = QColor(0,0,0,0);
    retEffect->secondary = QColor(0,0,0,0);
    offsetX = 0;
    offsetY = 0;
    noFill = false;
    fillable = false;
    effectSelected = false;
    effectFillColor = QColor("#ffffff");
    effectBorderColor = QColor("#ffffff");
    for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
        for (int x = 0; x < TAN_DEFAULT_COLS; x++)
            backgroundFrame[x][y] = frame[x][y];

    //QFrame *m_Frame = ui->frame;
    QGridLayout *m_FrameLayout = ui->gridLayout;
    //QString m_cellName;
    QSizePolicy m_cellSizePolicy;
    QSize m_cellSize(15,15);
    ui->gridLayout->setSpacing(1);

    // Configure the size policy that every cell widget will use
    m_cellSizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
    m_cellSizePolicy.setHorizontalStretch(1);
    m_cellSizePolicy.setVerticalPolicy(QSizePolicy::Fixed);
    m_cellSizePolicy.setVerticalStretch(1);
    m_cellSizePolicy.setHeightForWidth(true);

    for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
    {
        for (int x = 0; x < TAN_DEFAULT_COLS; x++)
        {
            // Generate the name for each cell, based on rows and cols
            // Relocate this job to TanFrame project at some point?
            //m_cellName = "cell" + (QString("%1").arg((i*TAN_DEFAULT_COLS + j), 3, 10, QChar('0')));
            QWidget *m_cellWidget = new QWidget;
            m_cellWidget->setMinimumSize(m_cellSize);
            m_cellWidget->setSizePolicy(m_cellSizePolicy);
            // Adding cell widget to the frame's gridLayout
            m_FrameLayout->addWidget(m_cellWidget, y, x);
            m_cellWidget->show();
            m_FrameLayout->update();
        }
    }
    updateGUI();
}

shapeEffectDialog::~shapeEffectDialog()
{
    delete ui;
}

void shapeEffectDialog::on_buttonBox_accepted()
{
    if (effectSelected)
    {
        QColor backup[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS];
        for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
            for (int x = 0; x < TAN_DEFAULT_COLS; x++)
                backup[x][y] = retEffect->pixels[x][y];
        for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
            for (int x = 0; x < TAN_DEFAULT_COLS; x++)
                retEffect->pixels[x][y] = backup[(x-offsetX)%TAN_DEFAULT_COLS][(y-offsetY)%TAN_DEFAULT_ROWS];
        emit accepted(retEffect);
    }
}

void shapeEffectDialog::on_pushButton_up_clicked()
{
    offsetY--;
    if (isTouchingYBoundaries())
        ui->pushButton_up->setEnabled(false);
    ui->pushButton_down->setEnabled(true);
    updateGUI();
}

void shapeEffectDialog::on_pushButton_down_clicked()
{
    offsetY++;
    if (isTouchingYBoundaries())
        ui->pushButton_down->setEnabled(false);
    ui->pushButton_up->setEnabled(true);
    updateGUI();
}

void shapeEffectDialog::on_pushButton_left_clicked()
{
    offsetX--;
    if (isTouchingXBoundaries())
        ui->pushButton_left->setEnabled(false);
    ui->pushButton_right->setEnabled(true);
    updateGUI();
}

void shapeEffectDialog::on_pushButton_right_clicked()
{
    offsetX++;
    if (isTouchingXBoundaries())
        ui->pushButton_right->setEnabled(false);
    ui->pushButton_left->setEnabled(true);
    updateGUI();
}

bool shapeEffectDialog::isTouchingXBoundaries()
{
    for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
        for (int x = 0; x < TAN_DEFAULT_COLS; x++)
            if (retEffect->pixels[x][y].alpha() == 255 && ((x+offsetX) == 0 || (x+offsetX) == (TAN_DEFAULT_COLS-1)))
                return true;
    return false;
}

bool shapeEffectDialog::isTouchingYBoundaries()
{
    for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
        for (int x = 0; x < TAN_DEFAULT_COLS; x++)
            if (retEffect->pixels[x][y].alpha() == 255 && ((y+offsetY) == 0 || (y+offsetY) == (TAN_DEFAULT_ROWS-1)))
                return true;
    return false;
}

//change fill color
void shapeEffectDialog::on_pushButton_color_clicked()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if(color.isValid())
    {
        effectFillColor = color;
        if (effectSelected && !noFill)
        {
            switch(ui->comboBox->currentIndex())
            {
            case 0 :
                createCircleFill();
                break;
            case 1 :
                createSquareFill();
                break;
            case 2 :
                createVerticalRectangleFill();
                break;
            case 3 :
                createHorizontalRectangleFill();
                break;
            default:
                break;
            }
        }
        if (color.red() < 191 && color.green() < 191 && color.blue() < 191)
            ui->pushButton_color->setStyleSheet("color: #ffffff; background-color: " + color.name());
        else ui->pushButton_color->setStyleSheet("color: #000000; background-color: " + color.name());
        ui->pushButton_color->setText(color.name());
        updateGUI();
    }
}

//change border color
void shapeEffectDialog::on_pushButton_color_2_clicked()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this);
    if(color.isValid())
    {
        effectBorderColor = color;
        if (effectSelected && fillable && !noFill)
        {
            switch(ui->comboBox->currentIndex())
            {
            case 0 :
                createCircle();
                break;
            case 1 :
                createSquare();
                break;
            case 2 :
                createVerticalRectangle();
                break;
            case 3 :
                createHorizontalRectangle();
                break;
            default:
                break;
            }
        }
        else
        {
            for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
                for (int x = 0; x < TAN_DEFAULT_COLS; x++)
                    if (retEffect->pixels[x][y].alpha() == 255)
                        retEffect->pixels[x][y] = color;
        }
        if (color.red() < 191 && color.green() < 191 && color.blue() < 191)
            ui->pushButton_color_2->setStyleSheet("color: #ffffff; background-color: " + color.name());
        else ui->pushButton_color_2->setStyleSheet("color: #000000; background-color: " + color.name());
        ui->pushButton_color_2->setText(color.name());
        updateGUI();
    }
}

void shapeEffectDialog::on_noFill_stateChanged(int state)
{//state is 2 if checked, and 0 if unchecked
    if (state == 0)
    {
        noFill = false;
        if (effectSelected && fillable)
        {
            switch(ui->comboBox->currentIndex())
            {
            case 0 :
                createCircleFill();
                break;
            case 1 :
                createSquareFill();
                break;
            case 2 :
                createVerticalRectangleFill();
                break;
            case 3 :
                createHorizontalRectangleFill();
                break;
            default:
                break;
            }
        }
    }
    if (state == 2)
    {
        noFill = true;
        if (effectSelected && fillable)
        {
            switch(ui->comboBox->currentIndex())
            {
            case 0 :
                removeCircleFill();
                break;
            case 1 :
                removeSquareFill();
                break;
            case 2 :
                removeVerticalRectangleFill();
                break;
            case 3 :
                removeHorizontalRectangleFill();
                break;
            default:
                break;
            }
        }
    }
    updateGUI();
}

void shapeEffectDialog::updateGUI()
{
    QString qss;
    for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
    {
        for (int x = 0; x < TAN_DEFAULT_COLS; x++)
        {
            if (x < 8 && x > 3 && y < 15 && y > 4)
            {
                if (retEffect->pixels[(x+TAN_DEFAULT_COLS-offsetX)%TAN_DEFAULT_COLS][(y+TAN_DEFAULT_ROWS-offsetY)%TAN_DEFAULT_ROWS].alpha() == 255)
                    qss = QString("margin: 0px; border: 1px solid rgb(127,127,127); border-radius: 2px; background-color: " + retEffect->pixels[(x+TAN_DEFAULT_COLS-offsetX)%TAN_DEFAULT_COLS][(y+TAN_DEFAULT_ROWS-offsetY)%TAN_DEFAULT_ROWS].name());
                else qss = QString("margin: 0px; border: 1px solid rgb(127,127,127); border-radius: 2px; background-color: " + backgroundFrame[x][y].name());
            }
            else
            {
                if (retEffect->pixels[(x+TAN_DEFAULT_COLS-offsetX)%TAN_DEFAULT_COLS][(y+TAN_DEFAULT_ROWS-offsetY)%TAN_DEFAULT_ROWS].alpha() == 255)
                    qss = QString("margin: 0px; border: 1px solid rgb(0,0,0); border-radius: 2px; background-color: " + retEffect->pixels[(x+TAN_DEFAULT_COLS-offsetX)%TAN_DEFAULT_COLS][(y+TAN_DEFAULT_ROWS-offsetY)%TAN_DEFAULT_ROWS].name());
                else qss = QString("margin: 0px; border: 1px solid rgb(0,0,0); border-radius: 2px; background-color: " + backgroundFrame[x][y].name());
            }
            ui->gridLayout->itemAtPosition(y,x)->widget()->setStyleSheet(qss);
        }
    }
    if (effectSelected)
    {
        if (fillable)
        {
            ui->noFill->setVisible(true);
            ui->label_3->setText("Border Color:");
            if (noFill)
            {
                ui->pushButton_color->setVisible(false);
                ui->label_2->setVisible(false);
            }
            else
            {
                ui->pushButton_color->setVisible(true);
                ui->label_2->setVisible(true);
            }
        }
        else
        {
            ui->noFill->setVisible(false);
            ui->pushButton_color->setVisible(false);
            ui->label_2->setVisible(false);
            ui->label_3->setText("Effect Color:");
        }
    }
    else
    {
        ui->noFill->setVisible(false);
        ui->pushButton_color->setVisible(false);
        ui->label_2->setVisible(false);
        ui->label_3->setText("Effect Color:");
    }
}

//clear grid
void shapeEffectDialog::on_pushButton_clear_clicked()
{
    ui->pushButton_up->setEnabled(false);
    ui->pushButton_down->setEnabled(false);
    ui->pushButton_left->setEnabled(false);
    ui->pushButton_right->setEnabled(false);
    clearGrid();
    if (effectSelected) ui->comboBox->insertItem(0, "Select a shape");
    ui->comboBox->setCurrentIndex(0);
    effectSelected = false;
    fillable = false;
    updateGUI();
}

void shapeEffectDialog::clearGrid()
{
    offsetX = 0;
    offsetY = 0;
    for (int x = 0; x < TAN_DEFAULT_ROWS; x++)
        for (int y = 0; y < TAN_DEFAULT_COLS; y++)
            retEffect->pixels[y][x] = QColor(0,0,0,0);
}

void shapeEffectDialog::on_comboBox_activated(int index)
{
    if (!effectSelected)
    {
        if (index == 0) return;
        index--;
        ui->comboBox->removeItem(0);
    }
    ui->pushButton_up->setEnabled(true);
    ui->pushButton_down->setEnabled(true);
    ui->pushButton_left->setEnabled(true);
    ui->pushButton_right->setEnabled(true);
    clearGrid();
    effectSelected = true;
    switch(index)
    {
    case 0:
        fillable = true;
        createCircle();
        if (!noFill) createCircleFill();
        break;
    case 1:
        fillable = true;
        createSquare();
        if (!noFill) createSquareFill();
        break;
    case 2:
        fillable = true;
        createVerticalRectangle();
        if (!noFill) createVerticalRectangleFill();
        break;
    case 3:
        fillable = true;
        createHorizontalRectangle();
        if (!noFill) createHorizontalRectangleFill();
        break;
    case 4:
        fillable = false;
        createL_Shape();
        break;
    case 5:
        fillable = false;
        createMirroredL_Shape();
        break;
    case 6:
        fillable = false;
        createS_Shape();
        break;
    case 7:
        fillable = false;
        createZ_Shape();
        break;
    case 8:
        fillable = false;
        createT_Shape();
        break;
    case 9:
        fillable = false;
        createBoxShape();
        break;
    case 10:
        fillable = false;
        createLineShape();
        break;
    default:
        break;
    }
    updateGUI();
}

//all shapes
void shapeEffectDialog::createCircle()
{
    //border
    retEffect->pixels[4][9] = effectBorderColor;
    retEffect->pixels[4][10] = effectBorderColor;
    retEffect->pixels[5][8] = effectBorderColor;
    retEffect->pixels[6][8] = effectBorderColor;
    retEffect->pixels[7][9] = effectBorderColor;
    retEffect->pixels[7][10] = effectBorderColor;
    retEffect->pixels[5][11] = effectBorderColor;
    retEffect->pixels[6][11] = effectBorderColor;
}

void shapeEffectDialog::createCircleFill()
{
    retEffect->pixels[5][9] = effectFillColor;
    retEffect->pixels[6][9] = effectFillColor;
    retEffect->pixels[5][10] = effectFillColor;
    retEffect->pixels[6][10] = effectFillColor;
}

void shapeEffectDialog::removeCircleFill()
{
    retEffect->pixels[5][9] = QColor(0,0,0,0);
    retEffect->pixels[6][9] = QColor(0,0,0,0);
    retEffect->pixels[5][10] = QColor(0,0,0,0);
    retEffect->pixels[6][10] = QColor(0,0,0,0);
}

void shapeEffectDialog::createSquare()
{
    //border
    retEffect->pixels[4][8] = effectBorderColor;
    retEffect->pixels[5][8] = effectBorderColor;
    retEffect->pixels[6][8] = effectBorderColor;
    retEffect->pixels[7][8] = effectBorderColor;
    retEffect->pixels[4][9] = effectBorderColor;
    retEffect->pixels[7][9] = effectBorderColor;
    retEffect->pixels[4][10] = effectBorderColor;
    retEffect->pixels[7][10] = effectBorderColor;
    retEffect->pixels[4][11] = effectBorderColor;
    retEffect->pixels[5][11] = effectBorderColor;
    retEffect->pixels[6][11] = effectBorderColor;
    retEffect->pixels[7][11] = effectBorderColor;
}

void shapeEffectDialog::createSquareFill()
{
    retEffect->pixels[5][9] = effectFillColor;
    retEffect->pixels[6][9] = effectFillColor;
    retEffect->pixels[5][10] = effectFillColor;
    retEffect->pixels[6][10] = effectFillColor;
}

void shapeEffectDialog::removeSquareFill()
{
    retEffect->pixels[5][9] = QColor(0,0,0,0);
    retEffect->pixels[6][9] = QColor(0,0,0,0);
    retEffect->pixels[5][10] = QColor(0,0,0,0);
    retEffect->pixels[6][10] = QColor(0,0,0,0);
}

//Vertical Rectangle
void shapeEffectDialog::createVerticalRectangle()
{
    //border
    retEffect->pixels[4][7] = effectBorderColor;
    retEffect->pixels[5][7] = effectBorderColor;
    retEffect->pixels[6][7] = effectBorderColor;
    retEffect->pixels[7][7] = effectBorderColor;
    retEffect->pixels[4][8] = effectBorderColor;
    retEffect->pixels[7][8] = effectBorderColor;
    retEffect->pixels[4][9] = effectBorderColor;
    retEffect->pixels[7][9] = effectBorderColor;
    retEffect->pixels[4][10] = effectBorderColor;
    retEffect->pixels[7][10] = effectBorderColor;
    retEffect->pixels[4][11] = effectBorderColor;
    retEffect->pixels[7][11] = effectBorderColor;
    retEffect->pixels[4][12] = effectBorderColor;
    retEffect->pixels[5][12] = effectBorderColor;
    retEffect->pixels[6][12] = effectBorderColor;
    retEffect->pixels[7][12] = effectBorderColor;
}

void shapeEffectDialog::createVerticalRectangleFill()
{
    retEffect->pixels[5][8] = effectFillColor;
    retEffect->pixels[6][8] = effectFillColor;
    retEffect->pixels[5][9] = effectFillColor;
    retEffect->pixels[6][9] = effectFillColor;
    retEffect->pixels[5][10] = effectFillColor;
    retEffect->pixels[6][10] = effectFillColor;
    retEffect->pixels[5][11] = effectFillColor;
    retEffect->pixels[6][11] = effectFillColor;
}

void shapeEffectDialog::removeVerticalRectangleFill()
{
    retEffect->pixels[5][8] = QColor(0,0,0,0);
    retEffect->pixels[6][8] = QColor(0,0,0,0);
    retEffect->pixels[5][9] = QColor(0,0,0,0);
    retEffect->pixels[6][9] = QColor(0,0,0,0);
    retEffect->pixels[5][10] = QColor(0,0,0,0);
    retEffect->pixels[6][10] = QColor(0,0,0,0);
    retEffect->pixels[5][11] = QColor(0,0,0,0);
    retEffect->pixels[6][11] = QColor(0,0,0,0);
}

void shapeEffectDialog::createHorizontalRectangle()
{
    //border
    retEffect->pixels[4][8] = effectBorderColor;
    retEffect->pixels[5][8] = effectBorderColor;
    retEffect->pixels[6][8] = effectBorderColor;
    retEffect->pixels[7][8] = effectBorderColor;
    retEffect->pixels[4][9] = effectBorderColor;
    retEffect->pixels[7][9] = effectBorderColor;
    retEffect->pixels[4][10] = effectBorderColor;
    retEffect->pixels[5][10] = effectBorderColor;
    retEffect->pixels[6][10] = effectBorderColor;
    retEffect->pixels[7][10] = effectBorderColor;
}

void shapeEffectDialog::createHorizontalRectangleFill()
{
    retEffect->pixels[5][9] = effectFillColor;
    retEffect->pixels[6][9] = effectFillColor;
}

void shapeEffectDialog::removeHorizontalRectangleFill()
{
    retEffect->pixels[5][9] = QColor(0,0,0,0);
    retEffect->pixels[6][9] = QColor(0,0,0,0);
}

void shapeEffectDialog::createL_Shape()
{
    retEffect->pixels[5][9] = effectBorderColor;
    retEffect->pixels[5][10] = effectBorderColor;
    retEffect->pixels[5][11] = effectBorderColor;
    retEffect->pixels[6][11] = effectBorderColor;
}
void shapeEffectDialog::createMirroredL_Shape()
{
    retEffect->pixels[6][9] = effectBorderColor;
    retEffect->pixels[6][10] = effectBorderColor;
    retEffect->pixels[6][11] = effectBorderColor;
    retEffect->pixels[5][11] = effectBorderColor;
}
void shapeEffectDialog::createS_Shape()
{
    retEffect->pixels[6][9] = effectBorderColor;
    retEffect->pixels[5][9] = effectBorderColor;
    retEffect->pixels[5][10] = effectBorderColor;
    retEffect->pixels[4][10] = effectBorderColor;
}
void shapeEffectDialog::createZ_Shape()
{
    retEffect->pixels[4][9] = effectBorderColor;
    retEffect->pixels[5][9] = effectBorderColor;
    retEffect->pixels[5][10] = effectBorderColor;
    retEffect->pixels[6][10] = effectBorderColor;
}
void shapeEffectDialog::createT_Shape()
{
    retEffect->pixels[4][10] = effectBorderColor;
    retEffect->pixels[5][10] = effectBorderColor;
    retEffect->pixels[6][10] = effectBorderColor;
    retEffect->pixels[5][9] = effectBorderColor;
}
void shapeEffectDialog::createBoxShape()
{
    retEffect->pixels[5][9] = effectBorderColor;
    retEffect->pixels[6][9] = effectBorderColor;
    retEffect->pixels[5][10] = effectBorderColor;
    retEffect->pixels[6][10] = effectBorderColor;
}
void shapeEffectDialog::createLineShape()
{
    retEffect->pixels[5][8] = effectBorderColor;
    retEffect->pixels[5][9] = effectBorderColor;
    retEffect->pixels[5][10] = effectBorderColor;
    retEffect->pixels[5][11] = effectBorderColor;
}
