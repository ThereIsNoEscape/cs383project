#ifndef TANFILE_H
#define TANFILE_H

#include <QLinkedList>
#include <QString>
#include <QColor>
#include <QMessageBox>
#include "config.h"

// Tower Frame
struct TanCell {
    QColor color;
    QString name;
};

struct TanFrame {
    // [x][y] ; tower : x=4..7,y=5..14
    struct TanCell pixels[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS];
    int frame_length; // >= 25ms
    int frame_start; // in ms
};

// TAN File
class TanFile {
private:
    QString m_filename_tan;                          // TAN file name
    QString m_filename_wav;                          // WAV file name
    QColor m_color_left;                             // the current color selected
    QColor m_color_right;                            // not saved in file; pulled from the 1st preset color
    QColor m_color_preset[TAN_DEFAULT_COLORPRESETS]; // preset colors
    int currFrame;                                   // holds current position in list of frames

    // m_frame_count = m_frames.size();              // CONSTANT! DO NOT NEED TO STORE

public:
    TanFile(); // New

    int getCurrFrame();
    void setCurrFrame(int);

    QLinkedList<TanFrame> m_frames; //Frame linked list
    void setFileName(QString);
    QString getFileName();

    void setAudioFile(QString);
    QString getAudioFile();

    void setLeftColor(int,int,int);
    void setLeftColor(QColor);
    QColor getLeftColor();

    void setRightColor(int,int,int);
    void setRightColor(QColor);
    QColor getRightColor();

    void storeFrameColor(int row, int col, QColor m_color);

    void setPresetColor(int []);
    QColor getPresetColor(int index);

    bool Save();
    bool SaveAs();
    bool SaveAs(const QString &p_filename);
};

#endif // TANFILE_H
