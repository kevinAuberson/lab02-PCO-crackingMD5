#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <pcosynchro/pcothread.h>
#include <QString>
#include <QCryptographicHash>
#include <QVector>
#include <iostream>
#include "threadmanager.h"

void workThread(ThreadManager* manager, int threadID, unsigned int nbThreads, long long unsigned int nbToCompute, QString hash, QString salt, unsigned int nbValidChars, QString charset, unsigned int nbChars);

#endif // MYTHREAD_H
