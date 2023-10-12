#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <pcosynchro/pcothread.h>
#include <QString>
#include <QCryptographicHash>
#include <QVector>
#include <iostream>

QString workThread(int threadID, unsigned int nbThreads, long long unsigned int nbComputed, long long unsigned int nbToCompute, QCryptographicHash* md5, QString hash, QString salt, QVector<unsigned int> currentPasswordArray, QString currentPasswordString, unsigned int nbValidChars, QString charset, unsigned int nbChars);

#endif // MYTHREAD_H
