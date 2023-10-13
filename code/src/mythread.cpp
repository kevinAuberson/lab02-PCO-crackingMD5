#include "mythread.h"
using namespace std;

extern bool passwordCracked;

void workThread(int threadID, unsigned int nbThreads, long long unsigned int nbComputed, long long unsigned int nbToCompute, QString hash, QString salt, QVector<unsigned int> currentPasswordArray, QString currentPasswordString, unsigned int nbValidChars, QString charset, unsigned int nbChars, QString result)
{
    QCryptographicHash md5(QCryptographicHash::Md5);
    QString currentHash;
    while (nbComputed < nbToCompute)
    {
        /* On vide les données déjà ajoutées au générateur */
        md5.reset();
        /* On préfixe le mot de passe avec le sel */
        md5.addData(salt.toLatin1());
        md5.addData(currentPasswordString.toLatin1());
        /* On calcul le hash */
        currentHash = md5.result().toHex();

        /*
         * Si on a trouvé, on retourne le mot de passe courant (sans le sel)
         */
        if (currentHash == hash)
        {
            result = currentPasswordString;
            passwordCracked = true;
            return;
        }

        if(passwordCracked)
            return;
        //if ((nbComputed % 1000) == 0) {
        //            incrementPercentComputed((double)1000/nbToCompute);
        //        }
        /*
         * On récupère le mot de pass à tester suivant.
         *
         * L'opération se résume à incrémenter currentPasswordArray comme si
         * chaque élément de ce vecteur représentait un digit d'un nombre en
         * base nbValidChars.
         *
         * Le digit de poids faible étant en position 0
         */
        unsigned int i = 0;

        while (i < (unsigned int)currentPasswordArray.size())
        {
            currentPasswordArray[i] = currentPasswordArray[i] + threadID + nbThreads;

            if (currentPasswordArray[i] >= nbValidChars)
            {
                currentPasswordArray[i] = 0;
                i++;
            }
            else
            {
                break;
            }
        }

        /*
         * On traduit les index présents dans currentPasswordArray en
         * caractères
         */
        for (i=0;i<nbChars;i++)
            currentPasswordString[i]  = charset.at(currentPasswordArray.at(i));
        std::cout << "Thread " << threadID << " : " << currentPasswordString.toStdString() << endl;
        nbComputed++;
    }
}
