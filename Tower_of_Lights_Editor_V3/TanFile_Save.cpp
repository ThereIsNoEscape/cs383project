#include "tanfile.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>

bool TanFile::Save() {
    if (m_filename_tan.isEmpty())
        return SaveAs();
    else return SaveAs(m_filename_tan);
}

bool TanFile::SaveAs() {

    QFileDialog dialog;

    //QWidget sets location of popup box (I think)
    //Then getSaveFileName, as expected, gets the name of the file to save to
    QWidget * parent = 0;
    QString fileName = QFileDialog::getSaveFileName(parent,
        QObject::tr("Save Tower Animation File"), "",
        QObject::tr("Tower Animation (*.tan2);;All Files (*)"));
    //qDebug() << fileName;
    /*
    if (fileName.mid((fileName.length()-5),5).compare(QString(".tan2")))
    {
        if (fileName.mid((fileName.length()-4),4).compare(QString(".tan"))) fileName.append(".tan2");
        else fileName.append("2");
    }*/
    return SaveAs(fileName);

}

bool TanFile::SaveAs(const QString& p_filename) {
    QFile real_file(p_filename);

    if (real_file.open(QIODevice::WriteOnly)) {
        QTextStream file(&real_file);

        // Version
        file << "0.4\r\n";

        // Audio File
        if (m_filename_wav.isEmpty()) {
            file << "NoAudioFile\r\n";
        } else {
            file << m_filename_wav << "\r\n";
        }

        // Current Color
        file << m_color_left.red() << " ";
        file << m_color_left.green() << " ";
        file << m_color_left.blue() << "\r\n";

        file << m_color_right.red() << " ";
        file << m_color_right.green() << " ";
        file << m_color_right.blue() << " ";

        // Palette
        for (int i = 1; i < TAN_DEFAULT_COLORPRESETS-1; i++) {
            file << m_color_preset[i].red() << " ";
            file << m_color_preset[i].green() << " ";
            file << m_color_preset[i].blue() << " ";
        }
        file << m_color_preset[TAN_DEFAULT_COLORPRESETS-1].red() << " ";
        file << m_color_preset[TAN_DEFAULT_COLORPRESETS-1].green() << " ";
        file << m_color_preset[TAN_DEFAULT_COLORPRESETS-1].blue() << "\r\n";

        //Checking if the last frame is blank
        QColor check(0,0,0,255);    //black test color
        int flag=0; //if set, append a blank frame

        for (int y = 0; y < TAN_DEFAULT_ROWS; y++) {
            for (int x = 0; x < TAN_DEFAULT_COLS-1; x++) {
                if ((*(m_frames.end()-1))->pixels[x][y]!=check) {   //check if pixels are black
                    flag=1;
                    y = TAN_DEFAULT_ROWS;   //end checking
                    x = TAN_DEFAULT_COLS;   //
                }
            }
            if ((*(m_frames.end()-1))->pixels[TAN_DEFAULT_COLS-1][y]!=check)   //check the last pixel
                flag=1;
        }

        //if a single blank frame project, DO NOT write a blank to the file
        if (m_frames.size()<=1)
            flag=0;

        //if a blank file needs to be added, write the correct number of frames to file
        if (flag==1)
            file << m_frames.size()+1 << " 10 4\r\n";
        else
            file << m_frames.size() << " 10 4\r\n";

        // Frames
        for (int i = 0; i < m_frames.size(); i++) {
            file << (*(m_frames.begin()+i))->frame_start << "\r\n";
            for (int y = 0; y < TAN_DEFAULT_ROWS; y++) {
                for (int x = 0; x < TAN_DEFAULT_COLS-1; x++) {
                    file << (*(m_frames.begin()+i))->pixels[x][y].red() << " ";
                    file << (*(m_frames.begin()+i))->pixels[x][y].green() << " ";
                    file << (*(m_frames.begin()+i))->pixels[x][y].blue() << " ";
                }
                file << (*(m_frames.begin()+i))->pixels[TAN_DEFAULT_COLS-1][y].red() << " ";
                file << (*(m_frames.begin()+i))->pixels[TAN_DEFAULT_COLS-1][y].green() << " ";
                file << (*(m_frames.begin()+i))->pixels[TAN_DEFAULT_COLS-1][y].blue() << "\r\n";
            }
        }

        //save a blank frame if necessary
        if (flag)
        {
            //write the start time of the blank frame
            file << (*(m_frames.end()-1))->frame_start + (*(m_frames.end()-1))->frame_length << "\r\n";
            //qDebug() << (*(m_frames.end()))->frame_start << (*(m_frames.end()))->frame_length;

            //write the blank frame RGB values
            for (int y = 0; y < TAN_DEFAULT_ROWS; y++) {
                for (int x = 0; x < TAN_DEFAULT_COLS-1; x++)
                    file << 0 << " "<< 0 << " "<< 0 << " ";
                file << 0 << " "<< 0 << " "<< 0 << "\r\n";
            }
        }

        real_file.close();
        m_filename_tan = p_filename;//in case user saved as new filename, update current filename
        return true;
    } else {
        return false;
        // TODO error
    }
}
