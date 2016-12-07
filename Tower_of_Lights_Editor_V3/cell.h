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
#include <QScrollArea>
#include <QTime>
#include <QCoreApplication>
#include "tanfile.h"

class CellWidget : public QWidget {

    Q_OBJECT

public:
    CellWidget(QString name, int y, int x , QColor color = QColor(Qt::black), QWidget *parent=Q_NULLPTR);
	~CellWidget();

    int getRow();
    int getColumn();

	QColor setColor(QColor rgb);
	QColor changeColor(QColor rgb);
	QColor getColor();

	bool getState();

signals:

    void colorChanged(const int row, const int col, QColor color);

    void clicked(const int row, const int col, const char btn);

    void doubleClicked(const char btn, const QColor);

	void selected(const int row, const int col);

private slots:

protected:

    bool event(QEvent *event);

    void paintEvent(QPaintEvent *event);

private:

	const int _row;
	const int _col;

    bool doubleclicked;

	QColor _color;

	bool _state;

    void delay(double time);
};

class Thumbnail : public QPushButton {
    Q_OBJECT
public:
    Thumbnail(TanFrame*);
    ~Thumbnail();
signals:
    void clicked(const long int);
protected:
    bool event(QEvent *event);
private:
    TanFrame* framePtr;
};

class interactableArea : public QScrollArea {
    Q_OBJECT
public:
    interactableArea();
    ~interactableArea();
signals:
    void clicked(const long int);
protected:
    bool event(QEvent *event);
private:
};

#endif // CELL_H
