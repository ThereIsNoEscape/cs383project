#ifndef TAN_FILE_H_
#define TAN_FILE_H_

#include <QString>
#include <QColor>       //added for pixel
#include <QLinkedList>
#include <QTime>        //for time

// Tower Frame
struct TanFrame {
    QColor pixel[12][20]; // [x][y] ; tower : x=4..7,y=5..14
    int frame_length; // >= 25ms
    QTime frame_start; //when the frame begins (ms)
};

// TAN File
class TanFile {
//private:
    // Variables
    QString m_filename_tan;                  //TAN file name
    QString m_filename_wav;                  //WAV file name
    QColor m_filename_curr;                  //the current color selected
    QColor m_filename_preset[16];            //the 16 preset colors
    QLinkedList<struct TanFrame *> m_frames; //Frame linked list
    int frame_count;                         //number of frames in file
    // Constant for all TAN files
    // version = 0.4
    // width = 4
    // height = 10
//public:
    TanFile(); // New
    QString getFileName();
    QString getAudioName();
    QColor getCurrRGB();
    QColor * getPresetRGB();    //returns pointer to QColor array
};

#endif
