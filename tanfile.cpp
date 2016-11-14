#include "TanFile.h"
#include <QMessageBox>

QString TanFile::getFileName()
{
    return m_filename_tan;
}

void TanFile::setfilename(QString input)    //set filename
{
    m_filename_tan = input;
}

void TanFile::setleftclr(int r, int g, int b)   //set left click color
{
    m_color_left.fromRgb(r,g,b,255);
}

void TanFile::setaudiofile(QString input)   //set audiofile name
{
    m_filename_wav=input;
}

void TanFile::setpresetclr(int presetRGB[])  //set preset colors and right click color
{
    if ((presetRGB[0]<0)||(presetRGB[0]>255)||(presetRGB[1]<0)||
            (presetRGB[1]>255)||(presetRGB[2]<0)||
            (presetRGB[2]>255))                          //error checking on rgb values

    m_color_right.fromRgb(presetRGB[0],presetRGB[1],presetRGB[2],255);

    for (int i=1;i<16;i++)
    {
        if ((presetRGB[i*3]<0)||(presetRGB[i*3]>255)||(presetRGB[(i*3)+1]<0)||
                (presetRGB[(i*3)+1]>255)||(presetRGB[(i*3)+2]<0)||
                (presetRGB[(i*3)+2]>255))                          //error checking on rgb values
        {
            QMessageBox::information(0,"error","preset rgb colors are not within range (0-255)");
            return;
        }
        m_color_preset[i-1].fromRgb(presetRGB[i*3],presetRGB[(i*3)+1],presetRGB[(i*3)+2],255);
    }
}
