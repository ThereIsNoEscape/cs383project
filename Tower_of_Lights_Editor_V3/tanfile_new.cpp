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
    m_frames = QList<TanFrame*>();
    //make blank frame
    TanFrame* newf = new TanFrame();
    newf->frame_length = 0;
    newf->frame_start = 0;
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            newf->pixels[j][i].color.setRgb(0,0,0,255);
        }
    }
    newf->thumbnail = QImage(120, 200, QImage::Format_RGB32);
    newf->thumbnail.fill(QColor(90,90,90));
    m_frames.append(newf); //append the frame to the linked list
    currFrame = m_frames.begin();      //sets the iterator to the first frame
}

TanFile::TanFile(QString filename) {
    m_filename_tan = filename;
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
    m_frames = QList<TanFrame*>();
}

TanFile::TanFile(TanFile* tfile) {
    m_filename_tan = tfile->m_filename_tan;
    m_filename_wav = tfile->m_filename_wav;
    m_color_left = tfile->m_color_left;
    m_color_right = tfile->m_color_right;
    m_color_preset[0] = tfile->m_color_preset[0];
    m_color_preset[1] = tfile->m_color_preset[1];
    m_color_preset[2] = tfile->m_color_preset[2];
    m_color_preset[3] = tfile->m_color_preset[3];
    m_color_preset[4] = tfile->m_color_preset[4];
    m_color_preset[5] = tfile->m_color_preset[5];
    m_color_preset[6] = tfile->m_color_preset[6];
    m_color_preset[7] = tfile->m_color_preset[7];
    m_color_preset[8] = tfile->m_color_preset[8];
    m_color_preset[9] = tfile->m_color_preset[9];
    m_color_preset[10] = tfile->m_color_preset[10];
    m_color_preset[11] = tfile->m_color_preset[11];
    m_color_preset[12] = tfile->m_color_preset[12];
    m_color_preset[13] = tfile->m_color_preset[13];
    m_color_preset[14] = tfile->m_color_preset[14];
    m_color_preset[15] = tfile->m_color_preset[15];
    m_frames = tfile->m_frames;
    currFrame = m_frames.begin();      //sets the iterator to the first frame
}
