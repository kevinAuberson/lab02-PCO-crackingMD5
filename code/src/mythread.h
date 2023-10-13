#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <pcosynchro/pcothread.h>
#include <QString>
#include <QCryptographicHash>
#include <QVector>
#include <iostream>

void workThread(int threadID, unsigned int nbThreads, long long unsigned int nbComputed, long long unsigned int nbToCompute, QString hash, QString salt, QVector<unsigned int> currentPasswordArray, QString currentPasswordString, unsigned int nbValidChars, QString charset, unsigned int nbChars, QString result);

#endif // MYTHREAD_H
