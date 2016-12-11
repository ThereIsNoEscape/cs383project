#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QDebug>
#include <QTime>
#include <QCoreApplication>

class myThread : public QThread
{
    Q_OBJECT
public:
    myThread();
    void setMilliseconds(double);
signals:
    void countdownDone();
protected:
    void run();
private:
    double milliseconds;
};

#endif // THREAD_H
