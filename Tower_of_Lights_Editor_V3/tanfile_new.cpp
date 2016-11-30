#include "tanfile.h"

TanFile::TanFile() {
    m_filename_tan = "";
	m_filename_wav = "NoAudioFile";
	m_color_left = QColor(255,0,0);
	m_color_right = QColor(169,169,169);
	m_color_preset[0] = QColor(169,169,169);
	m_color_preset[1] = QColor(128,128,0);
	m_color_preset[2] = QColor(139,0,139);
	m_color_preset[3] = QColor(0,139,139);
	m_color_preset[4] = QColor(0,0,139);
	m_color_preset[5] = QColor(0,100,0);
	m_color_preset[6] = QColor(139,0,0);
	m_color_preset[7] = QColor(0,0,0);
	m_color_preset[8] = QColor(128,128,128);
	m_color_preset[9] = QColor(255,255,0);
	m_color_preset[10] = QColor(255,0,255);
	m_color_preset[11] = QColor(0,255,255);
	m_color_preset[12] = QColor(0,0,255);
	m_color_preset[13] = QColor(0,128,0);
	m_color_preset[14] = QColor(255,0,0);
	m_color_preset[15] = QColor(255,255,255);
    currFrame = 0;      //sets the iterator to the first frame
    m_frames = QLinkedList<TanFrame>();
    //make blank frame
    //append the frame to the linked list
    TanFrame newf;
    newf.frame_length = 0;
    newf.frame_start = 0;
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            newf.pixels[j][i].color.setRgb(0,0,0,255);
        }
    }
    m_frames.append(newf);
}
