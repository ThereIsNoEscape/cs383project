#include "preview.h"
#include "ui_preview.h"

Preview::Preview(TanFile project, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preview)
{
    ui->setupUi(this);

    file = project;

    file.currFrame = file.m_frames.begin();

    t = new myThread;

    connect(t, SIGNAL(countdownDone()), this, SLOT(next_frame()));

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

            m_cellWidget->setStyleSheet(QString("margin: 0px; border: 2px solid rgb(127,127,127); border-radius: 4px; background-color: #00000"));
            // Adding cell widget to the frame's gridLayout
            m_FrameLayout->addWidget(m_cellWidget, y, x);
            m_cellWidget->show();
            m_FrameLayout->update();
        }
    }

    updateGUI();
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
        updateGUI();
    }
    else
    {
        playing = true;
        if (file.currFrame == (file.m_frames.end()-1))
        {
            file.currFrame = file.m_frames.begin();
            updateGUI();
        }
        else
        {
            ui->pushButton_back10->setEnabled(false);
            ui->pushButton_back1->setEnabled(false);
            ui->pushButton_forward1->setEnabled(false);
            ui->pushButton_forward10->setEnabled(false);
            ui->pushButton_play->setText("Pause");
        }
        t->setMilliseconds((*file.currFrame)->frame_length);
        t->start();
    }
}

void Preview::on_pushButton_back1_clicked()
{
    if (file.currFrame == file.m_frames.begin()) return;
    file.currFrame--;
    updateGUI();
}

void Preview::on_pushButton_back10_clicked()
{
    if (file.currFrame == file.m_frames.begin()) return;
    if ((file.currFrame-file.m_frames.begin()) < 10)
        file.currFrame = file.m_frames.begin();
    else file.currFrame -= 10;
    updateGUI();
}

void Preview::on_pushButton_forward1_clicked()
{
    if (file.currFrame == (file.m_frames.end()-1)) return;
    file.currFrame++;
    updateGUI();
}

void Preview::on_pushButton_forward10_clicked()
{
    if (file.currFrame == (file.m_frames.end()-1)) return;
    if ((file.currFrame-file.m_frames.begin()) > (file.m_frames.size()-11))
        file.currFrame = (file.m_frames.end()-1);
    else file.currFrame += 10;
    updateGUI();
}

void Preview::updateGUI()
{
    for (int y = 0; y < (TAN_DEFAULT_ROWS/2); y++)
        for (int x = 0; x < (TAN_DEFAULT_COLS/3); x++)
            ui->gridLayout->itemAtPosition(y,x)->widget()->setStyleSheet(QString("margin: 0px; border: 2px solid rgb(127,127,127); border-radius: 4px; background-color: " + (*file.currFrame)->pixels[x+4][y+5].color.name()));
    if (playing)
    {
        ui->pushButton_back10->setEnabled(false);
        ui->pushButton_back1->setEnabled(false);
        ui->pushButton_forward1->setEnabled(false);
        ui->pushButton_forward10->setEnabled(false);
        ui->pushButton_play->setText("Pause");
    }
    else
    {
        if (file.currFrame == file.m_frames.begin())
        {
            ui->pushButton_back10->setEnabled(false);
            ui->pushButton_back1->setEnabled(false);
            ui->pushButton_forward1->setEnabled(true);
            ui->pushButton_forward10->setEnabled(true);
        }
        else if (file.currFrame == (file.m_frames.end()-1))
        {
            ui->pushButton_back10->setEnabled(true);
            ui->pushButton_back1->setEnabled(true);
            ui->pushButton_forward1->setEnabled(false);
            ui->pushButton_forward10->setEnabled(false);
        }
        else
        {
            ui->pushButton_back10->setEnabled(true);
            ui->pushButton_back1->setEnabled(true);
            ui->pushButton_forward1->setEnabled(true);
            ui->pushButton_forward10->setEnabled(true);
        }
        ui->pushButton_play->setText("Play");
    }
    this->setWindowTitle("Frame " + QString::number(file.currFrame+1-file.m_frames.begin()));
    ui->label_start->setText(QString::number((*file.currFrame)->frame_start) + " ms");
    ui->label_duration->setText(QString::number((*file.currFrame)->frame_length) + " ms");
}

void Preview::next_frame()
{
    if (!playing) return;
    if (file.currFrame == (file.m_frames.end()-1))
    {
        playing = false;
        updateGUI();
    }
    else
    {
        file.currFrame++;
        updateGUI();
        t->setMilliseconds((*file.currFrame)->frame_length);
        t->start();
    }
}
