#include "tanfile.h"

int TanFile::getCurrFrame()
{
    return currFrame;
}

void TanFile::setCurrFrame(int input)
{
    currFrame = input;
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
		int alpha = 255;

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
    (m_frames.begin()+currFrame)->pixels[col][row].color = m_color;


    //Test to ensure correct color
    //qInfo("Print to console rgb values");
    //qInfo("%d",m_color.red());
    //qInfo("%d",m_color.green());
    //qInfo("%d",m_color.blue());

}

