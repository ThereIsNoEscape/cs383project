#ifndef TAN_FILE_H_
#define TAN_FILE_H_

#include <QColor>
#include <QString>
#include <QLinkedList>
#include <QTime>

// Tower Frame
struct TanFrame {
    /*QColor pixel[12][20]; // [x][y] ; tower : x=4..7,y=5..14
    int duration;    // the length of time the frame will last in ms
    QTime startTime; //when the frame begins in ms*/
    QColor pixel[12][20]; // [x][y] ; tower : x=4..7,y=5..14
    int frame_length; // >= 25ms
    QTime frame_start; //when the frame begins (ms)
};

// TAN File
class TanFile {
public:
    // Variables
    /*QString fileName;   //the name of the file
    QString audioName;  //the name of the audio file
    QColor leftClick;   //the color for left click
    QColor rightClick;  //the color for right click
    QColor preset[16];  //the 16 preset colors
    QLinkedList<TanFrame*>frame;   //the frame(s)
    int frameCount;     //the number of frames*/
    QString m_filename_tan;                  //TAN file name
    QString m_filename_wav;                  //WAV file name
    QColor m_filename_curr;                  //the current color selected
    QColor m_filename_preset[16];            //the 16 preset colors
    QLinkedList<struct TanFrame *> m_frames; //Frame linked list
    int frame_count; //number of frames in file
public:
    TanFile(); // New
    QString getFileName();
    QString getAudioName();
    QColor getCurrRGB();
    QColor * getPresetRGB();    //returns pointer to QColor array

    void Save();
    void SaveAs();
    void SaveAs(const QString& p_filename);
};

#endif
