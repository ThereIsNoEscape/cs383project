#include "openfile.h"
#include "mainwindow.h"

QStringList getFileContents(QString fileName)
{
    QString buffer;
    QStringList fileContents;	//will hold the contents of the file
    QFile fp(fileName);

    if (fp.open(QIODevice::ReadOnly))	//error checking
    {
        //the file is open
        QTextStream in(&fp);
        buffer = in.readAll();  //read file into Qstring buffer
        fileContents = buffer.split(QRegExp("\n|\r"),QString::SkipEmptyParts);  //delimiti buffer into Qstring list
        fp.close();	//close the file
        return fileContents;
    }
    else
    {
        //the file could NOT be opened
        QMessageBox::information(0,"error",fp.errorString());
        return fileContents;
    }
}

int MainWindow::load(QString fileName)
{
    TanFile* prospective = new TanFile(fileName);//this will temporarily hold the information so that if there's something wrong with this file we haven't written in bad data to the project object
    //this object is deleted when this function returns, so no memory is leaked
    QStringList contents = getFileContents(fileName);   //loads the contents of the file line by line into
                                                        //QStringList contents
    //check version
    if (contents[0]!="0.4")    //error checking
    {
        QMessageBox::information(0,"error","File is an unsupported version");
        return -1;
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
        return -1;
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
        return -1;
    }
    //error check dimensions
    if (hype[1]!="10" || hype[2]!="4")
    {
        QMessageBox::information(0,"error","invalid dimensions");
        return -1;
    }

    /*************************************************************************************/

    //error checking the tanfile frames
    if (((contents.size()-5) % 21)!=0)
    {
        QMessageBox::information(0,"error","frames corrupt");
        return -1;
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
                return -1;
            }
            for (int j=0,g=0;j<TAN_DEFAULT_COLS*3;j+=3,g++) //the increment for columns
            {
                rgb[0] = hype[j].toInt();
                rgb[1] = hype[j+1].toInt();
                rgb[2] = hype[j+2].toInt();
                if ((rgb[0]<0)||(rgb[0]>255)||(rgb[1]<0)||(rgb[1]>255)||(rgb[2]<0)||(rgb[2]>255)) //error checking on rgb values
                {
                    QMessageBox::information(0,"error","frame contains nonvalid rgb colors");
                    return -1;
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
    return 1;
}
