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
#include "config.h"
#include "openfile.h"
#include "cell.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

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
    void save();
    void saveAs();

    //void on_cell_colorChanged(const int row, const int col, QColor m_color);
    void on_cell_leftChanged(const int row, const int col, QColor m_color);
    void on_cell_rightChanged(const int row, const int col, QColor m_color);

    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
	Ui::MainWindow *ui;

	QString m_getObjName(QObject *m_obj);

	void m_generateFrame(int rows, int cols);

	void m_destroyFrame(int rows, int cols);

	void m_connectCellSignals(CellWidget *m_cell);

    void m_updateTanFileColor(const int row, const int col, QColor m_color);

    void m_setCellColor(CellWidget *, QColor color);

    void updateGUIColorButtons();

    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *quitAct;
};

#endif // MAINWINDOW_H
