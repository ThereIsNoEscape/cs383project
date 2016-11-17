#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>        // for testing purposes
#include <QFileDialog>   // used for selecting files
#include <QMessageBox>   // used for testing cell output, as of iteration 1
#include <QGridLayout>   // used for overall UI layout, and the frame layout
#include <QtWidgets>
#include <QString>
#include <QColor>
#include <QTime>         // for holding time
#include "tanfile.h"
#include "openfile.h"
#include "cell.h"

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

		void on_cell_colorChanged(const int row, const int col, QColor m_color);

		void on_comboBox_activated(const QString &arg1);

private:
	Ui::MainWindow *ui;

	QString m_getObjName(QObject *m_obj);

	void m_generateFrame(int rows, int cols);

	void m_destroyFrame(int rows, int cols);

	void m_connectCellSignals(CellWidget *m_cell);

	void m_updateTanFileColor(const int row, const int col, QColor m_color);

	void m_setCellColor(QString m_cellName, QColor m_color);

};

#endif // MAINWINDOW_H
