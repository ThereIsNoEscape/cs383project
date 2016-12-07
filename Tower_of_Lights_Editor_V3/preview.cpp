#include "preview.h"
#include "ui_preview.h"

Preview::Preview(TanFile* project, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preview)
{
    ui->setupUi(this);

    file = project;

    file->currFrame = file->m_frames.begin();

    playing = false;

    //QFrame *m_Frame = ui->frame;
    QGridLayout *m_FrameLayout = ui->gridLayout;
    //QString m_cellName;
    QSizePolicy m_cellSizePolicy;
    QSize m_cellSize(38,38);

    // Configure the size policy that every cell widget will use
    m_cellSizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
    m_cellSizePolicy.setHorizontalStretch(1);
    m_cellSizePolicy.setVerticalPolicy(QSizePolicy::Fixed);
    m_cellSizePolicy.setVerticalStretch(1);
    m_cellSizePolicy.setHeightForWidth(true);

    QString qss;

    for (int y = 0; y < (TAN_DEFAULT_ROWS/2); y++)
    {
        for (int x = 0; x < (TAN_DEFAULT_COLS/3); x++)
        {
            // Generate the name for each cell, based on rows and cols
            // Relocate this job to TanFrame project at some point?
            //m_cellName = "cell" + (QString("%1").arg((i*TAN_DEFAULT_COLS + j), 3, 10, QChar('0')));
            QWidget *m_cellWidget = new QWidget;
            m_cellWidget->setMinimumSize(m_cellSize);
            m_cellWidget->setSizePolicy(m_cellSizePolicy);

            qss = ("margin: 0px; border: 2px solid rgb(127,127,127); border-radius: 4px; background-color: #" + (*file->currFrame)->pixels[x][y].color.name());

            m_cellWidget->setStyleSheet(qss);
            // Adding cell widget to the frame's gridLayout
            m_FrameLayout->addWidget(m_cellWidget, y, x);
            m_cellWidget->show();
            m_FrameLayout->update();
        }
    }
}

Preview::~Preview()
{
    delete ui;
}

void Preview::on_pushButton_close_clicked()
{
    close();
}

void Preview::on_pushButton_play_clicked()
{
    if (playing)
    {
        playing = false;
    }
    else
    {
        playing = true;

    }
}

void Preview::on_pushButton_back1_clicked()
{

}

void Preview::on_pushButton_back10_clicked()
{

}

void Preview::on_pushButton_forward1_clicked()
{

}

void Preview::on_pushButton_forward10_clicked()
{

}
