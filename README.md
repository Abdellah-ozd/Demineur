# Démineur en C

## Présentation  
Ce projet est une implémentation du jeu Démineur en C, jouable en terminal.  
Le but du jeu est de découvrir toutes les cases sans bombe.  

## Fonctionnalités  
- Grille de 10x10  
- 20 bombes placées aléatoirement (modifiable dans le code source)  
- Détection du nombre de bombes adjacentes  
- Révélation automatique des zones sûres  
- Mode interactif : le joueur entre les coordonnées  
- Mode automatique : simulation d'une partie  

## Règles du jeu

Le jeu de démineur consiste en une grille de **10x10** cases contenant **20 bombes** placées aléatoirement.  
L'objectif est de révéler toutes les cases **sans bombe** pour gagner.  

### Fonctionnement :
- Une case peut être **libre** ou contenir une **bombe**.
- Une case **masquée** doit être révélée par le joueur.
- Si une case révélée contient une bombe, la partie est **perdue**.
- Sinon, un chiffre apparaît indiquant le **nombre de bombes adjacentes**.
- Si une case vide (sans bombe adjacente) est révélée, les cases voisines sont **automatiquement dévoilées**.
- La partie est **gagnée** quand toutes les cases sans bombe sont découvertes.

### Modes de jeu :
- **Démineur Auto** : L’ordinateur joue tout seul de manière aléatoire.
- **Démineur Joueur** : Le joueur choisit lui-même les cases à révéler.


