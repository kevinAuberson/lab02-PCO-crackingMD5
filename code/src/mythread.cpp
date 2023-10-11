#include "mythread.h"

MyThread::MyThread(unsigned int nbThread, unsigned int nbToCompute, unsigned int nbChars, const QString& salt, const QString& hash, const QString& charset, int nbValidChars){
    this->nbToCompute = nbToCompute;
    this->nbComputed = 0;
    this->nbValidChars = charset.length();
    this->currentPasswordString.fill(charset.at(0), nbChars);
    this->currentPasswordArray.fill(0, nbChars);
    this->md5 = new QCryptographicHash(QCryptographicHash::Md5);
    this->hash = hash;
    this->nbThreads = nbThread;
}

void MyThread::startThread(){
    for (int i = 0; i < this->nbThreads; ++i)
        this->threads.push_back(new PcoThread (&MyThread::workThread, i));
}
QString MyThread::hashing(){
    /* On vide les données déjà ajoutées au générateur */
    this->md5.reset();
    /* On préfixe le mot de passe avec le sel */
    md5.addData(salt.toLatin1());
    md5.addData(currentPasswordString.toLatin1());
    /* On calcul le hash */
    QString currentHash = md5.result().toHex();

    return currentHash;
}
QString MyThread::workThread(int threadID){

}
