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
            if (project.Save()) nothingToSave = true;;
    }
    return true;
}

void MainWindow::openFile()    //when open is clicked
{
    if (!saveSequence()) return;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open tan file"),"C:/",    //user selects fileName
											 "Tan File (*.tan*);;All files (*.*)");
    if (fileName=="")
        return;

    TanFile* prospective = new TanFile(fileName);//this will temporarily hold the information so that if there's something wrong with this file we haven't written in bad data to the project object
    //this object is deleted when this function returns, so no memory is leaked
    QStringList contents = getFileContents(fileName);   //loads the contents of the file line by line into
                                                                                                            //QStringList contents

    //check version
    if (contents[0]!="0.4")    //error checking
    {
        QMessageBox::information(0,"error","File is an unsupported version");
        return;
    }
    //set audio filename
    prospective->setAudioFile(contents[1]);   //set audio filename

    //get the current color value
    QStringList temp;   //holds parsed values
    int r,g,b;  //holds int values for rgb

    temp = contents[2].split(QRegExp(" "),QString::SkipEmptyParts); //delimit by spaces
    r = temp[0].toInt();    // convert to integers
    g = temp[1].toInt();    //
    b = temp[2].toInt();    //
    //WARNING: This code will accept characters with ascii values within the range
    //         This should not really be a big deal however
    if ((r<0)||(r>255)||(g<0)||(g>255)||(b<0)||(b>255)) //error checking on rgb values
    {
        QMessageBox::information(0,"error","current rgb color is not within range (0-255)");
        return;
    }
    prospective->setLeftColor(r,g,b);     //set the rgb value

    //get the preset RGB values
    QStringList buffer; //holds parsed input string
    int presetRGB[TAN_DEFAULT_COLORPRESETS*3];  //holds each individual rgb value

    buffer = contents[3].split(QRegExp(" "),QString::SkipEmptyParts); //delimit by spaces

    for (int i=0;i<TAN_DEFAULT_COLORPRESETS*3;i++)
        presetRGB[i]=buffer[i].toInt(); //places ints into presetRGB

    prospective->setPresetColor(presetRGB);

    //get the number of frames
    QStringList hype = contents[4].split(QRegExp(" "),QString::SkipEmptyParts); //delimit by spaces
    int num_frames = hype[0].toInt();  //set num_frames
    if (num_frames<1)   //error checking the number of frames
    {
        QMessageBox::information(0,"error","number of frames must be at least 1");
        return;
    }
    //error check dimensions
    if (hype[1]!="10" || hype[2]!="4")
    {
        QMessageBox::information(0,"error","invalid dimensions");
        return;
    }

    /*************************************************************************************/

    //error checking the tanfile frames
    if (((contents.size()-5) % 21)!=0)
    {
        QMessageBox::information(0,"error","frames corrupt");
        return;
    }
    else if (num_frames!=((contents.size() - 5) / 21))
    {
        QMessageBox::information(0,"error","specified number of frames does not equal actual number of frames");
        num_frames = (contents.size() - 5) / 21;
    }

    for (int k=0;k<num_frames*21;k+=21) //where k is the fileoffset
    {
        TanFrame* frame = new TanFrame;
        frame->frame_start = contents[5+k].toInt();  //set num_frames
        frame->thumbnail = QImage(120, 200, QImage::Format_RGB32);
        frame->thumbnail.fill(QColor(90,90,90));
        int rgb[3]; //holds an rgb value
        //calculate frame duration

        hype.clear();   //clear QStringList
        for (int i=0;i<TAN_DEFAULT_ROWS;i++) //the increment for rows
        {
            hype = contents[i+k+6].split(QRegExp(" "),QString::SkipEmptyParts); //delimit by spaces for row

            if (hype.size()!=TAN_DEFAULT_COLS*3)
            {
                QMessageBox::information(0,"error","frame contains invalid number of rgb values");
                return;
            }
            for (int j=0,g=0;j<TAN_DEFAULT_COLS*3;j+=3,g++) //the increment for columns
            {
                rgb[0] = hype[j].toInt();
                rgb[1] = hype[j+1].toInt();
                rgb[2] = hype[j+2].toInt();
                if ((rgb[0]<0)||(rgb[0]>255)||(rgb[1]<0)||(rgb[1]>255)||(rgb[2]<0)||(rgb[2]>255)) //error checking on rgb values
                {
                    QMessageBox::information(0,"error","frame contains nonvalid rgb colors");
                    return;
                }
                frame->pixels[g][i].color.setRgb(rgb[0],rgb[1],rgb[2],255);
            }
        }
        //got a frame!
        prospective->m_frames.append(frame); //add the frame to the linked list
    }

    //if we've gotten this far without returning, the file is good and the real project can be set to the value of the temp

    clearThumbnails();
    project = TanFile(prospective);
    addThumbnail();

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

    ui->pushButton_next->setIcon(QIcon());
    ui->pushButton_next->setStyleSheet(QString("background-color: #e0e0e0"));
    ui->pushButton_next->setEnabled(false);
    ui->pushButton_prev->setIcon(QIcon());
    ui->pushButton_prev->setStyleSheet(QString("background-color: #e0e0e0"));
    ui->pushButton_prev->setEnabled(false);

    updateGUIColorButtons();

    for(int i=0; i<TAN_DEFAULT_ROWS; i++)
        for(int j=0; j<TAN_DEFAULT_COLS; j++)
            ui->gridLayout->itemAtPosition(i,j)->widget()->setStyleSheet(QString("background-color: " + (*project.currFrame)->pixels[j][i].color.name()));
    ui->spinBox->setValue((*project.currFrame)->frame_length);

    if (project.m_frames.size() > 1)
    {
        generateThumbnail((*(project.currFrame+1)));
        ui->pushButton_delete->setEnabled(true);
        ui->pushButton_next->setEnabled(true);
        ui->pushButton_next->setIcon(QIcon(QPixmap::fromImage((*(project.currFrame+1))->thumbnail, Qt::AutoColor)));
        ui->pushButton_next->setIconSize(QSize(240,400));

        for (QList<TanFrame*>::iterator i = (project.m_frames.begin()+1); i != project.m_frames.end(); i++)
        {
            generateThumbnail((*i));
            addThumbnailToEnd((*i)->thumbnail, (*i));
        }
    }

    on_change_frame();
    nothingToSave = true;
}

void MainWindow::newFile()
{
    if (!saveSequence()) return;
    clearThumbnails();
    project = TanFile();
    addThumbnail();

    for(int i=0; i<TAN_DEFAULT_ROWS; i++)
        for(int j=0; j<TAN_DEFAULT_COLS; j++)
            ui->gridLayout->itemAtPosition(i,j)->widget()->setStyleSheet(QString("background-color: #000000"));
    ui->spinBox->setValue((*project.currFrame)->frame_length);
    ui->pushButton_next->setIcon(QIcon());
    ui->pushButton_next->setStyleSheet(QString("background-color: #e0e0e0"));
    ui->pushButton_next->setEnabled(false);
    ui->pushButton_prev->setIcon(QIcon());
    ui->pushButton_prev->setStyleSheet(QString("background-color: #e0e0e0"));
    ui->pushButton_prev->setEnabled(false);
    project.setLeftColor(255,255,255);
    project.setRightColor(255,255,255);
    updateGUIColorButtons();
    on_change_frame();
    nothingToSave = true;
}

void MainWindow::save()
{
    if (project.Save()) nothingToSave = true;
}

void MainWindow::saveAs()
{
    //qDebug("saving as");
    if (project.SaveAs()) nothingToSave = true;
}

// Create the grid of cell widgets
void MainWindow::m_generateFrame(int rows, int cols)
{
	int i = 0, j = 0;
	//QFrame *m_Frame = ui->frame;
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
			// Relocate this job to TanFrame project at some point?
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
	QString m_cellName;
	int i = 0, j = 0;

	for (i=0; i<rows; i++)
	{
		for (j=0; j<cols; j++)
		{
			// Generate the name for each cell, based on rows and cols
			// Relocate this job to TanFrame *project at some point
			m_cellName = "cell" + (QString("%1").arg((i*cols + j), 3, 10, QChar('0')));
			CellWidget *m_cellWidget = MainWindow::findChild<CellWidget*>(m_cellName);
			delete m_cellWidget;
			m_cellWidget = 0;
		}
	}
}


// Connecting all the cells to the same click handler
void MainWindow::m_connectCellSignals(CellWidget *m_cell)
{
    connect(m_cell, SIGNAL(clicked(const int, const int, const char)), this, SLOT(cell_clicked(const int, const int, const char)));
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
    if (m_color == (*project.currFrame)->pixels[col][row].color) return;
    // Then update the cell color
    on_change_color(row, col, m_color);
    // And update the corresponding color in the Tan file representation
    project.storeFrameColor(row,col,m_color);
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
}

void MainWindow::updateGUIColorButtons()
{
    ui->label_2->setText(project.getLeftColor().name());
    QString qss = ("background-color: " + project.getLeftColor().name());
    ui->pushButton_l->setStyleSheet(qss);

    ui->label_3->setText(project.getRightColor().name());
    qss = ("background-color: " + project.getRightColor().name());
    ui->pushButton_r->setStyleSheet(qss);
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
                    //qDebug() << x << " " << y << " " << a << " " << b << " " << temp << " | " << tempColor.name();
                    (*project.currFrame)->thumbnail.setPixelColor(((x*9+6)+1+b), ((y*9+10)+1+a), tempColor);
                }
            }
            (*project.currFrame)->thumbnail.setPixelColor(((x*9+6)+1), ((y*9+10)+1), QColor(90,90,90));//ui->gridLayout->itemAtPosition(x,y)->widget()->palette().color(QWidget::backgroundRole()));
            (*project.currFrame)->thumbnail.setPixelColor(((x*9+6)+8), ((y*9+10)+1), QColor(90,90,90));//ui->gridLayout->itemAtPosition(x,y)->widget()->palette().color(QWidget::backgroundRole()));
            (*project.currFrame)->thumbnail.setPixelColor(((x*9+6)+1), ((y*9+10)+8), QColor(90,90,90));//ui->gridLayout->itemAtPosition(x,y)->widget()->palette().color(QWidget::backgroundRole()));
            (*project.currFrame)->thumbnail.setPixelColor(((x*9+6)+8), ((y*9+10)+8), QColor(90,90,90));//ui->gridLayout->itemAtPosition(x,y)->widget()->palette().color(QWidget::backgroundRole()));
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
            tempColor = ptr->pixels[x][y].color;
            for (int a = 0; a < 8; a++)
            {
                for (int b = 0; b < 8; b++)
                {
                    //qDebug() << x << " " << y << " " << a << " " << b << " " << temp << " | " << tempColor.name();
                    ptr->thumbnail.setPixelColor(((x*9+6)+1+b), ((y*9+10)+1+a), tempColor);
                }
            }
            ptr->thumbnail.setPixelColor(((x*9+6)+1), ((y*9+10)+1), QColor(90,90,90));//ui->gridLayout->itemAtPosition(x,y)->widget()->palette().color(QWidget::backgroundRole()));
            ptr->thumbnail.setPixelColor(((x*9+6)+8), ((y*9+10)+1), QColor(90,90,90));//ui->gridLayout->itemAtPosition(x,y)->widget()->palette().color(QWidget::backgroundRole()));
            ptr->thumbnail.setPixelColor(((x*9+6)+1), ((y*9+10)+8), QColor(90,90,90));//ui->gridLayout->itemAtPosition(x,y)->widget()->palette().color(QWidget::backgroundRole()));
            ptr->thumbnail.setPixelColor(((x*9+6)+8), ((y*9+10)+8), QColor(90,90,90));//ui->gridLayout->itemAtPosition(x,y)->widget()->palette().color(QWidget::backgroundRole()));
        }
    }
}

void MainWindow::on_pushButton_prev_clicked()
{
    on_change_frame();
    switchSelectedThumbnail((project.currFrame-project.m_frames.begin())-1);

    ui->pushButton_next->setEnabled(true);
    ui->pushButton_next->setIcon(QIcon(QPixmap::fromImage((*project.currFrame)->thumbnail, Qt::AutoColor)));
    ui->pushButton_next->setIconSize(QSize(240,400));

    //qDebug() << (project.currFrame-project.m_frames.begin());
    //project.currFrame--;
    int temp = (project.currFrame-project.m_frames.begin());
    project.currFrame = (project.m_frames.begin()+temp-1);
    //qDebug() << (project.currFrame-project.m_frames.begin());

    if ((project.currFrame-project.m_frames.begin()) == 0)
    {
        ui->pushButton_prev->setIcon(QIcon());
        ui->pushButton_prev->setStyleSheet(QString("background-color: #e0e0e0"));
        ui->pushButton_prev->setEnabled(false);
    }
    else
    {
        ui->pushButton_prev->setEnabled(true);
        ui->pushButton_prev->setIcon(QIcon(QPixmap::fromImage((*(project.m_frames.begin()+(project.currFrame-project.m_frames.begin())-1))->thumbnail, Qt::AutoColor)));
        ui->pushButton_prev->setIconSize(QSize(240,400));
    }

    QString qss;
    for(int i=0; i<TAN_DEFAULT_ROWS; i++)
        for(int j=0; j<TAN_DEFAULT_COLS; j++)
            ui->gridLayout->itemAtPosition(i,j)->widget()->setStyleSheet(QString("background-color: " + (*project.currFrame)->pixels[j][i].color.name()));
    ui->spinBox->setValue((*project.currFrame)->frame_length);
}

void MainWindow::on_pushButton_next_clicked()
{
    on_change_frame();
    switchSelectedThumbnail((project.currFrame-project.m_frames.begin())+1);

    ui->pushButton_prev->setEnabled(true);
    ui->pushButton_prev->setIcon(QIcon(QPixmap::fromImage((*project.currFrame)->thumbnail, Qt::AutoColor)));
    ui->pushButton_prev->setIconSize(QSize(240,400));

    //qDebug() << (project.currFrame-project.m_frames.begin()) << " !!";
    //project.currFrame++;
    int temp = (project.currFrame-project.m_frames.begin());
    //qDebug() << temp << " !!!";
    project.currFrame = (project.m_frames.begin()+temp+1);
    //qDebug() << (project.currFrame-project.m_frames.begin()) << " | " << (project.m_frames.end()-project.m_frames.begin());

    if ((project.currFrame-project.m_frames.begin()) == (project.m_frames.end()-1-project.m_frames.begin()))
    {
        ui->pushButton_next->setIcon(QIcon());
        ui->pushButton_next->setStyleSheet(QString("background-color: #e0e0e0"));
        ui->pushButton_next->setEnabled(false);
    }
    else
    {
        ui->pushButton_next->setEnabled(true);
        ui->pushButton_next->setIcon(QIcon(QPixmap::fromImage((*(project.currFrame+1))->thumbnail, Qt::AutoColor)));
        ui->pushButton_next->setIconSize(QSize(240,400));
    }

    for(int i=0; i<TAN_DEFAULT_ROWS; i++)
        for(int j=0; j<TAN_DEFAULT_COLS; j++)
            ui->gridLayout->itemAtPosition(i,j)->widget()->setStyleSheet(QString("background-color: " + (*project.currFrame)->pixels[j][i].color.name()));
    ui->spinBox->setValue((*project.currFrame)->frame_length);
}

void MainWindow::switchCurrentFrame(int index)
{
    if (index < 0 || index >= project.m_frames.size()) return;
    on_change_frame();
    switchSelectedThumbnail(index);

    project.currFrame = (project.m_frames.begin()+index);

    if (index == 0)
    {
        ui->pushButton_prev->setIcon(QIcon());
        ui->pushButton_prev->setStyleSheet(QString("background-color: #e0e0e0"));
        ui->pushButton_prev->setEnabled(false);
    }
    else
    {
        ui->pushButton_prev->setEnabled(true);
        ui->pushButton_prev->setIcon(QIcon(QPixmap::fromImage((*(project.currFrame-1))->thumbnail, Qt::AutoColor)));
        ui->pushButton_prev->setIconSize(QSize(240,400));
    }

    if (index == (project.m_frames.size()-1))
    {
        ui->pushButton_next->setIcon(QIcon());
        ui->pushButton_next->setStyleSheet(QString("background-color: #e0e0e0"));
        ui->pushButton_next->setEnabled(false);
    }
    else
    {
        ui->pushButton_next->setEnabled(true);
        ui->pushButton_next->setIcon(QIcon(QPixmap::fromImage((*(project.currFrame+1))->thumbnail, Qt::AutoColor)));
        ui->pushButton_next->setIconSize(QSize(240,400));
    }

    for(int i=0; i<TAN_DEFAULT_ROWS; i++)
        for(int j=0; j<TAN_DEFAULT_COLS; j++)
            ui->gridLayout->itemAtPosition(i,j)->widget()->setStyleSheet(QString("background-color: " + (*project.currFrame)->pixels[j][i].color.name()));
    ui->spinBox->setValue((*project.currFrame)->frame_length);
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
            tempColor = thumbnail.pixelColor(((x*9)+8),((y*9)+12));
            for (int a = 0; a < 3; a++)
            {
                for (int b = 0; b < 3; b++)
                {
                    //qDebug() << x << " " << y << " " << a << " " << b << " " << temp << " | " << tempColor.name();
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

    ui->pushButton_prev->setEnabled(true);
    ui->pushButton_prev->setIcon(QIcon(QPixmap::fromImage((*project.currFrame)->thumbnail, Qt::AutoColor)));
    ui->pushButton_prev->setIconSize(QSize(240,400));

    QString qss;
    //set all pixels in grid to black
    for(int i=0; i<TAN_DEFAULT_ROWS; i++)
        for(int j=0; j<TAN_DEFAULT_COLS; j++)
            ui->gridLayout->itemAtPosition(i,j)->widget()->setStyleSheet("background-color: #000000");
    ui->spinBox->setValue((*project.currFrame)->frame_length);
    nothingToSave = false;
    on_change_frame();
}

void MainWindow::newFrameCopy()
{
    if (project.m_frames.size() == 1) ui->pushButton_delete->setEnabled(true);
    generateThumbnailCurrent();
    project.newFrame();
    addCurrentThumbnail();

    ui->pushButton_prev->setEnabled(true);
    ui->pushButton_prev->setIcon(QIcon(QPixmap::fromImage((*project.currFrame)->thumbnail, Qt::AutoColor)));
    ui->pushButton_prev->setIconSize(QSize(240,400));

    QString qss;
    for(int i=0; i<TAN_DEFAULT_ROWS; i++)
    {
        for(int j=0; j<TAN_DEFAULT_COLS; j++)
        {
            qss = "background-color: " + (*project.currFrame)->pixels[j][i].color.name();
            ui->gridLayout->itemAtPosition(i,j)->widget()->setStyleSheet(qss);
        }
    }
    ui->spinBox->setValue((*project.currFrame)->frame_length);
    nothingToSave = false;
    on_change_frame();
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    int totalTime = 0;                      //frame_legnth's < currFrame added together
    QList<TanFrame*>::iterator i; //iterator for linked list
    for(i = project.m_frames.begin(); i != project.m_frames.end(); i++){ //from begining of linked list to end of linked list
        if(i == project.currFrame){                               //if iterator is on your current frame
            (*i)->frame_length = arg1;                             //set frame length to the value in the spin box
            (*i)->frame_start = totalTime;                         //set your current frame start time to all previous frame lengths added together
            //qDebug() << (*i)->frame_length << (*i)->frame_start;
        }else if(i < project.currFrame) {                          //if iterator is on a frame < your current frame
            totalTime = totalTime + (*i)->frame_length;            //add frame legnth to total time
        }
    }
    nothingToSave = false;
}

void MainWindow::clearThumbnails() // used when opening a project or starting a new project
{
    QPushButton* temp;
    for (int c = 0; c < project.m_frames.size(); c++)
    {
        temp = ((QPushButton*)(ui->horizontalLayout_2->itemAt(0)->widget()));
        ui->horizontalLayout_2->removeWidget(temp);
        delete temp;
        ui->horizontalLayout_2->update();
    }
}

void MainWindow::addThumbnail() // only used when starting a new project;
{
    QPushButton *button = newThumbnail(QString(":/resources/currSelect.png"), (*project.currFrame));
    ui->horizontalLayout_2->addWidget(button);
    button->show();
    ui->horizontalLayout_2->update();
}

void MainWindow::addThumbnailToEnd(QImage in, TanFrame* ptr)
{
    QPushButton *button = newThumbnail(in, ptr);
    ui->horizontalLayout_2->addWidget(button);
    button->show();
    ui->horizontalLayout_2->update();
}

void MainWindow::switchSelectedThumbnail(int index) // used when the user switches frames
{
    generateThumbnailCurrent();
    ((QPushButton*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin()))->widget()))->setIcon(QIcon(QPixmap::fromImage(scaleDown((*project.currFrame)->thumbnail), Qt::AutoColor)));
    ((QPushButton*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin()))->widget()))->setIconSize(QSize(120,200));

    ((QPushButton*)(ui->horizontalLayout_2->itemAt(index)->widget()))->setIcon(QIcon(QPixmap::fromImage(QImage(":/resources/currSelect.png"), Qt::AutoColor)));
    ((QPushButton*)(ui->horizontalLayout_2->itemAt(index)->widget()))->setIconSize(QSize(120,200));
}

void MainWindow::addCurrentThumbnail() // used when creating a new frame (also switches selected frame)
{
    ((QPushButton*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin()-1))->widget()))->setIcon(QIcon(QPixmap::fromImage(scaleDown((*(project.currFrame-1))->thumbnail), Qt::AutoColor)));
    ((QPushButton*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin()-1))->widget()))->setIconSize(QSize(120,200));

    QPushButton *button = newThumbnail(QString(":/resources/currSelect.png"), (*project.currFrame));
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
    //qDebug() << (*project.currFrame)->frame_length;
//    qDebug() << "====================";
//    QString temp = "";
//    for (int c = 0; c < 12; c++)
//        temp.append((*project.currFrame)->pixels[c][0].color == QColor("#000000") ? "I" : "O");
//    qDebug() << temp;
//    qDebug() << "==================== " << (project.currFrame-project.m_frames.begin());
}

void MainWindow::on_pushButton_delete_clicked()
{
    QPushButton* temp;
    if ((project.currFrame-project.m_frames.begin()) == 0)
    { // deleting the start of the queue
        ((QPushButton*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin())+1)->widget()))->setIcon(QIcon(QPixmap::fromImage(QImage(":/resources/currSelect.png"), Qt::AutoColor)));
        ((QPushButton*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin())+1)->widget()))->setIconSize(QSize(120,200));

        temp = ((QPushButton*)(ui->horizontalLayout_2->itemAt(0)->widget()));
        ui->horizontalLayout_2->removeWidget(temp);
        delete temp;
        ui->horizontalLayout_2->update();
        qDebug() << (project.currFrame-project.m_frames.begin()) << "A";
        project.removeCurrentFrame();
        project.currFrame = project.m_frames.begin();
        qDebug() << (project.currFrame-project.m_frames.begin()) << "A";
        if (project.m_frames.size() == 1)
        {
            ui->pushButton_next->setIcon(QIcon());
            ui->pushButton_next->setStyleSheet(QString("background-color: #e0e0e0"));
            ui->pushButton_next->setEnabled(false);
        }
        else
        {
            ui->pushButton_next->setEnabled(true);
            ui->pushButton_next->setIcon(QIcon(QPixmap::fromImage((*(project.m_frames.begin()+(project.currFrame-project.m_frames.begin())+1))->thumbnail, Qt::AutoColor)));
            ui->pushButton_next->setIconSize(QSize(240,400));
        }
    }
    else
    { // not deleting the start of the queue
        ((QPushButton*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin())-1)->widget()))->setIcon(QIcon(QPixmap::fromImage(QImage(":/resources/currSelect.png"), Qt::AutoColor)));
        ((QPushButton*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin())-1)->widget()))->setIconSize(QSize(120,200));

        temp = ((QPushButton*)(ui->horizontalLayout_2->itemAt((project.currFrame-project.m_frames.begin()))->widget()));
        ui->horizontalLayout_2->removeWidget(temp);
        delete temp;
        ui->horizontalLayout_2->update();
        qDebug() << (project.currFrame-project.m_frames.begin()) << "B";
        project.removeCurrentFrame();
        qDebug() << (project.currFrame-project.m_frames.begin()) << "B";

        if ((project.currFrame-project.m_frames.begin()) == 0)
        {
            ui->pushButton_prev->setIcon(QIcon());
            ui->pushButton_prev->setStyleSheet(QString("background-color: #e0e0e0"));
            ui->pushButton_prev->setEnabled(false);
        }
        else
        {
            ui->pushButton_prev->setEnabled(true);
            ui->pushButton_prev->setIcon(QIcon(QPixmap::fromImage((*(project.m_frames.begin()+(project.currFrame-project.m_frames.begin())-1))->thumbnail, Qt::AutoColor)));
            ui->pushButton_prev->setIconSize(QSize(240,400));
        }
    }

    for(int i=0; i<TAN_DEFAULT_ROWS; i++)
        for(int j=0; j<TAN_DEFAULT_COLS; j++)
            ui->gridLayout->itemAtPosition(i,j)->widget()->setStyleSheet(QString("background-color: " + (*project.currFrame)->pixels[j][i].color.name()));
    ui->spinBox->setValue((*project.currFrame)->frame_length);

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

void MainWindow::on_undo() {
    QString qss;
    if (m_undo_index > 0) {
        m_undo_index--;
        qDebug() << m_undo_index << "-";
        struct Change *change = *(m_changes.begin() + m_undo_index);
        QString m_cellName = "cell" + (QString("%1").arg((change->x*12 + change->y), 3, 10, QChar('0')));
        CellWidget *m_cellWidget = MainWindow::findChild<CellWidget*>(m_cellName);
        m_cellWidget->setColor(change->old_color);
        (*project.currFrame)->pixels[change->y][change->x].color = change->old_color;
    }
    if (m_undo_index == 0) {
        ui->pushButton_undo->setEnabled(false);
        undoAct->setEnabled(false);
    }
    ui->pushButton_redo->setEnabled(true);
    redoAct->setEnabled(true);
}

void MainWindow::on_redo() {
    if (m_undo_index < m_changes.size()) {
        qDebug() << m_undo_index << "+";
        struct Change *change = *(m_changes.begin() + m_undo_index);
        QString m_cellName = "cell" + (QString("%1").arg((change->x*12 + change->y), 3, 10, QChar('0')));
        CellWidget *m_cellWidget = MainWindow::findChild<CellWidget*>(m_cellName);
        m_cellWidget->setColor(change->new_color);
        (*project.currFrame)->pixels[change->y][change->x].color = change->new_color;
        m_undo_index++;
    }
    if (m_undo_index == m_changes.size()) {
        ui->pushButton_redo->setEnabled(false);
        redoAct->setEnabled(false);
    }
    if (m_undo_index > 0) {
        ui->pushButton_undo->setEnabled(true);
        undoAct->setEnabled(true);
    }
}

void MainWindow::on_change_color(int x, int y, const QColor& p_color) {
    while (m_undo_index < m_changes.size()) {
        m_changes.removeLast();
    }
    //qDebug() << m_undo_index << x << y;
    struct Change *change = new struct Change;
    QString m_cellName = "cell" + (QString("%1").arg((x*12 + y), 3, 10, QChar('0')));
    //CellWidget *cell = MainWindow::findChild<CellWidget*>(m_cellName);

    change->x = x;
    change->y = y;
    change->old_color = QColor(ui->gridLayout->itemAtPosition(x,y)->widget()->styleSheet().mid((ui->gridLayout->itemAtPosition(x,y)->widget()->styleSheet().length())-7));//cell->getColor();
    change->new_color = p_color;
    m_changes.append(change);
    m_undo_index++;
    //cell->setColor(p_color);
    ui->gridLayout->itemAtPosition(x,y)->widget()->setStyleSheet((QString("background-color: ").append(p_color.name())));
    undoAct->setEnabled(true);
    redoAct->setEnabled(false);
    ui->pushButton_undo->setEnabled(true);
    ui->pushButton_redo->setEnabled(false);
}

void MainWindow::on_change_frame() {
    m_undo_index = 0;
    m_changes.clear();

    //for (int x = 0; x < 12; x++) {
    //    for (int y = 0; y < 20; y++)  {
    //        QString m_cellName = "cell" + (QString("%1").arg((x*12 + y), 3, 10, QChar('0')));
    //        CellWidget *m_cellWidget = MainWindow::findChild<CellWidget*>(m_cellName);
    //        m_cellWidget->setColor((*project.currFrame)->pixels[x][y].color);
    //    }
    //}
    ui->pushButton_undo->setEnabled(false);
    ui->pushButton_redo->setEnabled(false);
    undoAct->setEnabled(false);
    redoAct->setEnabled(false);
}


void MainWindow::on_pushButton_clearFrame_clicked()
{
    for(int i=0; i<TAN_DEFAULT_ROWS; i++)
    {
        for(int j=0; j<TAN_DEFAULT_COLS; j++)
        {
            (*project.currFrame)->pixels[j][i].color = QColor(0,0,0,0);
            ui->gridLayout->itemAtPosition(i,j)->widget()->setStyleSheet(QString("background-color: #000000"));
        }
    }
    on_change_frame();
}
