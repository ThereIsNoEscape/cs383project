#ifndef OPENFILE_H
#define OPENFILE_H

#include <QString>
#include <QTextStream>  //for iostream objects
#include <QFile>        //for file manipulation
#include <QMessageBox>  //for error checking
#include "TanFile.h"    //for making a TanFile object

using namespace std;

QStringList getFileContents(QString fileName);

#endif // OPENFILE_H
