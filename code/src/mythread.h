#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <pcosynchro/pcothread.h>
#include <QVector>
#include <QCryptographicHash>
#include <pcosynchro/pcomutex.h>

class MyThread{
private:
    PcoMutex mutex;
    int nbThreads;
    QVector<PcoThread*> threads;
    long long unsigned int nbToCompute;
    long long unsigned int nbComputed;
    unsigned int nbValidChars;
    unsigned int nbChars;
    QString currentPasswordString;
    QVector<unsigned int> currentPasswordArray;
    QString hash;
    QString salt;
    QString charset;
    QCryptographicHash *md5;
public:
    MyThread(unsigned int nbThread, unsigned int nbToCompute, unsigned int nbChars, const QString& salt, const QString& hash, const QString& charset);
    void startThread();
    QString hashing();
    QString workThread(int threadID);
};

#endif // MYTHREAD_H
