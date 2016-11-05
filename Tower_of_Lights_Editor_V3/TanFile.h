#ifndef TAN_FILE_H_
#define TAN_FILE_H_

#include <QString>
#include <QLinkedList>

// Pixel
union RGB {
    struct {
        unsigned char b, g, r;
    };
    int	rgb;
};

// Tower Frame
struct TanFrame {
    union RGB pixel[12][20]; // [x][y] ; tower : x=4..7,y=5..14
    int frame_length; // >= 25ms
};

// TAN File
class TanFile {
private:
    // Variables
    QString m_filename_tan; // TAN file name
    QString m_filename_wav; // WAV file name
    QLinkedList<struct TanFrame *> m_frames; // Frame list
    // Constant for all TAN files
    // version = 0.4
    // width = 4
    // height = 10
    // frame_count = m_frames.size();
public:
    TanFile(); // New
    TanFile(const QString& p_filename); // Open
    void Save() { SaveAs(m_filename_tan); } // Save
    void SaveAs(const QString& p_filename); // Save As
    struct TanFrame *GetFrame(int ms); // return TanFrame displayed at time=ms
};

#endif
