// Class for a custom cell display widget

#ifndef CELL_H
#define CELL_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QString>
#include <QColor>
#include <QMouseEvent>
#include <QPushButton>
#include "TanFile.h"

class CellWidget : public QWidget {

    Q_OBJECT

public:
    CellWidget(QString name, int x, int y, QColor color = QColor(Qt::black), QWidget *parent=Q_NULLPTR);
	~CellWidget();

    int getRow();
    int getColumn();

	QColor setColor(QColor rgb);
	QColor changeColor(QColor rgb);
	QColor getColor();

	bool getState();

signals:

    //void colorChanged(const int row, const int col, QColor color);
    void rightClick(const int row,const int col,QColor color); //right click
    void leftClick(const int row,const int col,QColor color);  //left click

	void clicked(const int row, const int col);

	void selected(const int row, const int col);

private slots:

protected:

    bool event(QEvent *event);

    void paintEvent(QPaintEvent *event);

private:

	const int _row;
	const int _col;

	QColor _color;

	bool _state;

};

class Thumbnail : public QPushButton {

    Q_OBJECT

public:
    Thumbnail(TanFrame*);
    ~Thumbnail();
signals:
    void clicked(TanFrame*);
protected:
    bool event(QEvent *event);
private:
    TanFrame* framePtr;
};

#endif // CELL_H
