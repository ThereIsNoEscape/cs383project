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

        // Palette
        for (int i = 0; i < TAN_DEFAULT_COLORPRESETS-1; i++) {
            file << m_color_preset[i].red() << " ";
            file << m_color_preset[i].green() << " ";
            file << m_color_preset[i].blue() << " ";
        }
        file << m_color_preset[TAN_DEFAULT_COLORPRESETS-1].red() << " ";
        file << m_color_preset[TAN_DEFAULT_COLORPRESETS-1].green() << " ";
        file << m_color_preset[TAN_DEFAULT_COLORPRESETS-1].blue() << "\r\n";

        // Stuff
        file << m_frames.size() << " 10 4\r\n";
        //qDebug() << (*m_frames.begin())->pixels[0][0].color.red();

        // Frames
        for (int i = 0; i < m_frames.size(); i++) {
            file << (*(m_frames.begin()+i))->frame_start << "\r\n";
            for (int y = 0; y < TAN_DEFAULT_ROWS; y++) {
                for (int x = 0; x < TAN_DEFAULT_COLS-1; x++) {
                    file << (*(m_frames.begin()+i))->pixels[x][y].color.red() << " ";
                    file << (*(m_frames.begin()+i))->pixels[x][y].color.green() << " ";
                    file << (*(m_frames.begin()+i))->pixels[x][y].color.blue() << " ";
                }
                file << (*(m_frames.begin()+i))->pixels[TAN_DEFAULT_COLS-1][y].color.red() << " ";
                file << (*(m_frames.begin()+i))->pixels[TAN_DEFAULT_COLS-1][y].color.green() << " ";
                file << (*(m_frames.begin()+i))->pixels[TAN_DEFAULT_COLS-1][y].color.blue() << "\r\n";
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
