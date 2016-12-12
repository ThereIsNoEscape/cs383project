#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QColorDialog>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/resources/icon.png"));

    createActions();
    createMenus();

    m_generateFrame(TAN_DEFAULT_ROWS, TAN_DEFAULT_COLS);
    project.setLeftColor(255,255,255);
    project.setRightColor(255,255,255);
    updateGUIColorButtons();
    QString qss = ("background-color: #e0e0e0");
    ui->pushButton_prev->setStyleSheet(qss);
    ui->pushButton_prev->setEnabled(false);
    ui->pushButton_next->setStyleSheet(qss);
    ui->pushButton_next->setEnabled(false);
    ui->pushButton_undo->setEnabled(false);
    ui->pushButton_redo->setEnabled(false);
    undoAct->setEnabled(false);
    redoAct->setEnabled(false);
    nothingToSave = true;
}

MainWindow::~MainWindow()
{
    m_destroyFrame(TAN_DEFAULT_ROWS, TAN_DEFAULT_COLS);

    delete ui;
}

bool MainWindow::saveSequence()
{
    if (nothingToSave) return true;
    QMessageBox::StandardButton reply;

    /* Create Message Box
     * Title of message box : "Tower Lights"
     * Prompt message : "Would you like to save?"
     * 3 button choices : "Save", "No", "Cancel"
    */

    reply = QMessageBox::question(this, "Tower Lights", "Would you like to save?",
                                                                QMessageBox::Save|QMessageBox::No|QMessageBox::Cancel);

    if (reply==0x00400000)  //if cancel selected
            return false;
    if (reply==0x00000800)  //if save selected
    {
            if (project.Save())
            {
                this->setWindowTitle(project.getFileName());
                nothingToSave = true;
            }
    }
    return true;
}

void MainWindow::openFile()    //when open is clicked
{
    //get the filename
    if (!saveSequence()) return;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open tan file"),"",    //user selects fileName
                                             "Tan File (*.tan*);;All files (*.*)");
    if (fileName=="")   //checking if blank name is selected
        return;

    TanFile* prospective = load(fileName);//loads all the project into memory

    if (prospective == NULL) //returns if nothing was returned (the file was invalid)
        return;

    //filename was good, file was loaded, proceed with updating GUI

    clearThumbnails();

    project = TanFile(prospective);

    this->setWindowTitle(project.getFileName());

    delete prospective;

    //set time interval for each frame
    QList<TanFrame*>::iterator iter;
    for(iter = project.m_frames.begin(); iter != project.m_frames.end(); iter++)
    {
        if((iter+1) == project.m_frames.end()) //if you're on the last frame
        {
            (*iter)->frame_length = 25;        //default time interval for last frame
            //qDebug() << iter->frame_length;
        }
        else
        {
            //current frame time interval = next frame start time = current frame start time
            (*iter)->frame_length = (*(iter + 1))->frame_start - (*iter)->frame_start;
        }
    }

    updateGUIColorButtons();
    if (project.getAudioFile().compare(QString("NoAudioFile")))
        ui->label_audiofile->setText(project.getAudioFile());
    else ui->label_audiofile->setText("unset");

    addThumbnail();

    if (project.m_frames.size() > 1)
    {
        ui->pushButton_delete->setEnabled(true);
        for (QList<TanFrame*>::iterator i = (project.m_frames.begin()+1); i != project.m_frames.end(); i++)
        {
            generateThumbnail((*i));
            addThumbnailToEnd((*i)->thumbnail, (*i));
        }
    }
    else ui->pushButton_delete->setEnabled(false);

    on_change_frame();
    nothingToSave = true;
}

void MainWindow::newFile()
{
    if (!saveSequence()) return;
    clearThumbnails();
    project = TanFile();
    addThumbnail();
    ui->pushButton_delete->setEnabled(false);

    ui->label_audiofile->setText("Audio File: unset");
    project.setLeftColor(255,255,255);
    project.setRightColor(255,255,255);
    updateGUIColorButtons();
    on_change_frame();
    nothingToSave = true;
}

void MainWindow::save()
{
    if (project.Save())
    {
        nothingToSave = true;
        this->setWindowTitle(project.getFileName());
    }
}

void MainWindow::saveAs()
{
    //qDebug("saving as");
    if (project.SaveAs())
    {
        nothingToSave = true;
        this->setWindowTitle(project.getFileName());
    }
}

// Create the grid of cell widgets
void MainWindow::m_generateFrame(int rows, int cols)
{
    int i = 0, j = 0;
    QGridLayout *m_FrameLayout = ui->gridLayout;
    QString m_cellName;
    QSizePolicy m_cellSizePolicy;
    QSize m_cellSize(18,18);	// Arbitrarily selected as a decent minimum ("quarter-inch" @ 72 ppi, less @ 96 ppi or higher resolutions)

    // Configure the size policy that every cell widget will use
    m_cellSizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
    m_cellSizePolicy.setHorizontalStretch(1);
    m_cellSizePolicy.setVerticalPolicy(QSizePolicy::Fixed);
    m_cellSizePolicy.setVerticalStretch(1);
    m_cellSizePolicy.setHeightForWidth(true);

    for (i=0; i<rows; i++)
    {
        for (j=0; j<cols; j++)
        {
            // Generate the name for each cell, based on rows and cols
            m_cellName = "cell" + (QString("%1").arg((i*cols + j), 3, 10, QChar('0')));
            CellWidget *m_cellWidget = new CellWidget(m_cellName, i, j);
            m_cellWidget->setMinimumSize(m_cellSize);
            m_cellWidget->setSizePolicy(m_cellSizePolicy);

            // Adding cell widget to the frame's gridLayout
            m_FrameLayout->addWidget(m_cellWidget, i, j);
            m_cellWidget->show();
            // Connecting each cell's signals to appropriate generic slots
            m_connectCellSignals(m_cellWidget);
            m_FrameLayout->update();
        }
    }
    addThumbnail();
}

// Destroy the grid of cell widgets
void MainWindow::m_destroyFrame(int rows, int cols)
{
	CellWidget* m_cellWidget;
	int i = 0, j = 0;

	for (i=0; i<rows; i++)
	{
		for (j=0; j<cols; j++)
		{
			// Iterate through the grid of cells and delete the widget at each (row,col)
			m_cellWidget = (CellWidget*)ui->gridLayout->itemAtPosition(i,j)->widget();
			delete m_cellWidget;
			m_cellWidget = 0;
		}
	}
}


// Connecting all the cells to the same click handler
void MainWindow::m_connectCellSignals(CellWidget *m_cell)
{
    connect(m_cell, SIGNAL(clicked(const int, const int, const char)), this, SLOT(cell_clicked(const int, const int, const char)));
    connect(m_cell, SIGNAL(doubleClicked(const char, const QColor)), this, SLOT(cell_doubleClicked(const char, const QColor)));
}


// Slot to respond to cell clicks
// Determines the color to use, based on which type of click (left or right)
// Updates the displayed color in the clicked cell and
// updates appropriate frame of Tan file representation with color information
void MainWindow::cell_clicked(const int row, const int col, const char btn)
{
    //QString m_cellName = m_getObjName(QObject::sender());
    //CellWidget *m_cell = MainWindow::findChild<CellWidget*>(m_cellName);
    QColor m_color = Qt::black;

    // Determine whether it was a left or right click
    if (btn == 'L')
    {
        m_color = project.getLeftColor();
    }
    else if (btn == 'R')
    {
        m_color = project.getRightColor();
    }
    //if both colors are the same, don't bother
    if (m_color == (*project.currFrame)->pixels[col][row]) return;
    // Then update the cell color
    on_change_color(row, col, m_color);
    // And update the corresponding color in the Tan file representation
    project.storeFrameColor(row,col,m_color);
    nothingToSave = false;
}


void MainWindow::cell_doubleClicked(const char btn, const QColor clr)
{
    // Determine whether it was a left or right double click
    if (btn == 'L')
    {
        project.setLeftColor(clr);
    }
    else if (btn == 'R')
    {
        project.setRightColor(clr);
    }

    updateGUIColorButtons();

    nothingToSave = false;
}


// Get the name of the referenced object.
QString MainWindow::m_getObjName(QObject *m_obj) {
    QString m_name = m_obj->property("objectName").toString();
    return m_name;
}

void MainWindow::createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    saveAsAct = new QAction(tr("&Save As"), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document to disk as a new file"));
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);

    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the application"));
    connect(quitAct, &QAction::triggered, this, &QWidget::close);

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    connect(undoAct, &QAction::triggered, this, &MainWindow::on_undo);

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    connect(redoAct, &QAction::triggered, this, &MainWindow::on_redo);

    letterAct = new QAction(tr("&Letter"), this);
    connect(letterAct, &QAction::triggered, this, &MainWindow::insert_letter);

    symbolAct = new QAction(tr("S&ymbol"), this);
    connect(symbolAct, &QAction::triggered, this, &MainWindow::insert_symbol);

    shapeAct = new QAction(tr("S&hape"), this);
    connect(shapeAct, &QAction::triggered, this, &MainWindow::insert_shape);

    infoAct = new QAction(tr("Info"), this);
    connect(infoAct, &QAction::triggered, this, &MainWindow::info);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);

    insertMenu = menuBar()->addMenu(tr("&Insert"));
    insertMenu->addAction(letterAct);
    insertMenu->addAction(symbolAct);
    insertMenu->addAction(shapeAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(infoAct);
}

void MainWindow::updateGUIColorButtons()
{
    ui->label_2->setText(project.getLeftColor().name());
    QString qss;
    if (project.getLeftColor().red() < 191 && project.getLeftColor().green() < 191 && project.getLeftColor().blue() < 191)
        qss = ("color: #ffffff; background-color: " + project.getLeftColor().name());
    else qss = ("color: #000000; background-color: " + project.getLeftColor().name());
    ui->pushButton_l->setStyleSheet(qss);
    ui->pushButton_l->setText("L");

    ui->label_3->setText(project.getRightColor().name());
    if (project.getRightColor().red() < 191 && project.getRightColor().green() < 191 && project.getRightColor().blue() < 191)
        qss = ("color: #ffffff; background-color: " + project.getRightColor().name());
    else qss = ("color: #000000; background-color: " + project.getRightColor().name());
    ui->pushButton_r->setStyleSheet(qss);
    ui->pushButton_r->setText("R");
}

void MainWindow::on_pushButton_l_clicked()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if(color.isValid())
    {
        project.setLeftColor(color);
        updateGUIColorButtons();
    }
    nothingToSave = false;
}

void MainWindow::generateThumbnailCurrent()
{
    QString tempString;
    QColor tempColor;
    for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
    {
        for (int x = 0; x < TAN_DEFAULT_COLS; x++)
        {
            tempString = ui->gridLayout->itemAtPosition(y,x)->widget()->styleSheet();
            tempColor = QColor(tempString.mid(tempString.length()-7));
            for (int a = 0; a < 8; a++)
            {
                for (int b = 0; b < 8; b++)
                {
                    if (a == 0 || a == 7 || b == 0 || b == 7)
                    {
                        if (x < 8 && x > 3 && y < 15 && y > 4)
                            (*project.currFrame)->thumbnail.setPixelColor(((x*9+6)+1+b), ((y*9+10)+1+a), QColor(127,127,127));
                        else (*project.currFrame)->thumbnail.setPixelColor(((x*9+6)+1+b), ((y*9+10)+1+a), QColor(90,90,90));
                    }
                    else (*project.currFrame)->thumbnail.setPixelColor(((x*9+6)+1+b), ((y*9+10)+1+a), tempColor);
                }
            }
            if (x < 8 && x > 3 && y < 15 && y > 4)
            {
                (*project.currFrame)->thumbnail.setPixelColor(((x*9+6)+2), ((y*9+10)+2), QColor(127,127,127));
                (*project.currFrame)->thumbnail.setPixelColor(((x*9+6)+7), ((y*9+10)+2), QColor(127,127,127));
                (*project.currFrame)->thumbnail.setPixelColor(((x*9+6)+2), ((y*9+10)+7), QColor(127,127,127));
                (*project.currFrame)->thumbnail.setPixelColor(((x*9+6)+7), ((y*9+10)+7), QColor(127,127,127));
            }
            else
            {
                (*project.currFrame)->thumbnail.setPixelColor(((x*9+6)+2), ((y*9+10)+2), QColor(90,90,90));
                (*project.currFrame)->thumbnail.setPixelColor(((x*9+6)+7), ((y*9+10)+2), QColor(90,90,90));
                (*project.currFrame)->thumbnail.setPixelColor(((x*9+6)+2), ((y*9+10)+7), QColor(90,90,90));
                (*project.currFrame)->thumbnail.setPixelColor(((x*9+6)+7), ((y*9+10)+7), QColor(90,90,90));
            }
        }
    }
}

void MainWindow::generateThumbnail(TanFrame* ptr)
{
    QColor tempColor;
    for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
    {
        for (int x = 0; x < TAN_DEFAULT_COLS; x++)
        {
            tempColor = ptr->pixels[x][y];
            for (int a = 0; a < 8; a++)
            {
                for (int b = 0; b < 8; b++)
                {
                    if (a == 0 || a == 7 || b == 0 || b == 7)
                    {
                        if (x < 8 && x > 3 && y < 15 && y > 4)
                            ptr->thumbnail.setPixelColor(((x*9+6)+1+b), ((y*9+10)+1+a), QColor(127,127,127));
                        else ptr->thumbnail.setPixelColor(((x*9+6)+1+b), ((y*9+10)+1+a), QColor(90,90,90));
                    }
                    else ptr->thumbnail.setPixelColor(((x*9+6)+1+b), ((y*9+10)+1+a), tempColor);
                }
            }
            if (x < 8 && x > 3 && y < 15 && y > 4)
            {
                ptr->thumbnail.setPixelColor(((x*9+6)+2), ((y*9+10)+2), QColor(127,127,127));//ui->gridLayout->itemAtPosition(x,y)->widget()->palette().color(QWidget::backgroundRole()));
                ptr->thumbnail.setPixelColor(((x*9+6)+7), ((y*9+10)+2), QColor(127,127,127));//ui->gridLayout->itemAtPosition(x,y)->widget()->palette().color(QWidget::backgroundRole()));
                ptr->thumbnail.setPixelColor(((x*9+6)+2), ((y*9+10)+7), QColor(127,127,127));//ui->gridLayout->itemAtPosition(x,y)->widget()->palette().color(QWidget::backgroundRole()));
                ptr->thumbnail.setPixelColor(((x*9+6)+7), ((y*9+10)+7), QColor(127,127,127));//ui->gridLayout->itemAtPosition(x,y)->widget()->palette().color(QWidget::backgroundRole()));
            }
            else
            {
                ptr->thumbnail.setPixelColor(((x*9+6)+2), ((y*9+10)+2), QColor(90,90,90));//ui->gridLayout->itemAtPosition(x,y)->widget()->palette().color(QWidget::backgroundRole()));
                ptr->thumbnail.setPixelColor(((x*9+6)+7), ((y*9+10)+2), QColor(90,90,90));//ui->gridLayout->itemAtPosition(x,y)->widget()->palette().color(QWidget::backgroundRole()));
                ptr->thumbnail.setPixelColor(((x*9+6)+2), ((y*9+10)+78), QColor(90,90,90));//ui->gridLayout->itemAtPosition(x,y)->widget()->palette().color(QWidget::backgroundRole()));
                ptr->thumbnail.setPixelColor(((x*9+6)+7), ((y*9+10)+78), QColor(90,90,90));//ui->gridLayout->itemAtPosition(x,y)->widget()->palette().color(QWidget::backgroundRole()));
            }
        }
    }
}

void MainWindow::on_pushButton_prev_clicked()
{
    switchSelectedThumbnail((project.currFrame-project.m_frames.begin())-1);

    int temp = (project.currFrame-project.m_frames.begin());
    project.currFrame = (project.m_frames.begin()+temp-1);

    on_change_frame();
}

void MainWindow::on_pushButton_next_clicked()
{
    switchSelectedThumbnail((project.currFrame-project.m_frames.begin())+1);

    int temp = (project.currFrame-project.m_frames.begin());
    project.currFrame = (project.m_frames.begin()+temp+1);

    on_change_frame();
}

void MainWindow::switchCurrentFrame(int index)
{
    if (index < 0 || index >= project.m_frames.size()) return;

    switchSelectedThumbnail(index);

    project.currFrame = (project.m_frames.begin()+index);

    on_change_frame();
}

void MainWindow::on_pushButton_r_clicked()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if(color.isValid())
    {
        project.setRightColor(color);
        updateGUIColorButtons();
    }
    nothingToSave = false;
}


void MainWindow::on_pushButton_new_clicked()
{
    newFrame();
}

void MainWindow::on_pushButton_copyNew_clicked()
{
    newFrameCopy();
}

void MainWindow::on_pushButton_undo_clicked()
{
    on_undo();
}

void MainWindow::on_pushButton_redo_clicked()
{
    on_redo();
}

QImage MainWindow::scaleDown(QImage thumbnail)
{
    QImage ret = QImage(60, 100, QImage::Format_RGB32);
    ret.fill(QColor(90,90,90));
    QColor tempColor;
    for (int y = 0; y < TAN_DEFAULT_ROWS; y++)
    {
        for (int x = 0; x < TAN_DEFAULT_COLS; x++)
        {
            tempColor = thumbnail.pixelColor(((x*9)+9),((y*9)+13));
            if (x < 8 && x > 3 && y < 15 && y > 4)
            {
                for (int a = 0; a < 5; a++)
                {
                    for (int b = 0; b < 5; b++)
                    {
                        ret.setPixelColor(((x*5)+b), ((y*5)+a), QColor(127,127,127));
                    }
                }
            }
            for (int a = 0; a < 3; a++)
            {
                for (int b = 0; b < 3; b++)
                {
                    ret.setPixelColor(((x*5)+b+1), ((y*5)+a+1), tempColor);
                }
            }
        }
    }
    return ret;
}

void MainWindow::newFrame()
{
    if (project.m_frames.size() == 1) ui->pushButton_delete->setEnabled(true);
    generateThumbnailCurrent();
    project.newFrame();
    addCurrentThumbnail();

    nothingToSave = false;
    on_change_frame();
}

void MainWindow::newFrameCopy()
{
    if (project.m_frames.size() == 1) ui->pushButton_delete->setEnabled(true);
    generateThumbnailCurrent();
    project.newFrameCopy();
    addCurrentThumbnail();

    nothingToSave = false;
    on_change_frame();
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{// I recoded this because it wasn't working properly
    int totalTime = (*project.currFrame)->frame_start + arg1;
    (*project.currFrame)->frame_length = arg1;
    for (QList<TanFrame*>::iterator i = (project.currFrame+1); i != project.m_frames.end(); i++)
    {
        (*i)->frame_start = totalTime;
        totalTime += (*i)->frame_length;
    }
    //int totalTime = 0;                      //frame_legnth's < currFrame added together
//    QList<TanFrame*>::iterator i; //iterator for linked list
//    for(i = project.m_frames.begin(); i != project.m_frames.end(); i++){ //from begining of linked list to end of linked list
//        if(i == project.currFrame){                               //if iterator is on your current frame
//            (*i)->frame_length = arg1;                             //set frame length to the value in the spin box
//            (*i)->frame_start = totalTime;                         //set your current frame start time to all previous frame lengths added together
//            //qDebug() << (*i)->frame_length << (*i)->frame_start;
//        }else if(i < project.currFrame) {                          //if iterator is on a frame < your current frame
//            totalTime = totalTime + (*i)->frame_length;            //add frame legnth to total time
//        }
//    }
    nothingToSave = false;
}

void MainWindow::clearThumbnails() // used when opening a project or starting a new project
{
    Thumbnail* temp;
    for (int c = 0; c < project.m_frames.size(); c++)
    {
        temp = ((Thumbnail*)(ui->horizontalLayout_2->itemAt(0)->widget()));
        ui->horizontalLayout_2->removeWidget(temp);
        delete temp;
        ui->horizontalLayout_2->update();
    }
}

void MainWindow::addThumbnail() // only used when starting a new project;
{
    Thumbnail *button = newThumbnail(QString(":/resources/currSelect.png"), (*project.currFrame));
    ui->horizontalLayout_2->addWidget(button);
    button->show();
    ui->horizontalLayout_2->update();
}

void MainWindow::addThumbnailToEnd(QImage in, TanFrame* ptr)
{
    Thumbnail *button = newThumbnail(in, ptr);
    ui->horizontalLayout_2->addWidget(button);
    button->show();
    ui->horizontalLayout_2->update();
}

void MainWindow::switchSelectedThumbnail(int index) // used when the user switches frames
{
    generateThumbnailCurrent();
    ((Thumbnail*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin()))->widget()))->setIcon(QIcon(QPixmap::fromImage(scaleDown((*project.currFrame)->thumbnail), Qt::AutoColor)));
    ((Thumbnail*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin()))->widget()))->setIconSize(QSize(120,200));

    ((Thumbnail*)(ui->horizontalLayout_2->itemAt(index)->widget()))->setIcon(QIcon(QPixmap::fromImage(QImage(":/resources/currSelect.png"), Qt::AutoColor)));
    ((Thumbnail*)(ui->horizontalLayout_2->itemAt(index)->widget()))->setIconSize(QSize(120,200));
}

void MainWindow::addCurrentThumbnail() // used when creating a new frame (also switches selected frame)
{
    ((Thumbnail*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin()-1))->widget()))->setIcon(QIcon(QPixmap::fromImage(scaleDown((*(project.currFrame-1))->thumbnail), Qt::AutoColor)));
    ((Thumbnail*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin()-1))->widget()))->setIconSize(QSize(120,200));

    Thumbnail *button = newThumbnail(QString(":/resources/currSelect.png"), (*project.currFrame));
    ui->horizontalLayout_2->insertWidget((project.currFrame-project.m_frames.begin()), button);
    button->show();
    ui->horizontalLayout_2->update();
}

Thumbnail* MainWindow::newThumbnail(QImage in, TanFrame* ptr)
{
    QString qss;
    QSizePolicy sizePolicy;
    QSize size(70,100);

    sizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(1);
    sizePolicy.setVerticalPolicy(QSizePolicy::Fixed);
    sizePolicy.setVerticalStretch(1);
    sizePolicy.setHeightForWidth(true);

    Thumbnail *button = new Thumbnail(ptr);
    button->setSizePolicy(sizePolicy);
    button->setMinimumSize(size);
    button->setMaximumSize(size);
    // Adding cell widget to the frame's gridLayout
    qss = QString("margin: 5px;");
    button->setStyleSheet(qss);
    button->setIcon(QIcon(QPixmap::fromImage(scaleDown(in), Qt::AutoColor)));
    button->setIconSize(QSize(120,200));
    connect(button, SIGNAL (clicked(const long int)),this, SLOT (thumbnail_clicked(const long int)));
    return button;
}

Thumbnail* MainWindow::newThumbnail(QString in, TanFrame* ptr)
{
    QString qss;
    QSizePolicy sizePolicy;
    QSize size(70,100);

    sizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(1);
    sizePolicy.setVerticalPolicy(QSizePolicy::Fixed);
    sizePolicy.setVerticalStretch(1);
    sizePolicy.setHeightForWidth(true);

    Thumbnail *button = new Thumbnail(ptr);
    button->setSizePolicy(sizePolicy);
    button->setMinimumSize(size);
    button->setMaximumSize(size);
    // Adding cell widget to the frame's gridLayout
    qss = QString("margin: 5px;");
    button->setStyleSheet(qss);
    button->setIcon(QIcon(in));
    button->setIconSize(QSize(120,200));
    connect(button, SIGNAL (clicked(const long int)),this, SLOT (thumbnail_clicked(const long int)));
    return button;
}

void MainWindow::on_pushButton_preview_clicked()
{
    Preview* p = new Preview(project);
    p->setModal(false);
    p->show();
    p->raise();
    p->activateWindow();
}

void MainWindow::on_pushButton_delete_clicked()
{
    if (project.m_frames.size() == 1) return;
    Thumbnail* temp;
    int totalTime;
    if (project.currFrame == project.m_frames.begin())
    { // deleting the first frame (move right)
        ((Thumbnail*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin())+1)->widget()))->setIcon(QIcon(QPixmap::fromImage(QImage(":/resources/currSelect.png"), Qt::AutoColor)));
        ((Thumbnail*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin())+1)->widget()))->setIconSize(QSize(120,200));

        temp = ((Thumbnail*)(ui->horizontalLayout_2->itemAt(0)->widget()));
        ui->horizontalLayout_2->removeWidget(temp);
        delete temp;
        ui->horizontalLayout_2->update();
        project.removeCurrentFrame();
        project.currFrame = project.m_frames.begin();

        totalTime = 0;
        for (QList<TanFrame*>::iterator i = project.currFrame; i != project.m_frames.end(); i++)
        {
            (*i)->frame_start = totalTime;
            totalTime += (*i)->frame_length;
        }
    }
    else
    { // not deleting the first frame (move left)
        temp = ((Thumbnail*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin()))->widget()));
        ui->horizontalLayout_2->removeWidget(temp);
        delete temp;
        ui->horizontalLayout_2->update();
        project.removeCurrentFrame();
        ((Thumbnail*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin()))->widget()))->setIcon(QIcon(QPixmap::fromImage(QImage(":/resources/currSelect.png"), Qt::AutoColor)));
        ((Thumbnail*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin()))->widget()))->setIconSize(QSize(120,200));

        if (project.currFrame == project.m_frames.begin())
        {
            totalTime = 0;
            for (QList<TanFrame*>::iterator i = project.currFrame; i != project.m_frames.end(); i++)
            {
                (*i)->frame_start = totalTime;
                totalTime += (*i)->frame_length;
            }
        }
        else
        {
            totalTime = (*(project.currFrame-1))->frame_start + (*(project.currFrame-1))->frame_length;
            for (QList<TanFrame*>::iterator i = project.currFrame; i != project.m_frames.end(); i++)
            {
                (*i)->frame_start = totalTime;
                totalTime += (*i)->frame_length;
            }
        }
    }

    nothingToSave = false;

    if (project.m_frames.size() == 1) ui->pushButton_delete->setEnabled(false);
    on_change_frame();
}

void MainWindow::thumbnail_clicked(const long int in)
{
    //qDebug() << "tanframe!!! length: " << ((TanFrame*)in)->frame_length;
    for (QList<TanFrame*>::iterator i = project.m_frames.begin(); i != project.m_frames.end(); i++)
    {
        if (((long int)(*(i))) == in)
        {
            switchCurrentFrame((i-project.m_frames.begin()));
            break;
        }
    }
}

void MainWindow::on_pushButton_changeAudioFile_clicked()
{
    //get the filename
    QString audiofilename = QFileDialog::getOpenFileName(this, tr("Select audio file"),"",    //user selects fileName
                                             "Wav File (*.wav*);;All files (*.*)");
    if (audiofilename=="")   //checking if blank name is selected
        return;

    project.setAudioFile(audiofilename);
    int fslash = audiofilename.lastIndexOf('\\');
    int bslash = audiofilename.lastIndexOf('/');
    ui->label_audiofile->setText("Audio File: " + (fslash > bslash ? audiofilename.mid(fslash+1) : audiofilename.mid(bslash+1)));
}

void MainWindow::on_undo()
{
    if ((*project.currFrame)->undoStack.size() > 0)
    {
        Change* change = (*project.currFrame)->undoStack.pop();
        (*project.currFrame)->redoStack.push(change);
        ((CellWidget*)ui->gridLayout->itemAtPosition(change->row,change->col)->widget())->setColor(change->old_color);
        (*project.currFrame)->pixels[change->col][change->row] = change->old_color;
        ui->pushButton_redo->setEnabled(true);
        redoAct->setEnabled(true);
    }
    if ((*project.currFrame)->undoStack.size() == 0)
    {
        ui->pushButton_undo->setEnabled(false);
        undoAct->setEnabled(false);
    }
}

void MainWindow::on_redo()
{
    if ((*project.currFrame)->redoStack.size() > 0)
    {
        Change* change = (*project.currFrame)->redoStack.pop();
        (*project.currFrame)->undoStack.push(change);
        ((CellWidget*)(ui->gridLayout->itemAtPosition(change->row,change->col)->widget()))->setColor(change->new_color);
        (*project.currFrame)->pixels[change->col][change->row] = change->new_color;
        ui->pushButton_undo->setEnabled(true);
        undoAct->setEnabled(true);
    }
    if ((*project.currFrame)->redoStack.size() == 0) {
        ui->pushButton_redo->setEnabled(false);
        redoAct->setEnabled(false);
    }
}

void MainWindow::on_change_color(int row, int col, const QColor& p_color)
{
    (*project.currFrame)->redoStack.clear();

    Change* change = new Change;
    CellWidget *cell = (CellWidget*)ui->gridLayout->itemAtPosition(row,col)->widget();// MainWindow::findChild<CellWidget*>(m_cellName);

    change->row = row;
    change->col = col;
    change->old_color = cell->getColor();
    change->new_color = p_color;
    (*project.currFrame)->undoStack.push(change);
    cell->setColor(p_color);
    undoAct->setEnabled(true);
    redoAct->setEnabled(false);
    ui->pushButton_undo->setEnabled(true);
    ui->pushButton_redo->setEnabled(false);
}

void MainWindow::on_change_frame()
{
    for (int y = 0; y < 20; y++)
        for (int x = 0; x < 12; x++)
            ((CellWidget*)(ui->gridLayout->itemAtPosition(y,x)->widget()))->setColor((*project.currFrame)->pixels[x][y]);

    ui->spinBox->setValue((*project.currFrame)->frame_length);

    if ((project.currFrame-project.m_frames.begin()) == 0)
    {
        ui->pushButton_prev->setIcon(QIcon());
        ui->pushButton_prev->setStyleSheet(QString("background-color: #e0e0e0"));
        ui->pushButton_prev->setEnabled(false);
    }
    else
    {
        generateThumbnail((*(project.currFrame-1)));
        ui->pushButton_prev->setEnabled(true);
        ui->pushButton_prev->setIcon(QIcon(QPixmap::fromImage((*(project.currFrame-1))->thumbnail, Qt::AutoColor)));
        ui->pushButton_prev->setIconSize(QSize(240,400));
    }

    if ((project.currFrame-project.m_frames.begin()) == (project.m_frames.size()-1))
    {
        ui->pushButton_next->setIcon(QIcon());
        ui->pushButton_next->setStyleSheet(QString("background-color: #e0e0e0"));
        ui->pushButton_next->setEnabled(false);
    }
    else
    {
        generateThumbnail((*(project.currFrame+1)));
        ui->pushButton_next->setEnabled(true);
        ui->pushButton_next->setIcon(QIcon(QPixmap::fromImage((*(project.currFrame+1))->thumbnail, Qt::AutoColor)));
        ui->pushButton_next->setIconSize(QSize(240,400));
    }
    if ((*project.currFrame)->undoStack.size() > 0) {
        undoAct->setEnabled(true);
        ui->pushButton_undo->setEnabled(true);
    } else {
        undoAct->setEnabled(false);
        ui->pushButton_undo->setEnabled(false);
    }
    if ((*project.currFrame)->redoStack.size() > 0) {
        redoAct->setEnabled(true);
        ui->pushButton_redo->setEnabled(true);
    } else {
        redoAct->setEnabled(false);
        ui->pushButton_redo->setEnabled(false);
    }
}


void MainWindow::on_pushButton_clearFrame_clicked()
{
    for(int i=0; i<TAN_DEFAULT_ROWS; i++)
    {
        for(int j=0; j<TAN_DEFAULT_COLS; j++)
        {
            (*project.currFrame)->pixels[j][i] = QColor(0,0,0,0);
        }
    }
    on_change_frame();
}

void MainWindow::spawnEffect(const effect* e)
{
    //apply effect
    for (int r=0;r<TAN_DEFAULT_ROWS;r++)
    {
        for (int c=0;c<TAN_DEFAULT_COLS;c++)
        {
            if (e->pixels[c][r].alpha() == 255) // check to make sure there's something there
            {
                //update project
                (*project.currFrame)->pixels[c][r]  = e->pixels[c][r];
                //update GUI
                //QString m_cellName = "cell" + (QString("%1").arg((r*TAN_DEFAULT_COLS + c), 3, 10, QChar('0')));
                //CellWidget *m_cellWidget = MainWindow::findChild<CellWidget*>(m_cellName);
                //m_cellWidget->setColor(e->pixels[c][r]);
                on_change_color(r, c, e->pixels[c][r]);
            }
        }
    }
}

void MainWindow::insert_letter() {
    letterEffectDialog d((*project.currFrame)->pixels);
    connect(&d, SIGNAL(accepted(const effect*)), this, SLOT(spawnEffect(const effect*)));
    d.exec();
}

void MainWindow::insert_symbol() {
    symbolEffectDialog d((*project.currFrame)->pixels);
    connect(&d, SIGNAL(accepted(const effect*)), this, SLOT(spawnEffect(const effect*)));
    d.exec();
}

void MainWindow::insert_shape()  {
    shapeEffectDialog d((*project.currFrame)->pixels);
    connect(&d, SIGNAL(accepted(const effect*)), this, SLOT(spawnEffect(const effect*)));
    d.exec();
}

void MainWindow::info()  {
    infoDialog* d = new infoDialog;
    d->setModal(false);
    d->show();
    d->raise();
    d->activateWindow();
}
