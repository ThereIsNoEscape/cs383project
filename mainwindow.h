#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>   // used for overall UI layout, and the frame layout
#include <QPushButton>   // used for the cells of the frame, as of iteration 1
#include <QFileDialog>   // used for selecting files
#include <QMessageBox>   // used for testing cell output, as of iteration 1
#include <QString>
#include <QDebug>        // for testing purposes
#include <QColor>
#include <QTime>         // for holding time
#include "TanFile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    TanFile project;   //the object that MainWindow will use for data storage
    ~MainWindow();

private slots:

    void openFile();

    void newFile();

    void on_cell_clicked();

    void on_comboBox_activated(const QString &arg1);

private:
	Ui::MainWindow *ui;

	QString m_getObjName(QObject *m_cell);

	void m_connectCellButtons(int cellCt);

	void m_changeCellColor(QString m_cellName);

	void m_alertCoords(QString m_cellName);
};

#endif // MAINWINDOW_H
