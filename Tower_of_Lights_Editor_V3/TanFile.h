#ifndef TAN_FILE_H_
#define TAN_FILE_H_

#include <QColor>
#include <QString>
#include <QLinkedList>
#include <QTime>

// Tower Frame
struct TanFrame {
    QColor pixel[12][20]; // [x][y] ; tower : x=4..7,y=5..14
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
    QColor m_color_preset[16];               //the 16 preset colors
    QLinkedList<struct TanFrame *> m_frames; //Frame linked list
    // m_frame_count = m_frames.size();      // CONSTANT! DO NOT NEED TO STORE
    QColor m_color_right;                    // not saved in file
public:
    TanFile(); // New
    QString getFileName();
    QString getAudioName();
    QColor getCurrRGB();
    QColor getPresetRGB(int index);

    void Save();
    void SaveAs(const QString& p_filename);
};

#endif

