#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <pcosynchro/pcothread.h>
#include <QString>
#include<QObject>
#include <QCryptographicHash>
#include <QVector>

class MyThread{
    friend void workThread(int threadID);
private:
    static unsigned int i;
    long long unsigned int nbToCompute;
    static long long unsigned int nbComputed;
    unsigned int nbChars;
    unsigned int nbValidChars;
    QString currentPasswordString;
    QVector<unsigned int> currentPasswordArray;
    QString hash;
    QString currentHash;
    int nbThreads;
    QVector<PcoThread*> threads;
    QCryptographicHash *md5;
public:
    MyThread(long long unsigned int nbToCompute, unsigned int nbChars, const std::string& charset, const int numThreads, const std::string& salt, const std::string& hash);
    void startThreads();
};

#endif // MYTHREAD_H
