#include "symboleffectdialog.h"
#include "ui_symboleffectdialog.h"

symbolEffectDialog::symbolEffectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::symbolEffectDialog)
{
    ui->setupUi(this);
    retEffect = new effect;
    for (int x = 0; x < TAN_DEFAULT_ROWS; x++)
        for (int y = 0; y < TAN_DEFAULT_COLS; y++)
            retEffect->pixels[y][x] = QColor(0,0,0,0);
    retEffect->primary = QColor(0,0,0,0);
    retEffect->secondary = QColor(0,0,0,0);
    int offsetX = 0;
    int offsetY = 0;
    effectSelected = false;

    int i = 0, j = 0;
    //QFrame *m_Frame = ui->frame;
    QGridLayout *m_FrameLayout = ui->gridLayout;
    //QString m_cellName;
    QSizePolicy m_cellSizePolicy;
    QSize m_cellSize(16,16);

    // Configure the size policy that every cell widget will use
    m_cellSizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
    m_cellSizePolicy.setHorizontalStretch(1);
    m_cellSizePolicy.setVerticalPolicy(QSizePolicy::Fixed);
    m_cellSizePolicy.setVerticalStretch(1);
    m_cellSizePolicy.setHeightForWidth(true);

    QString qss;

    for (i=0; i<(TAN_DEFAULT_ROWS/2); i++)
    {
        for (j=0; j<(TAN_DEFAULT_COLS/3); j++)
        {
            // Generate the name for each cell, based on rows and cols
            // Relocate this job to TanFrame project at some point?
            //m_cellName = "cell" + (QString("%1").arg((i*TAN_DEFAULT_COLS + j), 3, 10, QChar('0')));
            QWidget *m_cellWidget = new QWidget;
            m_cellWidget->setMinimumSize(m_cellSize);
            m_cellWidget->setSizePolicy(m_cellSizePolicy);

            qss = QString("margin: 0px; border: 3px solid rgb(0,0,0); border-radius: 4px; background-color: #000000;");
            m_cellWidget->setStyleSheet(qss);
            //m_cellWidget->setStyleSheet("background-color: #000000");
            // Adding cell widget to the frame's gridLayout
            m_FrameLayout->addWidget(m_cellWidget, i, j);
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
        emit accepted(retEffect);
}

void symbolEffectDialog:: on_pushButton_test_clicked()
{
    ui->label->move(QPoint(180,120));
    ui->pushButton_test->setEnabled(false);
    ui->label->setText(QString("Good because that's the\nonly effect we've got"));

    effectSelected = true;

    retEffect->pixels[4][8] = QColor(165,190,165,255);
    retEffect->pixels[5][7] = QColor(190,155,155,255);
    retEffect->pixels[6][8] = QColor(145,145,190,255);
    retEffect->pixels[6][9] = QColor(135,135,190,255);
    retEffect->pixels[5][10] = QColor(190,125,125,255);
    retEffect->pixels[5][12] = QColor(190,115,115,255);

    updateGUI();
}

void symbolEffectDialog::on_pushButton_up_clicked()
{
    //offsetY--;
}

void symbolEffectDialog::on_pushButton_down_clicked()
{
    //offsetY++;
}

void symbolEffectDialog::on_pushButton_left_clicked()
{
    //offsetX--;
}

void symbolEffectDialog::on_pushButton_right_clicked()
{
    //offsetX++;
}

void symbolEffectDialog::updateGUI()
{
    for (int y = 0; y < (TAN_DEFAULT_ROWS/2); y++)
        for (int x = 0; x < (TAN_DEFAULT_COLS/3); x++)
            ui->gridLayout->itemAtPosition(y,x)->widget()->setStyleSheet("background-color: " + retEffect->pixels[x+4][y+5].name());
}
