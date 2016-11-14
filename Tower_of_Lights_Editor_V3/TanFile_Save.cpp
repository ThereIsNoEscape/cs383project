#include "tanfile.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

void TanFile::Save() {
    SaveAs(m_filename_tan);
}

void TanFile::SaveAs() {
/*
		QStringList fileNames;
    QFileDialog dialog();
		dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("*.tan*;;All Files (*)"));
    dialog.setViewMode(QFileDialog::Detail);
    if(dialog.exec()){
        fileNames = dialog.selectedFiles();
    }
	SaveAs(fileNames[0]);
*/
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
				file << m_color_left.red() << " ";
				file << m_color_left.green() << " ";
				file << m_color_left.blue() << "\r\n";

		// Palette
		for (int i = 0; i < TAN_DEFAULT_COLORPRESETS-1; i++) {
						file << m_color_preset[i].red() << " ";
						file << m_color_preset[i].green() << " ";
						file << m_color_preset[i].blue() << " ";
		}
		file << m_color_preset[TAN_DEFAULT_COLORPRESETS-1].red() << " ";
		file << m_color_preset[TAN_DEFAULT_COLORPRESETS-1].green() << " ";
		file << m_color_preset[TAN_DEFAULT_COLORPRESETS-1].blue() << "\r\n";

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
