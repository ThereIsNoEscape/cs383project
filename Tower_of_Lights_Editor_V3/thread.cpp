#include "thread.h"

myThread::myThread()
{

}

void myThread::setMilliseconds(double d)
{
    milliseconds = d;
}

void myThread::run()
{
    QTime dieTime = QTime::currentTime().addMSecs(milliseconds);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    emit countdownDone();
}
