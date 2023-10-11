#include "mythread.h"

MyThread::MyThread(unsigned int nbThread, unsigned int nbToCompute, unsigned int nbChars, const QString& salt, const QString& hash, const QString& charset){
    this->nbToCompute = nbToCompute;
    this->nbComputed = 0;
    this->nbValidChars = charset.length();
    this->currentPasswordString.fill(charset.at(0), nbChars);
    this->currentPasswordArray.fill(0, nbChars);
    this->md5 = new QCryptographicHash(QCryptographicHash::Md5);
    this->hash = hash;
    this->nbThreads = nbThread;
    this->nbChars = nbChars;
    this->salt = salt;
}

void MyThread::startThread(){
    for (int i = 0; i < this->nbThreads; i++)
        this->threads.push_back(new PcoThread (&MyThread::workThread, i));
    for (int i = 0; i < this->nbThreads; i++)
            threads[i]->join();
}
QString MyThread::hashing(){
    /* On vide les données déjà ajoutées au générateur */
    md5->reset();
    /* On préfixe le mot de passe avec le sel */
    md5->addData(this->salt.toLatin1());
    md5->addData(this->currentPasswordString.toLatin1());
    /* On calcul le hash */
    QString currentHash = md5->result().toHex();

    return currentHash;
}
QString MyThread::workThread(int threadID){
    unsigned int i = threadID;
    while (nbComputed < nbToCompute) {

        /*
         * Si on a trouvé, on retourne le mot de passe courant (sans le sel)
         */
        if (hashing() == hash)
            return currentPasswordString;


        /*
         * On récupère le mot de pass à tester suivant.
         *
         * L'opération se résume à incrémenter currentPasswordArray comme si
         * chaque élément de ce vecteur représentait un digit d'un nombre en
         * base nbValidChars.
         *
         * Le digit de poids faible étant en position 0
         */

        while (i < (unsigned int)currentPasswordArray.size()) {
            currentPasswordArray[i]++;

            if (currentPasswordArray[i] >= nbValidChars) {
                currentPasswordArray[i] = 0;
                i = i + this->nbThreads;
            } else
                break;
        }

        /*
         * On traduit les index présents dans currentPasswordArray en
         * caractères
         */
        for (i=0;i<nbChars;i++)
            currentPasswordString[i]  = charset.at(currentPasswordArray.at(i));

        mutex.lock();
        nbComputed++;
        mutex.unlock();
    }
    return QString("");
}
