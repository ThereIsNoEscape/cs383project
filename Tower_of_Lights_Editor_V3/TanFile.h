#ifndef TAN_FILE_H_
#define TAN_FILE_H_

#include <QColor>
#include <QString>
#include <QLinkedList>
#include <QTime>
#include "config.h"

// Tower Frame
struct TanCell {
	QColor color;
	QString name;
};

struct TanFrame {
	// [x][y] ; tower : y=4..7,x=5..14
	struct TanCell cells[TAN_DEFAULT_ROWS][TAN_DEFAULT_COLS];
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
	QColor m_color_right;                    // not saved in file
	QColor m_color_preset[TAN_DEFAULT_COLORPRESETS];               //preset colors
	// m_frame_count = m_frames.size();      // CONSTANT! DO NOT NEED TO STORE

public:
	TanFile(); // New

	QLinkedList<struct TanFrame *> m_frames; //Frame linked list
	QString getFileName();
	QString getAudioName();
	QColor getLeftRGB() { return m_color_left; }
	QColor getRightRGB() { return m_color_right; }
	QColor getPresetRGB(int index) { if(index >= 0 && index < TAN_DEFAULT_COLORPRESETS) return m_color_preset[index]; else return QColor(Qt::black); }

	void Save();
	void SaveAs();
	void SaveAs(const QString& p_filename);
};

#endif
