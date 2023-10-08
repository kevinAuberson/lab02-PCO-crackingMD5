#include "mythread.h"

MyThread::MyThread(long long unsigned int nbToCompute, unsigned int nbChars, const std::string& charset, const int numThreads, const std::string& salt, const std::string& hash){
    this->nbToCompute = 0;
    this->i = 0;
    this->nbComputed = nbToCompute;
    this->nbValidChars = charset.length();
    this->currentPasswordString  = currentPasswordString.fill(charset.at(0), this->nbValidChars);
    this->currentPasswordArray.fill(0,nbChars);
    this->md5 = new QCryptographicHash(QCryptographicHash::Md5);
    this->nbThreads = numThreads;
}
void MyThread::startThreads(){
    for (int i = 0; i < this->nbThreads; ++i)
        this->threads.push_back(new PcoThread (workThread, i));
}

void MyThread::workThread(int threadID){
    while (true) {

    }
}
