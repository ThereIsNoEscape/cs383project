#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "openFile.cpp"
#include <Qdebug>
#include <QString>
#include <QMessageBox>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("new");       //instantiates the items in the comboBox
    ui->comboBox->addItem("open");      //
    ui->comboBox->addItem("save as");   //
    ui->comboBox->addItem("exit");      //

    m_connectCellButtons(40);
}

MainWindow::~MainWindow()
{
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
    project.setfilename(fileName);

    //check version
    if (contents[0]!="0.4")    //error checking
    {
        QMessageBox::information(0,"error","not supported version");
        return;
    }
    //set audio filename
    project.setaudiofile(contents[1]);   //set audio filename

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
    project.setleftclr(r,g,b);     //set the rgb value

    //get the preset RGB values
    QStringList buffer; //holds parsed input string
    int presetRGB[48];  //holds each individual rgb value

    buffer = contents[3].split(QRegExp(" "),QString::SkipEmptyParts); //delimit by spaces

    for (int i=0;i<48;i++)
        presetRGB[i]=buffer[i].toInt(); //places ints into presetRGB

    project.setpresetclr(presetRGB);

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

    int frameRGB[36][20];   //holds the frame rgbs
    project.m_frames.clear(); //clear the linked list

    for (int k=0;k<num_frames*21;k+=21) //where k is the fileoffset
    {
        TanFrame frame;
        frame.frame_start = contents[5+k].toInt();  //set num_frames
        //calculate frame duration

        hype.clear();   //clear QStringList
        for (int i=0;i<20;i++) //the increment for rows
        {
            hype = contents[i+k+6].split(QRegExp(" "),QString::SkipEmptyParts); //delimit by spaces for row
            if (hype.size()!=36)
            {
                    QMessageBox::information(0,"error","frame contains invalid number of rgb values");
                    return;
            }
            int rgb[3]; //holds an rgb value
            for (int j=0,g=0;j<36;j++,g++) //the increment for columns
            {
                frameRGB[j][i]=hype[j].toInt();  //convert to int and place into frameRGB
                if (g<3)
                {
                    rgb[g]=frameRGB[j][i];  //place the frameRGB into rgb
                    if ((rgb[g]<0)||(rgb[g]>255)) //error checking on rgb value
                    {
                        QMessageBox::information(0,"error","frame contains nonvalid rgb colors");
                        return;
                    }
                }
                else    //every 3 integers
                {
                    frame.pixels[j/3-1][i].color.fromRgb(rgb[0],rgb[1],rgb[2],255); //add color to a pixel
                    g=0;    //reset incrementor
                    rgb[g]=frameRGB[j][i];  //place the frameRGB into rgb[0]
                    if ((rgb[g]<0)||(rgb[g]>255)) //error checking on rgb value
                    {
                        QMessageBox::information(0,"error","frame contains nonvalid rgb colors");
                        return;
                    }
                }
            }
            frame.pixels[11][i].color.fromRgb(rgb[0],rgb[1],rgb[2],255); //add color to last pixel in row
        }
        //got a frame!
        project.m_frames.append(frame); //add the frame to the linked list
    }
//  qDebug() << project.m_frames.begin()->pixels[0][0].color;
    /*************************************************************************************/
    /*
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
            */
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


// Get the name of the referenced object.
QString MainWindow::m_getObjName(QObject *m_obj) {
	QString m_name = m_obj->property("objectName").toString();
	return m_name;
}


// Connecting all the cells to the same click handler
void MainWindow::m_connectCellButtons(int cellCt)
{
	QString m_cellName;
	int i=0;
	// Cycling through all cells
	for(i=0; i<cellCt; i++)
	{
		// Generate the name for each cell
		m_cellName = "cell" + (QString("%1").arg(i, 3, 10, QChar('0')));
		// Acquire a reference to the object
		QPushButton *m_cell = ui->frame->findChild<QPushButton *>(m_cellName, Qt::FindChildrenRecursively);
		// If valid, connect up the clicked() signal to on_cell_clicked()
		if(m_cell->objectName() == m_cellName) {
			connect(m_cell, SIGNAL(clicked()), this, SLOT(on_cell_clicked()));
		}
	}
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


void MainWindow::on_comboBox_activated(const QString &arg1)
{
    if (arg1=="open")       //open a file
        openFile();
    //if (arg1=="save as")    //save the file
        //project->SaveAs();
    if (arg1=="new")        //make a new file
        newFile();
    if (arg1=="exit")       //quit the application
        QApplication::quit();
}
