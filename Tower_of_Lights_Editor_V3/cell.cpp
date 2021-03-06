// Class for a custom cell display widget
#include "cell.h"

// Constructor
CellWidget::CellWidget(QString name, int y, int x, QColor color, QWidget *parent)
    :	QWidget(parent),
        _row(y),
        _col(x),
        _state(false)
{
    setObjectName(name);
    // Set initial styles
    doubleclicked = false;
    QString qss;
    if (x < 8 && x > 3 && y < 15 && y > 4) qss= QString("margin: 0px; border: 2px solid rgb(127,127,127); border-radius: 4px;");
    else qss= QString("margin: 0px; border: 2px solid rgb(0,0,0); border-radius: 4px;");
    setStyleSheet(qss);
    setColor(color);

    if (_row < 0 || _col < 0)
    {
        setObjectName(QString("cellInvalid%1%2").arg(y,x));
    }
}


// Destructor
CellWidget::~CellWidget()
{

}


// Return this widget's row, corresponding with an index in TanFrame
int CellWidget::getRow()
{
    return _row;
}


// Return this widget's column, corresponding with an index in TanFrame
int CellWidget::getColumn()
{
    return _col;
}


// Sets the background color of this widget
// Returns the color that was set, for verification purposes
QColor CellWidget::setColor(QColor rgb)
{
    QString qss;

    if (_col < 8 && _col > 3 && _row < 15 && _row > 4) qss= QString("margin: 0px; border: 2px solid rgb(127,127,127); border-radius: 4px; background-color: ");
    else qss= QString("margin: 0px; border: 2px solid rgb(0,0,0); border-radius: 4px; background-color: ");


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

    if (event->type() == QEvent::MouseButtonPress)
    {
        delay(200);
        if (doubleclicked)
        {
            doubleclicked = false;
            return false;
        }
        QMouseEvent *qme = static_cast<QMouseEvent*>(event);
        char btn = 'X';

        // Handle left-click here
        // Left-click changes the color based on
        // the current leftColor of the Tan file representation
        if (qme->button() == Qt::LeftButton) {
            btn = 'L';
        }
        // Handle right-click here
        // Right-click changes the color based on
        // the current rightColor of the Tan file representation
        else if (qme->button() == Qt::RightButton)
        {
            btn = 'R';
        }
        emit clicked(getRow(), getColumn(), btn);
        return true;
    }
    else if (event->type() == QEvent::MouseButtonDblClick)
    {
        doubleclicked = true;
        QMouseEvent *qme = static_cast<QMouseEvent*>(event);
        char btn = 'X';

        // Handle left-click here
        // Left-click changes the color based on
        // the current leftColor of the Tan file representation
        if (qme->button() == Qt::LeftButton) {
            btn = 'L';
        }
        // Handle right-click here
        // Right-click changes the color based on
        // the current rightColor of the Tan file representation
        else if (qme->button() == Qt::RightButton)
        {
            btn = 'R';
        }
        emit doubleClicked(btn, _color);
        return true;
    }
    else
    {
        // Pass all other events down to the base class
        return QWidget::event(event);
    }
}


// Reimplementing base widget paintEvent in order for the stylesheet to work
void CellWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void CellWidget::delay(double milliseconds)
{
    QTime dieTime = QTime::currentTime().addMSecs(milliseconds);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

Thumbnail::Thumbnail(TanFrame* fin)
{
    framePtr = fin;
}

Thumbnail::~Thumbnail()
{

}

bool Thumbnail::event(QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        emit clicked((long int)framePtr);
        return true;
    }
    return QWidget::event(event);// Pass all other events down to the base class
}

interactableArea::interactableArea()
{

}

interactableArea::~interactableArea()
{

}

bool interactableArea::event(QEvent *event)
{
    if (event->type() == QEvent::MouseMove)
    {
        return true;
    }
    return QWidget::event(event);// Pass all other events down to the base class
}
