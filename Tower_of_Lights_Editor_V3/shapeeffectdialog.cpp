#include "shapeeffectdialog.h"
#include "ui_shapeeffectdialog.h"
#include <QDebug>

shapeEffectDialog::shapeEffectDialog(QColor frame[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS], QWidget *parent) :
    QDialog(parent),
    ui(new Ui::shapeEffectDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/resources/icon.png"));
    retEffect = new effect;
    for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
        for (int x = 0; x < TAN_DEFAULT_COLS; x++)
            retEffect->pixels[x][y] = QColor(0,0,0,0);
    retEffect->primary = QColor(0,0,0,0);
    retEffect->secondary = QColor(0,0,0,0);
    offsetX = 0;
    offsetY = 0;
    effectSelected = false;
    effectColor = QColor("#ffffff");
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

    QString qss;

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

            if (x < 8 && x > 3 && y < 15 && y > 4)
                qss = QString("margin: 0px; border: 1px solid rgb(127,127,127); border-radius: 2px; background-color: " + backgroundFrame[x][y].name());
            else qss = QString("margin: 0px; border: 1px solid rgb(0,0,0); border-radius: 2px; background-color: " + backgroundFrame[x][y].name());

            m_cellWidget->setStyleSheet(qss);
            // Adding cell widget to the frame's gridLayout
            m_FrameLayout->addWidget(m_cellWidget, y, x);
            m_cellWidget->show();
            m_FrameLayout->update();
        }
    }
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
    {
        for (int x = 0; x < TAN_DEFAULT_COLS; x++)
        {
            if (retEffect->pixels[x][y].alpha() == 255 && ((x+offsetX) == 0 || (x+offsetX) == (TAN_DEFAULT_COLS-1)))
            {
                return true;
            }
        }
    }
    return false;
}

bool shapeEffectDialog::isTouchingYBoundaries()
{
    for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
    {
        for (int x = 0; x < TAN_DEFAULT_COLS; x++)
        {
            if (retEffect->pixels[x][y].alpha() == 255 && ((y+offsetY) == 0 || (y+offsetY) == (TAN_DEFAULT_ROWS-1)))
            {
                return true;
            }
        }
    }
    return false;
}

//change fill color
void shapeEffectDialog::on_pushButton_color_clicked()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if(color.isValid())
    {
        effectFillColor = color;
        /*
        for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
            for (int x = 0; x < TAN_DEFAULT_COLS; x++)
                if (retEffect->pixels[x][y].alpha() == 255)
                    retEffect->pixels[x][y] = color;
        */
        if (color.red() < 191 && color.green() < 191 && color.blue() < 191)
            ui->pushButton_color->setStyleSheet("color: #ffffff; background-color: " + color.name());
        else ui->pushButton_color->setStyleSheet("color: #000000; background-color: " + color.name());
        ui->pushButton_color->setText(color.name());

    }
}

//change border color
void shapeEffectDialog::on_pushButton_color_2_clicked()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this);
    if(color.isValid())
    {
        effectBorderColor = color;
        for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
            for (int x = 0; x < TAN_DEFAULT_COLS; x++)
                if (retEffect->pixels[x][y].alpha() == 255)
                    retEffect->pixels[x][y] = color;
        if (color.red() < 191 && color.green() < 191 && color.blue() < 191)
            ui->pushButton_color_2->setStyleSheet("color: #ffffff; background-color: " + color.name());
        else ui->pushButton_color_2->setStyleSheet("color: #000000; background-color: " + color.name());
        ui->pushButton_color->setText(color.name());

    }
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
}

//clear grid
void shapeEffectDialog::on_pushButton_clicked()
{
    clearGrid();
}

void shapeEffectDialog::clearGrid()
{
    for (int x = 0; x < TAN_DEFAULT_ROWS; x++)
        for (int y = 0; y < TAN_DEFAULT_COLS; y++)
            retEffect->pixels[y][x] = QColor(0,0,0,0);
    /*
    circleSelected = false;
    squareSelected = false;
    verRecSelected = false;
    horRecSelected = false;
    */
    updateGUI();
}

void shapeEffectDialog::on_comboBox_activated(int index)
{
    clearGrid();
    updateGUI();
    /*
    circleSelected = false;
    squareSelected = false;
    verRecSelected = false;
    horRecSelected = false;
    */
    switch(index){
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
        ;
    }
}

void shapeEffectDialog::on_comboBox_2_activated(int index)
{
    clearGrid();
    updateGUI();
    switch(index){
      case 0 :
        createL_Shape();
        break;
      case 1 :
        createMirroredL_Shape();
        break;
      case 2 :
        createS_Shape();
        break;
      case 3 :
        createZ_Shape();
        break;
      case 4 :
        createT_Shape();
        break;
      case 5 :
        createBoxShape();
        break;
      case 6 :
        createLineShape();
        break;
      default:
        ;
    }
}


//all shapes

void shapeEffectDialog::createCircle()
{
    ui->pushButton_up->setEnabled(true);
    ui->pushButton_down->setEnabled(true);
    ui->pushButton_left->setEnabled(true);
    ui->pushButton_right->setEnabled(true);

    effectSelected = true;
    //circleSelected = true;

    if(ui->noFill->checkState() == Qt::Unchecked){
        //border
        retEffect->pixels[4][9] = effectBorderColor;
        retEffect->pixels[4][10] = effectBorderColor;
        retEffect->pixels[5][8] = effectBorderColor;
        retEffect->pixels[6][8] = effectBorderColor;
        retEffect->pixels[7][9] = effectBorderColor;
        retEffect->pixels[7][10] = effectBorderColor;
        retEffect->pixels[5][11] = effectBorderColor;
        retEffect->pixels[6][11] = effectBorderColor;

        //area
        retEffect->pixels[5][9] = effectFillColor;
        retEffect->pixels[6][9] = effectFillColor;
        retEffect->pixels[5][10] = effectFillColor;
        retEffect->pixels[6][10] = effectFillColor;
        /*
        for(int i = 5; i < 7; i++)          //x direction
            for(int j = 8; j < 12; j++){    //y direction
                retEffect->pixels[i][j] = effectColor;
        for(int i = 4; i < 8; i++)          //x direction
            for(int j = 9; j < 11; j++)     //y direction
                retEffect->pixels[i][j] = effectColor;
        qDebug() << "circle";
        */
    }else{
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
    updateGUI();
}

void shapeEffectDialog::createSquare()
{
    ui->pushButton_up->setEnabled(true);
    ui->pushButton_down->setEnabled(true);
    ui->pushButton_left->setEnabled(true);
    ui->pushButton_right->setEnabled(true);

    effectSelected = true;
    //squareSelected = true;

    if(ui->noFill->checkState() == Qt::Unchecked){

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

        //area
        retEffect->pixels[5][9] = effectFillColor;
        retEffect->pixels[6][9] = effectFillColor;
        retEffect->pixels[5][10] = effectFillColor;
        retEffect->pixels[6][10] = effectFillColor;

        /*
        for(int i = 4; i < 8; i++)          //x direction
            for(int j = 8; j < 12; j++)     //y direction
                retEffect->pixels[i][j] = effectColor;
        */
    }else{
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

    updateGUI();
    qDebug() << "square";
}

//Vertical Rectangle
void shapeEffectDialog::createVerticalRectangle()
{
    ui->pushButton_up->setEnabled(true);
    ui->pushButton_down->setEnabled(true);
    ui->pushButton_left->setEnabled(true);
    ui->pushButton_right->setEnabled(true);

    effectSelected = true;
    //verRecSelected = true;

    if(ui->noFill->checkState() == Qt::Unchecked){
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

        //area
        retEffect->pixels[5][8] = effectFillColor;
        retEffect->pixels[6][8] = effectFillColor;
        retEffect->pixels[5][9] = effectFillColor;
        retEffect->pixels[6][9] = effectFillColor;
        retEffect->pixels[5][10] = effectFillColor;
        retEffect->pixels[6][10] = effectFillColor;
        retEffect->pixels[5][11] = effectFillColor;
        retEffect->pixels[6][11] = effectFillColor;

        /*
        for(int i = 4; i < 8; i++)          //x direction
            for(int j = 7; j < 13; j++)     //y direction
                retEffect->pixels[i][j] = effectColor;
        */
    }else{
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

    updateGUI();
}

void shapeEffectDialog::createHorizontalRectangle()
{
    ui->pushButton_up->setEnabled(true);
    ui->pushButton_down->setEnabled(true);
    ui->pushButton_left->setEnabled(true);
    ui->pushButton_right->setEnabled(true);

    effectSelected = true;
    //horRecSelected = true;

    if(ui->noFill->checkState() == Qt::Unchecked){

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

        //area
        retEffect->pixels[5][9] = effectFillColor;
        retEffect->pixels[6][9] = effectFillColor;

        /*
        for(int i = 4; i < 8; i++)          //x direction
            for(int j = 8; j < 11; j++)     //y direction
                retEffect->pixels[i][j] = effectColor;
        */
    }else{
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

    updateGUI();
}

void shapeEffectDialog::createL_Shape()
{
    ui->pushButton_up->setEnabled(true);
    ui->pushButton_down->setEnabled(true);
    ui->pushButton_left->setEnabled(true);
    ui->pushButton_right->setEnabled(true);

    effectSelected = true;

    retEffect->pixels[5][9] = effectFillColor;
    retEffect->pixels[5][10] = effectFillColor;
    retEffect->pixels[5][11] = effectFillColor;
    retEffect->pixels[6][11] = effectFillColor;

    updateGUI();
}

void shapeEffectDialog::createMirroredL_Shape()
{
    ui->pushButton_up->setEnabled(true);
    ui->pushButton_down->setEnabled(true);
    ui->pushButton_left->setEnabled(true);
    ui->pushButton_right->setEnabled(true);

    effectSelected = true;

    retEffect->pixels[6][9] = effectFillColor;
    retEffect->pixels[6][10] = effectFillColor;
    retEffect->pixels[6][11] = effectFillColor;
    retEffect->pixels[5][11] = effectFillColor;

    updateGUI();
}


void shapeEffectDialog::createS_Shape()
{
    ui->pushButton_up->setEnabled(true);
    ui->pushButton_down->setEnabled(true);
    ui->pushButton_left->setEnabled(true);
    ui->pushButton_right->setEnabled(true);

    effectSelected = true;

    retEffect->pixels[6][9] = effectFillColor;
    retEffect->pixels[5][9] = effectFillColor;
    retEffect->pixels[5][10] = effectFillColor;
    retEffect->pixels[4][10] = effectFillColor;

    updateGUI();
}

void shapeEffectDialog::createZ_Shape()
{
    ui->pushButton_up->setEnabled(true);
    ui->pushButton_down->setEnabled(true);
    ui->pushButton_left->setEnabled(true);
    ui->pushButton_right->setEnabled(true);

    effectSelected = true;

    retEffect->pixels[4][9] = effectFillColor;
    retEffect->pixels[5][9] = effectFillColor;
    retEffect->pixels[5][10] = effectFillColor;
    retEffect->pixels[6][10] = effectFillColor;

    updateGUI();
}

void shapeEffectDialog::createT_Shape()
{
    ui->pushButton_up->setEnabled(true);
    ui->pushButton_down->setEnabled(true);
    ui->pushButton_left->setEnabled(true);
    ui->pushButton_right->setEnabled(true);

    effectSelected = true;

    retEffect->pixels[4][10] = effectFillColor;
    retEffect->pixels[5][10] = effectFillColor;
    retEffect->pixels[6][10] = effectFillColor;
    retEffect->pixels[5][9] = effectFillColor;

    updateGUI();
}

void shapeEffectDialog::createBoxShape()
{
    ui->pushButton_up->setEnabled(true);
    ui->pushButton_down->setEnabled(true);
    ui->pushButton_left->setEnabled(true);
    ui->pushButton_right->setEnabled(true);

    effectSelected = true;

    retEffect->pixels[5][9] = effectFillColor;
    retEffect->pixels[6][9] = effectFillColor;
    retEffect->pixels[5][10] = effectFillColor;
    retEffect->pixels[6][10] = effectFillColor;

    updateGUI();
}

void shapeEffectDialog::createLineShape()
{
    ui->pushButton_up->setEnabled(true);
    ui->pushButton_down->setEnabled(true);
    ui->pushButton_left->setEnabled(true);
    ui->pushButton_right->setEnabled(true);

    effectSelected = true;

    retEffect->pixels[5][8] = effectFillColor;
    retEffect->pixels[5][9] = effectFillColor;
    retEffect->pixels[5][10] = effectFillColor;
    retEffect->pixels[5][11] = effectFillColor;

    updateGUI();
}
