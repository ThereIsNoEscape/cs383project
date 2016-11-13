// Class for a custom cell display widget
#include "cell.h"


// Constructor
CellWidget::CellWidget(QString name, int x, int y, QColor color, QWidget *parent)
	:	QWidget(parent),
		_row(x),
		_col(y),
		_state(false)
{
	setObjectName(name);
	setColor(color);

	if (_row < 0 || _col < 0)
	{
		setObjectName(QString("cellInvalid%1%2").arg(x,y));
	}
}

// Destructor
CellWidget::~CellWidget()
{

}


// Return this widget's row, corresponding with an index in TanFrame
const int CellWidget::getRow()
{
	return _row;
}

// Return this widget's column, corresponding with an index in TanFrame
const int CellWidget::getColumn()
{
	return _col;
}

// Sets the background color of this widget
// Returns the color that was set, for verification purposes
QColor CellWidget::setColor(QColor rgb)
{
	QString qss = QString("background-color: ");

	if (!(rgb.isValid()))
	{
		rgb = Qt::black;
	}
	_color = rgb;

	qss += _color.name();
	setStyleSheet(qss);

	return getColor();
}

// Calls setColor(), and then triggers the colorChanged() signal
// Returns the color that was set, for verification purposes
QColor CellWidget::changeColor(QColor rgb)
{
	setColor(rgb);

	emit colorChanged(getRow(), getColumn(), getColor());

	return getColor();
}

// Return the current color
QColor CellWidget::getColor()
{
	return _color;
}

// Returns the current state of the widget, indicating currently selected or not
bool CellWidget::getState()
{
	return _state;
}

// Event handlers
// QMouseEvent handlers
void CellWidget::mousePressEvent(QMouseEvent *event)
{
	QColor testColor1 = Qt::yellow;
	QColor testColor2 = Qt::black;
	// Handle left-click here
	if (event->button() == Qt::LeftButton)
	{
		// Get color from left-click colorbox and pass to changeColor()
		// Get reference to left-click colorbox
		// Pass value to changeColor()
		setColor(testColor1);
	}
	// Handle right-click here
	else if (event->button() == Qt::RightButton)
	{
		// Get color from right-click colorbox and pass to changeColor()
		// Get reference to right-click colorbox
		// Pass value to changeColor()
		setColor(testColor2);
	}
	else {
			// pass on other buttons to base class
			QWidget::mousePressEvent(event);
	}
}
