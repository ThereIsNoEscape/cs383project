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
}

MainWindow::~MainWindow()
{
	m_destroyFrame(TAN_DEFAULT_ROWS, TAN_DEFAULT_COLS);

	delete ui;
}



void MainWindow::openFile()    //when open is clicked
{
		QMessageBox::StandardButton reply;

		/* Create Message Box
		 * Title of message box : "Tower Lights"
		 * Prompt message : "Would you like to save?"
		 * 3 button choices : "Save", "No", "Cancel"
		*/

		reply = QMessageBox::question(this, "Tower Lights", "Would you like to save?",
																	QMessageBox::Save|QMessageBox::No|QMessageBox::Cancel);

		if (reply==0x00400000)  //if cancel selected
				return;
		if (reply==0x00000800)  //if save selected
		{
				project.Save();
		}

		QString fileName = QFileDialog::getOpenFileName(this, tr("Open tan file"),"C:/",    //user selects fileName
											 "Tan File (*.tan*);;All files (*.*)");
		if (fileName=="")
				return;

		QStringList contents = getFileContents(fileName);   //loads the contents of the file line by line into
																												//QStringList contents

		//get fileName
		project.setFileName(fileName);

		//check version
		if (contents[0]!="0.4")    //error checking
		{
				QMessageBox::information(0,"error","not supported version");
				return;
		}
		//set audio filename
		project.setAudioFile(contents[1]);   //set audio filename

		//view section later for audio file error checking
		/*QString last3 = ;  //get last 3 characters
		if (contents[1]=="NoAudioFile")
				m_filename_wav = "NoAudioFile"; //valid
		else
		{
				//check last 3 characters
				if (last3 == "mp3"||"mp4"||"wav")
						m_filename_wav = contents[1];   //valid audio type
				else
						QMessageBox::information(0,"error","audio format not supported");   //invalid audio type
		}*/

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
		project.setLeftColor(r,g,b);     //set the rgb value
        updateGUIColorButtons();

		//get the preset RGB values
		QStringList buffer; //holds parsed input string
		int presetRGB[TAN_DEFAULT_COLORPRESETS*3];  //holds each individual rgb value

		buffer = contents[3].split(QRegExp(" "),QString::SkipEmptyParts); //delimit by spaces

		for (int i=0;i<TAN_DEFAULT_COLORPRESETS*3;i++)
				presetRGB[i]=buffer[i].toInt(); //places ints into presetRGB

		project.setPresetColor(presetRGB);
        updateGUIColorButtons();

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

		project.m_frames.clear(); //clear the linked list
        project.m_frames.begin();   //start the linked list at the beginning

		for (int k=0;k<num_frames*21;k+=21) //where k is the fileoffset
		{
				TanFrame frame;
				frame.frame_start = contents[5+k].toInt();  //set num_frames
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
                            frame.pixels[g][i].color.setRgb(rgb[0],rgb[1],rgb[2],255);
                        }
                }
				//got a frame!
                project.m_frames.append(frame); //add the frame to the linked list
        }
}


void MainWindow::newFile()
{
    QMessageBox::StandardButton reply;

    /* Create Message Box
     * Title of message box : "Tower Lights"
     * Prompt message : "Would you like to save?"
     * 3 button choices : "Save", "No", "Cancel"
    */
    QString qss;

    reply = QMessageBox::question(this, "Tower Lights", "Would you like to save?",
                                  QMessageBox::Save|QMessageBox::No|QMessageBox::Cancel);


    if(reply == QMessageBox::Save){
        //TanFile newFile;
        if(QString(project.getFileName()).isEmpty()){ // check if there is a file name
            project.SaveAs();
            //qDebug() << "SaveAs\n";
        }else{
            project.Save();
            //qDebug() << "Save\n";
        }
        project = TanFile();
        TanFrame frame;
        for(int i=0; i<TAN_DEFAULT_ROWS; i++){
            for(int j=0; j<TAN_DEFAULT_COLS; j++){
                //frame.pixels[i][j].color.setRgb(0,0,0,255); //set all pixels in grid to black
                qss = ("background-color: #000000");
                ui->gridLayout_2->itemAtPosition(i,j)->widget()->setStyleSheet(qss);
            }
        }
        project.setLeftColor(255,255,255);
        project.setRightColor(255,255,255);
        updateGUIColorButtons();
    }else if(reply == QMessageBox::No){
        project = TanFile();
        TanFrame frame;
        for(int i=0; i<TAN_DEFAULT_ROWS; i++){
            for(int j=0; j<TAN_DEFAULT_COLS; j++){
                //frame.pixels[i][j].color.setRgb(0,0,0,255); //set all pixels in grid to black
                qss = ("background-color: #000000");
                ui->gridLayout_2->itemAtPosition(i,j)->widget()->setStyleSheet(qss);
            }
        }
        project.setLeftColor(255,255,255);
        project.setRightColor(255,255,255);
        updateGUIColorButtons();
    }else if(reply == QMessageBox::Cancel){
        //do nothing
    }
}

void MainWindow::save()
{
    project.Save();
}

void MainWindow::saveAs()
{
    qDebug("saving as");
    project.SaveAs();
}

// Create the grid of cell widgets
void MainWindow::m_generateFrame(int rows, int cols)
{
    project.setLeftColor(255,255,255);
    project.setRightColor(255,255,255);
    updateGUIColorButtons();
	int i = 0, j = 0;
	//QFrame *m_Frame = ui->frame;
	QGridLayout *m_FrameLayout = ui->gridLayout_2;
	QString m_cellName;
	QSizePolicy m_cellSizePolicy;
	QSize m_cellSize(36,36);	// Arbitrarily selected as a decent minimum ("half-inch" @ 72 ppi, less @ 96 ppi or higher resolutions)

	// Configure the size policy that every cell widget will use
	m_cellSizePolicy.setHorizontalPolicy(QSizePolicy::MinimumExpanding);
	m_cellSizePolicy.setHorizontalStretch(1);
	m_cellSizePolicy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
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
	connect(m_cell, SIGNAL(colorChanged(const int, const int, QColor)), this, SLOT(on_cell_colorChanged(const int, const int, QColor)));
}


// The primary handler for cell clicks
void MainWindow::on_cell_colorChanged(const int row, const int col, QColor m_color)
{
	//QString m_cellName = m_getObjName(QObject::sender());
	//CellWidget *m_cell = MainWindow::findChild<CellWidget*>(m_cellName);
	m_updateTanFileColor(row, col, m_color);
}


// Update the corresponding Cell struct in TanFrame when color is changed in a cell widget.
void MainWindow::m_updateTanFileColor(const int row, const int col, QColor m_color)
{
	TanFrame frame;
	frame.pixels[col][row].color = m_color;
	// Need to determine how to identify each frame
	/*
	struct TanFrame *frame = project->m_frames...@iterator@node_identifier;
	struct TanCell *cell = frame->cells[row][col];
	cell->color = m_color;
	*/
}


// Obtain a reference to a cell widget by name, and set its color.
// This is the function to call when opening or creating a new Tan file.
// Does not trigger the signal that will then cause an update to the corresponding TanFile cell
void MainWindow::m_setCellColor(QString m_cellName, QColor m_color)
{
	CellWidget *m_cell = MainWindow::findChild<CellWidget*>(m_cellName);

	m_cell->setColor(m_color);
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
}

void MainWindow::updateGUIColorButtons()
{
    ui->label_2->setText(project.getLeftColor().name());
    QString qss = ("background-color: " + project.getLeftColor().name());
    ui->pushButton_2->setStyleSheet(qss);

    ui->label_3->setText(project.getRightColor().name());
    qss = ("background-color: " + project.getRightColor().name());
    ui->pushButton_3->setStyleSheet(qss);
}

void MainWindow::on_pushButton_2_clicked()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if(color.isValid())
    {
        project.setLeftColor(color);
        updateGUIColorButtons();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if(color.isValid())
    {
        project.setRightColor(color);
        updateGUIColorButtons();
    }
}

