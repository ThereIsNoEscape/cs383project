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
	// Set initial styles
	QString qss = QString("margin: 0px; border: 2px solid rgb(192,192,192); border-radius: 4px;");
	setStyleSheet(qss);
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

// Custom event handler
bool CellWidget::event(QEvent *event)
{
	// Can be deleted once actually connected to TanCells
	QColor testColor1 = Qt::red;
	QColor testColor2 = Qt::blue;
	QColor baseColor = Qt::black;

	if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent *qme = static_cast<QMouseEvent*>(event);
		// Handle left-click here
		if (qme->button() == Qt::LeftButton)
		{
			// Get color from left-click colorbox and pass to changeColor()
			// Get reference to left-click colorbox
			// Pass value to changeColor()
			QColor thisColor;
			if (_state) {
				thisColor = testColor1;
				_state = false;
			}
			else {
				thisColor = testColor2;
				_state = true;
			}
			changeColor(thisColor);
			return true;
		}
		// Handle right-click here
		else if (qme->button() == Qt::RightButton)
		{
			// Get color from right-click colorbox and pass to changeColor()
			// Get reference to right-click colorbox
			// Pass value to changeColor()
			changeColor(baseColor);
			_state = false;
			return true;
		}
	}

	// Pass all other events down to the base class
	return QWidget::event(event);
}


// Reimplementing base widget paintEvent in order for the stylesheet to work
void CellWidget::paintEvent(QPaintEvent *event)
{
		QStyleOption opt;
		opt.initFrom(this);
		QPainter p(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
