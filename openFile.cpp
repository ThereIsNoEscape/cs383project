#include <QString>
#include <QTextStream>  //for iostream objects
#include <QFile>        //for file manipulation
#include <QMessageBox>  //for error checking
#include "TanFile.h"    //for making a TanFile object

using namespace std;

QStringList getFileContents(QString fileName)
{
    QString buffer;
    QStringList fileContents;	//will hold the contents of the file
    QFile fp(fileName);

    if (fp.open(QIODevice::ReadOnly))	//error checking
    {
        //the file is open
        QTextStream in(&fp);
        buffer = in.readAll();  //read file into Qstring buffer
        fileContents = buffer.split(QRegExp("\n|\r"),QString::SkipEmptyParts);  //delimiti buffer into Qstring list
        fp.close();	//close the file
        return fileContents;
    }
    else
    {
        //the file could NOT be opened
        QMessageBox::information(0,"error",fp.errorString());
        return fileContents;
    }
}
