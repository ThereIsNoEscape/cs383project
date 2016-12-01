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
#include <QLinkedList>
#include "tanfile.h"
#include "config.h"
#include "openfile.h"
#include "cell.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

struct Change {
    QString cell_name;
    QColor  old_color;
    QColor  new_color;
};

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


    void on_spinBox_valueChanged(int arg1);

    void on_undo();
    void on_redo();

private:
	Ui::MainWindow *ui;
    bool nothingToSave;

	QString m_getObjName(QObject *m_obj);

	void m_generateFrame(int rows, int cols);

	void m_destroyFrame(int rows, int cols);

	void m_connectCellSignals(CellWidget *m_cell);

    void m_updateTanFileColor(const int row, const int col, QColor m_color);

    void m_setCellColor(CellWidget *, QColor color);

    void updateGUIColorButtons();

    bool saveSequence();//returns false if the user cancels the entire process

    void createActions();
    void createMenus();

    void on_change_color(const QString& p_cell_name, const QColor& p_color);
    void on_change_frame();

    QMenu *fileMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *quitAct;

    QMenu *editMenu;
    QAction *undoAct;
    QAction *redoAct;

    int m_undo_index = 0;
    QLinkedList<struct Change *> m_changes;
};

#endif // MAINWINDOW_H
