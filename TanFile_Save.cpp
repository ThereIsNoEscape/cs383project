#include "TanFile.h"
#include <QFile>
//#include <QTextStream>

void TanFile::Save() {
    SaveAs(m_filename_tan);
}

void TanFile::SaveAs() {
	QString filename;
    //TODO save file dialog
	SaveAs(filename);
}

void TanFile::SaveAs(const QString& p_filename) {
	QFile real_file(p_filename);

    if (real_file.open(QIODevice::WriteOnly)) {
		QTextStream file(&real_file);

		// Version
		file << "0.4\r\n";

		// Audio File
        if (m_filename_wav.isEmpty()) {
			file << "NoAudioFile\r\n";
		} else {
			file << m_filename_wav << "\r\n";
		}

		// Current Color
        file << m_filename_curr.red() << " ";
        file << m_filename_curr.green() << " ";
        file << m_filename_curr.blue() << "\r\n";

		// Palette
		for (int i = 0; i < 15; i++) {
            file << m_filename_preset[i].red() << " ";
            file << m_filename_preset[i].green() << " ";
            file << m_filename_preset[i].blue() << " ";
		}
        file << m_filename_preset[15].red() << " ";
        file << m_filename_preset[15].green() << " ";
        file << m_filename_preset[15].blue() << "\r\n";

		// Stuff
		file << m_frames.size() << " 10 4\r\n";

		// Frames
		for (int i = 0; i < m_frames.size(); i++) {
			// TODO
			// frame ms
			// frame pixels
		}

		real_file.close();
	} else {
		// TODO error
	}
}
