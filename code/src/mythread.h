#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <pcosynchro/pcothread.h>
#include <QVector>

class MyThread{
private:
    int nbThreads;
    QVector<PcoThread*> threads;
public:
    MyThread(int nbThreads);
    void workThread(int threadID);
};

#endif // MYTHREAD_H
