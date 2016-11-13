#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

		m_generateFrame(12, 20);

    ui->comboBox->addItem("new");       //instantiates the items in the comboBox
    ui->comboBox->addItem("open");      //
    ui->comboBox->addItem("save as");   //
    ui->comboBox->addItem("exit");      //
}

MainWindow::~MainWindow()
{
	m_destroyFrame(12, 20);

	delete ui;
}



void MainWindow::openFile()    //when open is clicked
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open tan file"),"C:/",    //user selects fileName
                       "Tan File (*.tan*);;All files (*.*)");
    if (fileName=="")
        return;

    QStringList contents = getFileContents(fileName);   //loads the contents of the file line by line into
                                                        //QStringList contents

    QString m_filename_tan, m_filename_wav;         //holds filename and audio filename
    QColor m_filename_curr, m_filename_preset[15];  //holds current color and the 16 preset colors
    int num_frames = 1; //holds the number of frames in the project

    //get fileName
    m_filename_tan = fileName;

    //get Audio Filename
    if (contents[0]!="0.4")    //error checking
    {
        QMessageBox::information(0,"error","not supported version");
        return;
    }
    m_filename_wav = contents[1];   //set audio filename

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
    m_filename_curr.fromRgb(r,g,b,255);     //set the rgb value

    //get the preset RGB values
    QStringList buffer; //holds parsed input string
    int presetRGB[48];  //holds each individual rgb value

    buffer = contents[3].split(QRegExp(" "),QString::SkipEmptyParts); //delimit by spaces

    for (int i=0;i<48;i++)
        presetRGB[i]=buffer[i].toInt(); //places ints into presetRGB
    for (int i=0;i<16;i++)
    {
        if ((presetRGB[i*3]<0)||(presetRGB[i*3]>255)||(presetRGB[(i*3)+1]<0)||
                (presetRGB[(i*3)+1]>255)||(presetRGB[(i*3)+2]<0)||
                (presetRGB[(i*3)+2]>255))                          //error checking on rgb values
        {
            QMessageBox::information(0,"error","preset rgb colors are not within range (0-255)");
            return;
        }
        m_filename_preset[i].fromRgb(presetRGB[i*3],presetRGB[(i*3)+1],presetRGB[(i*3)+2],255);
    }

    //get the number of frames
    QStringList hype = contents[4].split(QRegExp(" "),QString::SkipEmptyParts); //delimit by spaces
    num_frames = hype[0].toInt();  //set num_frames
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

    //get the frames
    QTime start;   //the starting time for frame
    int frameRGB[20][36];   //2d array of ints (20 rows, 36 integers)
    QColor frame_grid[20][12];  //holds rgb values for a frame

    if (contents[5].toInt()!=0) //error checking the first frame start time
    {
        QMessageBox::information(0,"error","the first frame must start at 0ms");
        return;
    }

    QStringList bof;    //will holds delimited strings
    int i=0;
    int j=0;    //incrementors i=row and j is the number of integers in each
    while (i<20)
    {
        bof = contents[i+6].split(QRegExp(" "),QString::SkipEmptyParts); //delimit by spaces for row
        while (j<36)
        {
            frameRGB[i][j]=bof[j].toInt();  //convert to int and place into frameRGB
            j++;
        }
        j=0;
        i++;
    }

    for (int i=0;i<20;i++)
        for (int j=0;j<12;j++)
            frame_grid[i][j].fromRgb(frameRGB[i][(j*3)], frameRGB[i][(j*3)+1], frameRGB[i][(j*3)+2], 255);
}


void MainWindow::newFile()
{
    QMessageBox::StandardButton reply;

    /* Create Message Box
     * Title of message box : "Tower Lights"
     * Prompt message : "Would you like to save?"
     * 3 button choices : "Save", "No", "Cancel"
    */

    reply = QMessageBox::question(this, "Tower Lights", "Would you like to save?",
                                  QMessageBox::Save|QMessageBox::No|QMessageBox::Cancel);


    if(reply == QMessageBox::Save){
        TanFile newFile;
        if(QString(newFile.getFileName()).isEmpty()){ // check if there is a file name
            //SaveAs();
            qDebug() << "SaveAs\n";
        }else{
            //Save();
            qDebug() << "Save\n";
        }
    }else if(reply == QMessageBox::No){
        TanFile newFile; //creates new blank .tan file
        //do we delete a .tan file if it was never saved in the first place?
    }else if(reply == QMessageBox::Cancel){
        //do nothing
    }
}


// Create the grid of cell widgets
void MainWindow::m_generateFrame(int rows, int cols)
{
	int i = 0, j = 0;
	QGridLayout *m_FrameLayout = ui->gridLayout_2;
	QString m_cellName;
	QSizePolicy m_cellSizePolicy;
	QSize m_cellSize(36,36);

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
			// Relocate this job to TanFrame *project at some point
			m_cellName = "cell" + (QString("%1").arg((i*cols + j), 3, 10, QChar('0')));
			CellWidget *m_cellWidget = new CellWidget(m_cellName, i, j);
			m_cellWidget->setMinimumSize(m_cellSize);
			m_cellWidget->setSizePolicy(m_cellSizePolicy);

			// Adding cell widget to the frame's gridLayout
			m_FrameLayout->addWidget(m_cellWidget, i, j);
			// Connecting each cell's signals to appropriate generic slots
			m_connectCellSignals(m_cellWidget);
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
	// Can't currently access -- is a private member
	//project->m_frames->pixel[row][col] = m_color;
}


// Obtain a reference to a cell widget by name, and set its color.
// This is the function to call when opening or creating a new Tan file.
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


// Generate a message box announcing the value of the custom coordinate property for a cell
void MainWindow::m_alertCoords(QString m_cellName)
{
	QPushButton *m_cell = MainWindow::findChild<QPushButton*>(m_cellName);
	const char *m_cellPropertyName = "coord";
	QString m_coord = m_cell->property(m_cellPropertyName).toString();
	QMessageBox m_msg;

	m_msg.setWindowTitle("Hi from Cell " + m_coord + "!");
	m_msg.setText("This is Cell " + m_coord + ".");
	m_msg.setInformativeText("This is a stand-in for tracking which cell was clicked and signaling its coordinates: " + m_coord + ".");

	m_msg.exec();
}


void MainWindow::on_comboBox_activated(const QString &arg1)
{
    if (arg1=="open")       //open a file
        openFile();
    if (arg1=="save as")    //save the file
        project->SaveAs();
    if (arg1=="new")        //make a new file
        newFile();
    if (arg1=="exit")       //quit the application
        QApplication::quit();
}
