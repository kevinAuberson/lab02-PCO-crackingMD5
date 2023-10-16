#include "mythread.h"

static bool passwordCracked = false;
QString result = "";

void workThread(ThreadManager* manager,int threadID, unsigned int nbThreads, long long unsigned int nbToCompute, QString hash, QString salt, unsigned int nbValidChars, QString charset, unsigned int nbChars)
{
    bool changePosition = false;
    /*
     * Object QCryptographicHash servant à générer des md5
     */
    QCryptographicHash md5(QCryptographicHash::Md5);

    QString currentHash;

    unsigned long long int nbComputed = 0;
    /*
     * Mot de passe à tester courant
     */
    QString currentPasswordString;
    /*
     * Tableau contenant les index dans la chaine charset des caractères de
     * currentPasswordString
     */
    QVector<unsigned int> currentPasswordArray;
    /*
     * On initialise le premier mot de passe à tester courant en le remplissant
     * de nbChars fois du premier caractère de charset
     */
    currentPasswordString.fill(charset.at(0),nbChars - 1);
    currentPasswordString = charset.at(threadID) + currentPasswordString;
    currentPasswordArray.fill(0,nbChars);
    currentPasswordArray[0] = threadID;

    while (nbComputed < nbToCompute)
    {
        //permet d'arreter les autres threads une fois que un a trouvé le bon hash
        if(passwordCracked)
            return;

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

        if ((nbComputed % 1000) == 0) {
            manager->incrementPercentComputed((double)1000/nbToCompute);
        }
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
            //  permet d'incrémenté la lettre à l'emplacement suivant
            if(changePosition){
                currentPasswordArray[i]++;
            }else {
                // incrémente les lettres de façon à ce que chaque thread test une possiblité
                currentPasswordArray[i] = currentPasswordArray[i] + nbThreads;
            }

            if (currentPasswordArray[i] >= nbValidChars)
            {
                // met en place le décalage des différentes lettres entre thread
                currentPasswordArray[i] = threadID;
                i++;
                changePosition = true;
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

        nbComputed++;
    }
}
