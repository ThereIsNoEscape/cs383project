#ifndef TANFILE_H
#define TANFILE_H

#include <QLinkedList>
#include <QString>
#include <QColor>
#include <QMessageBox>
#include "config.h"
#include <QDebug>        // for testing purposes

struct Change {
    int col;
    int row;
    QColor  old_color;
    QColor  new_color;
};

struct TanFrame {
    // [x][y] ; tower : x=4..7,y=5..14
    QColor pixels[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS];
    int frame_length; // >= 25ms
    int frame_start; // in ms
    QImage thumbnail;

    int m_undo_index;
    QLinkedList<struct Change *> m_changes;
};

// TAN File
class TanFile {
private:
    QString m_filename_tan;                          // TAN file name
    QString m_filename_wav;                          // WAV file name
    QColor m_color_left;                             // the current color selected
    QColor m_color_right;                            // not saved in file; pulled from the 1st preset color
    QColor m_color_preset[TAN_DEFAULT_COLORPRESETS]; // preset colors

    // m_frame_count = m_frames.size();              // CONSTANT! DO NOT NEED TO STORE

public:
    TanFile(); // New
    TanFile(QString filename); // New from file
    TanFile(TanFile* tfile); // Copy constructor

    QList<TanFrame*>::iterator currFrame;       // holds current position in list of frames

    void newFrame(); //creates a new frame after the current one
    void newFrameCopy(); //creates a new frame copying the current one
    void removeCurrentFrame();

    QList<TanFrame*> m_frames; //Frame linked list
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

    void setPresetColor(int []);
    QColor getPresetColor(int index);

    void storeFrameColor(int row, int col, QColor m_Color);

    bool Save();
    bool SaveAs();
    bool SaveAs(const QString &p_filename);
};

#endif // TANFILE_H
