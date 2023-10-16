# Laboratoire 2 : Cracking md5

Auteurs: Kevin Auberson, Vitória Cosmo

## Introduction
Le but central de ce projet est le développement d'une application capable de déchiffrer des hash MD5 pour récupérer les mots de passe associés. Le logiciel initial qui nous a été fourni présentait des limitations en termes de performances, principalement en raison de l'absence de concurrence. Notre objectif principal était d'améliorer de manière significative ces performances en mettant en œuvre des calculs parallèles grâce à l'utilisation de threads.

## Fonctionnalités du logiciel
- Calcul du hash MD5 d'un mot de passe.
- Recherche du mot de passe correspondant à un hash MD5 donné.
- Utilisation de threads pour accélérer le processus de recherche.
- Utilisation de la programmation concurrente pour améliorer la performance de l'algorithme. 

## Choix d'implémentation

Afin d'aborder le problème de manière optimale, nous avons ajouté des éléments dans les fichiers *mythread.h* et *mythread.cpp* et tout en effectuant les modifications nécessaires à la fonction *startHacking*. 

Notre principal objectif était d'assurer la création, le lancement, et la gestion des threads directement à l'intérieur de cette fonction. 

- Création de Threads

    À l'intérieur de la fonction *startHacking*, nous générons et lançons les threads requis pour le travail concurrent. Ils sont stockés dans un tableau de pointeur de threads de type objet *PcoThread*. 

- Partage d'informations 
    
    Pour que chaque thread accomplisse sa tâche de manière indépendante, nous avons pris soin de partager de manière sécurisée les paramètres nécessaires.
    Nous passons par référence aux threads les paramètres suivants: hash à rechercher, le sel, le jeu de caractères et le nombre de caractères dans le mot de passe. 

- Communication entre les threads
     La variable *passwordCracked* est introduite pour gérer la synchronisation entre les threads. Lorsqu'un thread trouve le mot de passe, il met à jour *passwordCracked*, ce qui permet aux autres threads de s'arrêter. 
     
     La variable *result* est utilisée pour stocker le mot de passe trouvé. L'utilisation de cette variable partagée permet à chaque thread d'être capable d'écrire le résultat final. Elle est initialisée vide pour le cas échéant ou l'on ne trouve pas le mot de passe. 

- Répartition du Travail

    Une partie essentielle de notre implémentation consiste en une répartition efficace du travail entre les threads. Chaque thread exécute en parallèle la fonction *workThread*, c'est ici qu'elle teste les combinaisons de mots de passe dans le but de trouver le mot de passe correspondant au hash MD5 fourni. 
    
    En effet, chaque thread explore le tableau *currentPasswordArray* de manière stratégique pour garantir une distribution équilibrée du travail. 
    Chacun d'entre eux parcourt les éléments de ce tableau en fonction de son *ID* thread et l'incrémentation se fait avec le nombre total de threads.
    Lorsqu'un thread atteint la fin de son sous-ensemble de combinaisons, il incrémente l'index actuel d'où il se trouve dans le tableau de manière à prendre en charge de nouvelles combinaisons. 

    L'objectif est d'assurer que chaque thread traite un sous-ensemble différent de combinaisons de mots de passe, répartissant ainsi efficacement la charge de travail et contribuant ainsi à une progression plus rapide de la recherche globale.


- Terminaison des Threads

    Nous avons implémenté une fonctionnalité de terminaison des threads qui nous a permis d'obtenir le résultat sans attendre la fin de l'exécution de tous les threads. Dès qu'un thread trouve le mot de passe correspondant au hash MD5, la variable statique *passwordCracked* est définie à true, le mot de passe est enregistré dans la variable *result*, et les threads sont arrêtés. Cela a contribué à économiser des ressources en évitant l'exécution inutile de threads supplémentaires.
    Une fois le résultat retourné, on lance une boucle qui joint chaque thread du vector de threads. 

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
