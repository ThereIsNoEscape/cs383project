#ifndef TAN_FILE_H_
#define TAN_FILE_H_

#include <QColor>
#include <QString>
#include <QLinkedList>

// Frame Cell
struct Cell
{
   QColor color;    //the color of a cell
   QString name;    //the name of the button associated
};

// Tower Frame
struct TanFrame {
    Cell pixels[12][20]; // [x][y] ; tower : x=4..7,y=5..14
    int frame_length; // >= 25ms
    int frame_start; // in ms
};

// TAN File
class TanFile {
private:
    // Variables
    QString m_filename_tan;                  //TAN file name
    QString m_filename_wav;                  //WAV file name
    QColor m_color_left;                     //the current color selected
    QColor m_color_right;                    //saved as the 1st preset color
    QColor m_color_preset[15];               //the 15 preset colors
    // m_frame_count = m_frames.size();      //CONSTANT! DO NOT NEED TO STORE

public:
    QLinkedList<TanFrame> m_frames; //Frame linked list

    //set functions
    TanFile(); // New
    void setfilename(QString);
    void setaudiofile(QString);
    void setleftclr(int,int,int);
    void setpresetclr(int []);
    //get functions
    QString getFileName();
    QString getAudioName();
    QColor getCurrRGB();
    QColor getPresetRGB(int index);

    void Save();
    void SaveAs();
    void SaveAs(const QString& p_filename);
};

#endif

