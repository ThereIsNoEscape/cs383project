#include "symboleffectdialog.h"
#include "ui_symboleffectdialog.h"

symbolEffectDialog::symbolEffectDialog(QColor frame[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS], QWidget *parent) :
    QDialog(parent),
    ui(new Ui::symbolEffectDialog)
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

    for (int y = 0; y < (TAN_DEFAULT_ROWS); y++)
    {
        for (int x = 0; x < (TAN_DEFAULT_COLS); x++)
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

symbolEffectDialog::~symbolEffectDialog()
{
    delete ui;
}

void symbolEffectDialog::on_buttonBox_accepted()
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

void symbolEffectDialog::on_pushButton_up_clicked()
{
    offsetY--;
    if (isTouchingYBoundaries())
        ui->pushButton_up->setEnabled(false);
    ui->pushButton_down->setEnabled(true);
    updateGUI();
}

void symbolEffectDialog::on_pushButton_down_clicked()
{
    offsetY++;
    if (isTouchingYBoundaries())
        ui->pushButton_down->setEnabled(false);
    ui->pushButton_up->setEnabled(true);
    updateGUI();
}

void symbolEffectDialog::on_pushButton_left_clicked()
{
    offsetX--;
    if (isTouchingXBoundaries())
        ui->pushButton_left->setEnabled(false);
    ui->pushButton_right->setEnabled(true);
    updateGUI();
}

void symbolEffectDialog::on_pushButton_right_clicked()
{
    offsetX++;
    if (isTouchingXBoundaries())
        ui->pushButton_right->setEnabled(false);
    ui->pushButton_left->setEnabled(true);
    updateGUI();
}

bool symbolEffectDialog::isTouchingXBoundaries()
{
    for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
        for (int x = 0; x < TAN_DEFAULT_COLS; x++)
            if (retEffect->pixels[x][y].alpha() == 255 && ((x+offsetX) == 0 || (x+offsetX) == (TAN_DEFAULT_COLS-1)))
                return true;
    return false;
}

bool symbolEffectDialog::isTouchingYBoundaries()
{
    for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
        for (int x = 0; x < TAN_DEFAULT_COLS; x++)
            if (retEffect->pixels[x][y].alpha() == 255 && ((y+offsetY) == 0 || (y+offsetY) == (TAN_DEFAULT_ROWS-1)))
                return true;
    return false;
}

void symbolEffectDialog::on_pushButton_color_clicked()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if(color.isValid())
    {
        effectColor = color;
        for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
            for (int x = 0; x < TAN_DEFAULT_COLS; x++)
                if (retEffect->pixels[x][y].alpha() == 255)
                    retEffect->pixels[x][y] = color;
        if (color.red() < 191 && color.green() < 191 && color.blue() < 191)
            ui->pushButton_color->setStyleSheet("color: #ffffff; background-color: " + color.name());
        else ui->pushButton_color->setStyleSheet("color: #000000; background-color: " + color.name());
        ui->pushButton_color->setText(color.name());
        updateGUI();
    }
}

//clear grid
void symbolEffectDialog::on_pushButton_clear_clicked()
{
    ui->pushButton_up->setEnabled(false);
    ui->pushButton_down->setEnabled(false);
    ui->pushButton_left->setEnabled(false);
    ui->pushButton_right->setEnabled(false);
    clearGrid();
    if (effectSelected) ui->comboBox->insertItem(0, "Select a symbol");
    ui->comboBox->setCurrentIndex(0);
    effectSelected = false;
    updateGUI();
}

void symbolEffectDialog::clearGrid()
{
    offsetX = 0;
    offsetY = 0;
    for (int x = 0; x < TAN_DEFAULT_ROWS; x++)
        for (int y = 0; y < TAN_DEFAULT_COLS; y++)
            retEffect->pixels[y][x] = QColor(0,0,0,0);
}

void symbolEffectDialog::updateGUI()
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

void symbolEffectDialog::on_comboBox_activated(int index)
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

    switch (index)
    {
    case 0: // Question Mark
        retEffect->pixels[4][8] = effectColor;
        retEffect->pixels[5][7] = effectColor;
        retEffect->pixels[6][8] = effectColor;
        retEffect->pixels[6][9] = effectColor;
        retEffect->pixels[5][10] = effectColor;
        retEffect->pixels[5][12] = effectColor;
        break;
    case 1:  // Exclamation Mark
        retEffect->pixels[4][7] = effectColor;
        retEffect->pixels[4][8] = effectColor;
        retEffect->pixels[4][9] = effectColor;
        retEffect->pixels[4][10] = effectColor;
        retEffect->pixels[4][12] = effectColor;
        break;
    case 2: // Dollar Sign
        retEffect->pixels[6][7] = effectColor;
        retEffect->pixels[5][8] = effectColor;
        retEffect->pixels[6][8] = effectColor;
        retEffect->pixels[7][8] = effectColor;
        retEffect->pixels[4][9] = effectColor;
        retEffect->pixels[6][9] = effectColor;
        retEffect->pixels[5][10] = effectColor;
        retEffect->pixels[6][10] = effectColor;
        retEffect->pixels[7][10] = effectColor;
        retEffect->pixels[6][11] = effectColor;
        retEffect->pixels[7][11] = effectColor;
        retEffect->pixels[5][12] = effectColor;
        retEffect->pixels[6][12] = effectColor;
        break;
    case 3: // Percent Sign
        retEffect->pixels[4][9] = effectColor;
        retEffect->pixels[7][9] = effectColor;
        retEffect->pixels[6][10] = effectColor;
        retEffect->pixels[5][11] = effectColor;
        retEffect->pixels[4][12] = effectColor;
        retEffect->pixels[7][12] = effectColor;
        break;
    case 4: // Left Paren
        retEffect->pixels[5][7] = effectColor;
        retEffect->pixels[4][8] = effectColor;
        retEffect->pixels[4][9] = effectColor;
        retEffect->pixels[4][10] = effectColor;
        retEffect->pixels[4][11] = effectColor;
        retEffect->pixels[5][12] = effectColor;
        break;
    case 5: // Right Paren
        retEffect->pixels[4][7] = effectColor;
        retEffect->pixels[5][8] = effectColor;
        retEffect->pixels[5][9] = effectColor;
        retEffect->pixels[5][10] = effectColor;
        retEffect->pixels[5][11] = effectColor;
        retEffect->pixels[4][12] = effectColor;
        break;
    case 6: // Left Square Bracket
        retEffect->pixels[4][7] = effectColor;
        retEffect->pixels[5][7] = effectColor;
        retEffect->pixels[4][8] = effectColor;
        retEffect->pixels[4][9] = effectColor;
        retEffect->pixels[4][10] = effectColor;
        retEffect->pixels[4][11] = effectColor;
        retEffect->pixels[4][12] = effectColor;
        retEffect->pixels[5][12] = effectColor;
        break;
    case 7: // Right Square Bracket
        retEffect->pixels[4][7] = effectColor;
        retEffect->pixels[5][7] = effectColor;
        retEffect->pixels[5][8] = effectColor;
        retEffect->pixels[5][9] = effectColor;
        retEffect->pixels[5][10] = effectColor;
        retEffect->pixels[5][11] = effectColor;
        retEffect->pixels[4][12] = effectColor;
        retEffect->pixels[5][12] = effectColor;
        break;
    case 8: // Plus Sign
        retEffect->pixels[5][8] = effectColor;
        retEffect->pixels[4][9] = effectColor;
        retEffect->pixels[5][9] = effectColor;
        retEffect->pixels[6][9] = effectColor;
        retEffect->pixels[5][10] = effectColor;
        break;
    case 9: // Minus Sign
        retEffect->pixels[4][9] = effectColor;
        retEffect->pixels[5][9] = effectColor;
        retEffect->pixels[6][9] = effectColor;
        break;
    case 10: // Equals Sign
        retEffect->pixels[4][8] = effectColor;
        retEffect->pixels[5][8] = effectColor;
        retEffect->pixels[6][8] = effectColor;
        retEffect->pixels[4][10] = effectColor;
        retEffect->pixels[5][10] = effectColor;
        retEffect->pixels[6][10] = effectColor;
        break;
    case 11: // Up Caret
        retEffect->pixels[5][8] = effectColor;
        retEffect->pixels[4][9] = effectColor;
        retEffect->pixels[6][9] = effectColor;
        break;
    case 12: // Left Caret
        retEffect->pixels[5][9] = effectColor;
        retEffect->pixels[4][10] = effectColor;
        retEffect->pixels[5][11] = effectColor;
        break;
    case 13: // Right Caret
        retEffect->pixels[4][9] = effectColor;
        retEffect->pixels[5][10] = effectColor;
        retEffect->pixels[4][11] = effectColor;
        break;
    case 14: // Left Hook Bracket
        retEffect->pixels[4][7] = effectColor;
        retEffect->pixels[5][7] = effectColor;
        retEffect->pixels[4][8] = effectColor;
        retEffect->pixels[4][9] = effectColor;
        retEffect->pixels[4][10] = effectColor;
        break;
    case 15: // Right Hook Bracket
        retEffect->pixels[4][7] = effectColor;
        retEffect->pixels[5][7] = effectColor;
        retEffect->pixels[5][8] = effectColor;
        retEffect->pixels[5][9] = effectColor;
        retEffect->pixels[5][10] = effectColor;
        break;
    case 16: // Forward Slash
        retEffect->pixels[6][7] = effectColor;
        retEffect->pixels[6][8] = effectColor;
        retEffect->pixels[5][9] = effectColor;
        retEffect->pixels[5][10] = effectColor;
        retEffect->pixels[4][11] = effectColor;
        retEffect->pixels[4][12] = effectColor;
        break;
    case 17: // Backwards Slash
        retEffect->pixels[4][7] = effectColor;
        retEffect->pixels[4][8] = effectColor;
        retEffect->pixels[5][9] = effectColor;
        retEffect->pixels[5][10] = effectColor;
        retEffect->pixels[6][11] = effectColor;
        retEffect->pixels[6][12] = effectColor;
        break;
    case 18: // Semicolon
        retEffect->pixels[5][9] = effectColor;
        retEffect->pixels[5][11] = effectColor;
        retEffect->pixels[4][12] = effectColor;
        break;
    case 19: // Colon
        retEffect->pixels[4][9] = effectColor;
        retEffect->pixels[4][11] = effectColor;
        break;
    case 20: // Asterisk
        retEffect->pixels[4][8] = effectColor;
        retEffect->pixels[6][8] = effectColor;
        retEffect->pixels[8][8] = effectColor;
        retEffect->pixels[5][9] = effectColor;
        retEffect->pixels[6][9] = effectColor;
        retEffect->pixels[7][9] = effectColor;
        retEffect->pixels[5][10] = effectColor;
        retEffect->pixels[6][10] = effectColor;
        retEffect->pixels[7][10] = effectColor;
        retEffect->pixels[4][11] = effectColor;
        retEffect->pixels[6][11] = effectColor;
        retEffect->pixels[8][11] = effectColor;
        break;
    case 21: // Bar
        retEffect->pixels[4][7] = effectColor;
        retEffect->pixels[4][8] = effectColor;
        retEffect->pixels[4][9] = effectColor;
        retEffect->pixels[4][10] = effectColor;
        retEffect->pixels[4][11] = effectColor;
        retEffect->pixels[4][12] = effectColor;
        break;
    case 22: // Tetris I
        retEffect->pixels[4][8] = effectColor;
        retEffect->pixels[4][9] = effectColor;
        retEffect->pixels[4][10] = effectColor;
        retEffect->pixels[4][11] = effectColor;
        break;
    case 23: // Tetris O
        retEffect->pixels[4][9] = effectColor;
        retEffect->pixels[5][9] = effectColor;
        retEffect->pixels[4][10] = effectColor;
        retEffect->pixels[5][10] = effectColor;
        break;
    case 24: // Tetris T
        retEffect->pixels[5][9] = effectColor;
        retEffect->pixels[4][10] = effectColor;
        retEffect->pixels[5][10] = effectColor;
        retEffect->pixels[6][10] = effectColor;
        break;
    case 25: // Tetris S
        retEffect->pixels[5][9] = effectColor;
        retEffect->pixels[6][9] = effectColor;
        retEffect->pixels[4][10] = effectColor;
        retEffect->pixels[5][10] = effectColor;
        break;
    case 26: // Tetris Z
        retEffect->pixels[4][9] = effectColor;
        retEffect->pixels[5][9] = effectColor;
        retEffect->pixels[5][10] = effectColor;
        retEffect->pixels[6][10] = effectColor;
        break;
    case 27: // Tetris J
        retEffect->pixels[5][8] = effectColor;
        retEffect->pixels[5][9] = effectColor;
        retEffect->pixels[5][10] = effectColor;
        retEffect->pixels[4][10] = effectColor;
        break;
    case 28: // Tetris L
        retEffect->pixels[4][8] = effectColor;
        retEffect->pixels[4][9] = effectColor;
        retEffect->pixels[4][10] = effectColor;
        retEffect->pixels[5][10] = effectColor;
        break;
    default:
        break;
    }
    updateGUI();
}
