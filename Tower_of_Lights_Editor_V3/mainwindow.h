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
#include "cell.h"
#include "effect.h" //for storing effects
#include "lettereffectdialog.h"
#include "symboleffectdialog.h"
#include "shapeeffectdialog.h"
#include "preview.h"
#include "infodialog.h"

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
    TanFile* load(QString);

    void cell_clicked(const int row, const int col, const char btn);
    void cell_doubleClicked(const char btn, const QColor);

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
    void on_pushButton_changeAudioFile_clicked();
    void on_checkBox_stateChanged(int state);
    void on_pushButton_up_clicked();
    void on_pushButton_down_clicked();
    void on_pushButton_left_clicked();
    void on_pushButton_right_clicked();
    void on_pushButton_upleft_clicked();
    void on_pushButton_downright_clicked();
    void on_pushButton_downleft_clicked();
    void on_pushButton_upright_clicked();

    void on_spinBox_valueChanged(int arg1);
    void on_undo();
    void on_redo();

    void insert_letter();
    void insert_symbol();
    void insert_shape();
    void insert_from_file();

    void info();

    void spawnEffect(const effect*); //signaled from dialog
private:
	Ui::MainWindow *ui;
    bool nothingToSave;
    bool wrap;

	QString m_getObjName(QObject *m_obj);
	void m_generateFrame(int rows, int cols);
	void m_destroyFrame(int rows, int cols);
	void m_connectCellSignals(CellWidget *m_cell);
    void m_updateTanFileColor(const int row, const int col, QColor m_color);
    void updateGUIColorButtons();
    void newFrame();
    void newFrame(TanFrame*);
    void newFrameCopy();
    bool saveSequence();//returns false if the user cancels the entire process
    void createActions();
    void createMenus();
    void switchCurrentFrame(int index);
    void generateThumbnail(TanFrame* ptr);
    QImage scaleDown(QImage thumbnail);
    void clearThumbnails(); // used when opening a project or starting a new project
    void appendThumbnail(TanFrame*);
    void addThumbnail(TanFrame*, int);
    void clearSelectedThumbnail();
    Thumbnail* newThumbnail(TanFrame*);
    void on_change_color(int row, int col, const QColor& p_color);
    void on_change_color(QList<int>, QList<int>, QList<QColor>, int);
    void on_change_frame();
    void on_change_file();
    void move(int);

    QMenu *fileMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *quitAct;

    QMenu *editMenu;
    QAction *undoAct;
    QAction *redoAct;

    QMenu *insertMenu;
    QAction *letterAct;
    QAction *symbolAct;
    QAction *shapeAct;
    QAction *fromFileAct;

    QMenu *helpMenu;
    QAction *infoAct;
};

#endif // MAINWINDOW_H
