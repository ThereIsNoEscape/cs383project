#include "tanfile.h"

void TanFile::newFrame()
{
    TanFrame* newf = new TanFrame;
    newf->frame_length = 25;
    newf->frame_start = (*currFrame)->frame_start + (*currFrame)->frame_length;
    for(int i = 0; i < TAN_DEFAULT_ROWS; i++)
    {
        for(int j = 0; j < TAN_DEFAULT_COLS; j++)
        {
            newf->pixels[j][i].color.setRgb(0,0,0,255);
        }
    }
    newf->thumbnail = QImage(120, 200, QImage::Format_RGB32);
    newf->thumbnail.fill(QColor(90,90,90));

    newf->m_undo_index = 0;

    //qDebug() << (currFrame-m_frames.begin());
    int temp = (currFrame-m_frames.begin());
    m_frames.insert((currFrame+1-m_frames.begin()), newf);
    currFrame = (m_frames.begin()+temp+1);
    //qDebug() << (currFrame-m_frames.begin());

    QList<TanFrame *>::iterator thing = currFrame;
    while (thing < m_frames.end()) {
        (*thing)->frame_start += newf->frame_length;
        thing++;
    }
}

void TanFile::newFrameCopy()
{
    TanFrame* newf = new TanFrame;
    newf->frame_length = (*currFrame)->frame_length;
    newf->frame_start = (*currFrame)->frame_start + (*currFrame)->frame_length;
    for(int i = 0; i < TAN_DEFAULT_ROWS; i++)
    {
        for(int j = 0; j < TAN_DEFAULT_COLS; j++)
        {
            newf->pixels[j][i].color = (*currFrame)->pixels[j][i].color;
        }
    }
    newf->thumbnail = QImage(120, 200, QImage::Format_RGB32);
    newf->thumbnail.fill(QColor(90,90,90));

    newf->m_undo_index = (*currFrame)->m_undo_index;
    newf->m_changes = (*currFrame)->m_changes;

    //qDebug() << (currFrame-m_frames.begin());
    int temp = (currFrame-m_frames.begin());
    m_frames.insert((currFrame+1-m_frames.begin()), newf);
    currFrame = (m_frames.begin()+temp+1);
    //qDebug() << (currFrame-m_frames.begin());

    QList<TanFrame *>::iterator thing = currFrame;
    while (thing < m_frames.end()) {
        (*thing)->frame_start += newf->frame_length;
        thing++;
    }
}

void TanFile::removeCurrentFrame()
{
    if ((currFrame-m_frames.begin()) == (m_frames.end()-1-m_frames.begin())) // deleting the last frame
    {qDebug() << "Y";
         m_frames.removeAt(currFrame-m_frames.begin());
         currFrame = (m_frames.end()-1);
    }
    else // not deleting the last frame
    {qDebug() << "N";
         m_frames.removeAt(currFrame-m_frames.begin());
    }
}

void TanFile::setFileName(QString input)    //set TAN filename
{
		m_filename_tan = input;
}

QString TanFile::getFileName()		//get TAN filename
{
		return m_filename_tan;
}


void TanFile::setAudioFile(QString input)   //set audio file name
{
		m_filename_wav=input;
}

QString TanFile::getAudioFile()		//get audio file name
{
		return m_filename_wav;
}


void TanFile::setLeftColor(int r, int g, int b)   //set left-click color
{
		int alpha = 255;

		if ((r>=0) && (r<=255) &&
				(g>=0) && (g<=255) &&
				(b>=0) && (b<=255))				//error checking on rgb values
		{
                m_color_left = QColor(r,g,b,alpha);
		}
		else
		{
				QMessageBox::information(0,"error","preset rgb colors are not within range (0-255)");
		}
}

void TanFile::setLeftColor(QColor in)   //set left-click color
{
    m_color_left = in;
}

QColor TanFile::getLeftColor()		//get left-click color
{
		return m_color_left;
}


void TanFile::setRightColor(int r, int g, int b)   //set right-click color
{
		int alpha = 255;

		if ((r>=0) && (r<=255) &&
				(g>=0) && (g<=255) &&
				(b>=0) && (b<=255))				//error checking on rgb values
		{
                m_color_right = QColor(r,g,b,alpha);
		}
		else
		{
				QMessageBox::information(0,"error","preset rgb colors are not within range (0-255)");
		}
}

void TanFile::setRightColor(QColor in)   //set left-click color
{
    m_color_right = in;
}

QColor TanFile::getRightColor()		//get right-click color
{
		return m_color_right;
}


void TanFile::setPresetColor(int presetRGB[])  //set preset colors and right-click color
{
        //int alpha = 255;

		setRightColor(presetRGB[0],presetRGB[1],presetRGB[2]);

		for (int i=0;i<TAN_DEFAULT_COLORPRESETS;i++)
		{
				//error checking on rgb values
				if ((presetRGB[i*3]>=0) && (presetRGB[i*3]<=255) &&
						(presetRGB[(i*3)+1]>=0) && (presetRGB[(i*3)+1]<=255) &&
						(presetRGB[(i*3)+2]>=0) && (presetRGB[(i*3)+2]<=255))
				{
						m_color_preset[i].fromRgb(presetRGB[i*3],presetRGB[(i*3)+1],presetRGB[(i*3)+2],255);
				}
				else
				{
						QMessageBox::information(0,"error","preset rgb colors are not within range (0-255)");
						return;
				}
		}
}

QColor TanFile::getPresetColor(int index)
{
		if(index >= 0 && index < TAN_DEFAULT_COLORPRESETS)
		{
				return m_color_preset[index];
		}
		else
		{
				return QColor(Qt::black);
		}
}

void TanFile::storeFrameColor(int row, int col, QColor m_color){
    //Takes updated color and stores in project
    (*currFrame)->pixels[col][row].color = m_color;


    //Test to ensure correct color
    //qInfo("Print to console rgb values");
    //qInfo("%d",m_color.red());
    //qInfo("%d",m_color.green());
    //qInfo("%d",m_color.blue());

}
