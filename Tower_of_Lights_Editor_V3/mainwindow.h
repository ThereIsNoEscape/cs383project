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
    int x;
    int y;
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

    void cell_clicked(const int row, const int col, const char btn);

    void on_pushButton_prev_clicked();
    void on_pushButton_next_clicked();
    void on_pushButton_l_clicked();
    void on_pushButton_r_clicked();
    void on_pushButton_new_clicked();
    void on_pushButton_copyNew_clicked();
    void on_pushButton_undo_clicked();
    void on_pushButton_redo_clicked();
    void on_pushButton_preview_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_clearFrame_clicked();
    void thumbnail_clicked(const long int);

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
    void updateGUIColorButtons();
    void newFrame();
    void newFrameCopy();
    bool saveSequence();//returns false if the user cancels the entire process
    void createActions();
    void createMenus();
    void switchCurrentFrame(int index);
    void generateThumbnailCurrent();
    void generateThumbnail(TanFrame* ptr);
    QImage scaleDown(QImage thumbnail);
    void clearThumbnails(); // used when opening a project or starting a new project
    void addThumbnail(); // only used when starting a new project;
    void addThumbnailToEnd(QImage in, TanFrame*);
    void switchSelectedThumbnail(int index);
    void addCurrentThumbnail();
    Thumbnail* newThumbnail(QImage in, TanFrame*);
    Thumbnail* newThumbnail(QString in, TanFrame*);
    void on_change_color(int x, int y, const QColor& p_color);
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
