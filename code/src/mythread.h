#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <pcosynchro/pcothread.h>
#include <QVector>
#include <QCryptographicHash>

class MyThread{
private:
    int nbThreads;
    QVector<PcoThread*> threads;
    unsigned int i;
    long long unsigned int nbToCompute;
    long long unsigned int nbComputed;
    unsigned int nbValidChars;
    QString currentPasswordString;
    QVector<unsigned int> currentPasswordArray;
    QString currentHash;
    QString hash;
    QString salt;
    QString charset;
    QCryptographicHash *md5;
public:
    MyThread(unsigned int nbThread, unsigned int nbToCompute, unsigned int nbChars, const QString& salt, const QString& hash, const QString& charset, int nbValidChars);
    void startThread();
    QString hashing();
    void workThread(int threadID);
};

#endif // MYTHREAD_H
