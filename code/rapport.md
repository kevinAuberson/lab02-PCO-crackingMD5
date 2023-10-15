# Laboratoire 2 : Cracking md5

Auteurs: Kevin Auberson, Vitória Cosmo

## Introduction
Le but central de ce projet est le développement d'une application capable de déchiffrer des hash MD5 pour récupérer les mots de passe associés. Le logiciel initial qui nous a été fourni présentait des limitations en termes de performances, principalement en raison de l'absence de concurrence. Notre objectif principal était d'améliorer de manière significative ces performances en mettant en œuvre des calculs parallèles grâce à l'utilisation de threads.

## Description des fonctionnalités du logiciel
*à developper*
- Calcul du hash MD5 d'un mot de passe.
- Recherche du mot de passe correspondant à un hash MD5 donné.
- Utilisation de threads pour accélérer le processus de recherche.

## Choix d'implémentation
*------------------(à enlever)-------------*

*Comment avez-vous abordé le problème, quels choix avez-vous fait, quelle 
décomposition avez-vous choisie, quelles variables ont dû être protégées, ...*



Afin d'aborder le problème de manière optimale, nous avons ajouté des éléments dans les fichiers mythread.h et mythread.cpp et tout en effectuant les modifications nécessaires à la fonction startHacking. 

Notre principal objectif était d'assurer la création, le lancement, et la gestion des threads directement à l'intérieur de cette fonction cruciale. 

- Création de Threads

    À l'intérieur de la fonction startHacking, nous générons et lançons les threads requises pour le travail concurrent. 

- Partage des données
    
    Pour que chaque thread accomplisse sa tâche de manière indépendante, nous avons pris soin de partager de manière sécurisée les paramètres nécessaires.
    
    *-----------------------à compléter--------------------*

- Répartition du Travail

    Une partie essentielle de notre implémentation consiste en une répartition efficace du travail entre les threads. Chaque thread est chargé de générer et de tester des combinaisons de mots de passe dans le but de trouver le mot de passe correspondant au hash MD5 fourni. En s'attaquant à différentes combinaisons de manière concurrente, les threads permettent une accélération significative de la recherche.
    
    En effet, chaque thread explore le tableau currentPasswordArray de manière stratégique pour garantir une distribution équilibrée du travail. 
    Chaque thread parcourt de manière spécifique à travers les éléments de cet array car cette itération dépend de l'ID du thread ainsi que du nombre total de threads.
    Lorsqu'un thread atteint la fin de son sous-ensemble de combinaisons, il incrémente sa position dans le tableau de manière à prendre en charge de nouvelles combinaisons. 

    L'objectif est d'assurer que chaque thread traite un sous-ensemble différent de combinaisons de mots de passe, répartissant ainsi efficacement la charge de travail et contribuant ainsi à une progression plus rapide de la recherche globale.


- Terminaison des Threads

    Nous avons implémenté une fonctionnalité de terminaison des threads qui nous a permis d'obtenir des résultats sans attendre l'exécution de tous les threads. Dès qu'un thread trouve le mot de passe correspondant au hash MD5, la variable statique passwordCracked est définie sur true, le mot de passe est enregistré dans la variable result, et le thread est arrêté. Cela a contribué à économiser des ressources en évitant l'exécution inutile de threads supplémentaires.

- Partage d'Informations

    Un aspect crucial de notre implémentation était de garantir un partage sécurisé des informations entre les threads. Cela a été réalisé en veillant à ce que chaque thread ait accès aux données nécessaires de manière ordonnée, sans risque d'erreurs de synchronisation ni de conflits de données.
    *à compléter, quels mécanismes*

## Tests effectués
*----------------------(à enlever)-----------------------*

*Description de chaque test, et information sur le fait qu'il ait passé ou non*

*----------------------(à enlever)-----------------------*

Nous avons effectué une série de tests pour vérifier les performances et le bon fonctionnement de notre logiciel de crackage de hash MD5. Chaque test était conçu pour évaluer différents aspects de l'application.

*----------------------(à effectuer)-----------------------*
- Test de performance (temps)
- Test de précision (vérifier si le mdp trouvé est le bon)
- Test de terminaison (vérifier que le mécanisme de terminaison fonctionne correctement, cad, threads sont terminées une fois que le mdp est trouvé)
- Test de synchronisation (vérifier la fiabilité des valeurs des données partagées)

*----------------------(à effectuer)-----------------------*

# Conclusion

En implémentant le parallélisme à l'aide de threads, nous avons considérablement amélioré les performances de l'application, réduisant ainsi le temps nécessaire pour cracker un hash MD5. Les tests effectués ont confirmé que le logiciel fonctionne de manière précise et efficace, tout en garantissant la terminaison précoce des threads pour économiser des ressources.

*----------------------(à completer)-----------------------*

*Dire si on a eu des échecs, choses qui ne jouent pas, qu'on a pas réussi à implémenter*

*----------------------(à completer)-----------------------*


Ce projet illustre la manière dont l'utilisation du parallélisme peut avoir un impact significatif sur les performances d'une application. Il offre également une démonstration de l'importance de la synchronisation et du partage de données entre les threads pour garantir un fonctionnement correct.
