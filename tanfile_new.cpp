/*
 *  TanFile_New.cpp
 *
*/
#include <QFile>
#include <QTextStream>
#include "TanFile.h"

TanFile::TanFile()
{
    QFile new_tan_file("unedited.tan");
    if(!new_tan_file.open(QIODevice::ReadWrite))
        return;

    QTextStream out(&new_tan_file);
    out << "0.4\n";
    out << "NoAudioFile\n";
    out << "255 0 0\n";
    out << "169 169 169 128 128 0 139 0 139 0 139 139 0 0 139 0 100 0 139 0 0 0 0 0 128 128 128 255 255 0 255 0 255 0 255 255 0 0 255 0 128 0 255 0 0 255 255 255\n";
    out << "1 10 4\n";
    out << "0\n";
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 36; j++){
            if(j == 35)
                out << "0\n";
            else
                out << "0 ";
        }
    }
    new_tan_file.close();
}
