/*
 *  mainwindow.cpp
 *
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TanFile.h"
#include <QString>
#include <QDebug>   //for testing purposes
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply;

    /* Create Message Box
     * Title of message box : "Tower Lights"
     * Prompt message : "Would you like to save?"
     * 3 button choices : "Save", "No", "Cancel"
    */

    reply = QMessageBox::question(this, "Tower Lights", "Would you like to save?",
                                  QMessageBox::Save|QMessageBox::No|QMessageBox::Cancel);


    if(reply == QMessageBox::Save){
        TanFile newFile;
        if(QString(newFile.getFileName()).isEmpty()){ // check if there is a file name
            //SaveAs();
            qDebug() << "SaveAs\n";
        }else{
            //Save();
            qDebug() << "Save\n";
        }
    }else if(reply == QMessageBox::No){
        TanFile newFile; //creates new blank .tan file
        //do we delete a .tan file if it was never saved in the first place?
    }else if(reply == QMessageBox::Cancel){
        //do nothing
    }
}
