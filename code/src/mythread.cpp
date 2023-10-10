#include "mythread.h"

MyThread::MyThread(int nbThreads){
    this->nbThreads = nbThreads;
    for (int i = 0; i < this->nbThreads; ++i)
        this->threads.push_back(new PcoThread (&MyThread::workThread, i));
}

void MyThread::workThread(int threadID){

}
