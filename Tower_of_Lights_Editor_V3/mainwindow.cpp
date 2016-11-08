#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "openFile.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// Connecting all the cells to the same click handler
/*
	foreach(QObject *child, ui->frame->children())
	{
		QString m_name = m_getObjName(child);
		if(m_name.startsWith("cell")) {
			connect(child, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
		}
	}
/*
	int i=0, cellCt=12;

	for(i=0; i<cellCt; i++) {
		// Generate the name for each cell
		QString m_cellName = "cell" + (QString("%1").arg(i, 2, 10, QChar('0')));
		// Connect up the clicked signal with the click handler
		connect(ui->m_cellName, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	}
*/
	// Sorry, I can't make the shorter versions above work
	connect(ui->cell000, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell001, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell002, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell003, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell004, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell005, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell006, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell007, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell008, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell009, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell010, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell011, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell012, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell013, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell014, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell015, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell016, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell017, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell018, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell019, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell020, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell021, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell022, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell023, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell024, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell025, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell026, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell027, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell028, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell029, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell030, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell031, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell032, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell033, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell034, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell035, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell036, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell037, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell038, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
	connect(ui->cell039, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_clicked()    //when open is clicked
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open tan file"),"C:/",    //user selects fileName
                       "Tan File (*.tan*);;All files (*.*)");

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

// Get the name of the referenced object.
QString MainWindow::m_getObjName(QObject *m_obj) {
	QString m_name = m_obj->property("objectName").toString();
	return m_name;
}

// Find a cell by its name,
// toggle its color,
// and toggle its state to determine appropriate color on next click.
// This function as-is is only meant for testing purposes;
// To be connected up with actual frame data eventually.
void MainWindow::m_changeCellColor(QString m_cellName)
{
	QPushButton *m_cell = MainWindow::findChild<QPushButton*>(m_cellName);
	const char *m_cellPropertyName = "activated";
	QString m_activated = m_cell->property(m_cellPropertyName).toString();
	QColor m_color = Qt::green;
	QString qss = QString("color: white;\nbackground-color: ");

	if(m_color.isValid()) {
		// Determine which state we're in and switch the state, and the color, if appropriate
		if(m_activated == "false") {
			m_activated = "true";
		}
		else {
			m_color = Qt::black;
			m_activated = "false";
		}
		// Set the color on the stylesheet after concatenating the resulting color to the style string
		qss += m_color.name();
		m_cell->setStyleSheet(qss);
		// Switch state
		m_cell->setProperty(m_cellPropertyName, m_activated);
	}
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

// The primary handler for cell clicks
void MainWindow::on_cell_clicked()
{
	QString m_cellName = m_getObjName(QObject::sender());
	m_changeCellColor(m_cellName);
	//m_alertCoords(m_cellName);
}
