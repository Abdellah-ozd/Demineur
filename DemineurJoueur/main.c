//Version joueur

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#pragma warning(disable:4996)

typedef enum { LIBRE, BOMBE } Contenu;
typedef enum { MASQUEE, DEMASQUEE } Etat;
typedef enum { EN_COURS, GAGNEE, PERDUE } Statut;

typedef struct {
    Contenu cont;
    Etat etat;
} Cellule;

enum { TAILLE = 10, NB_BOMBES = 20 };
typedef Cellule Partie[TAILLE][TAILLE];

void remplir(Partie p, int nb);
void melanger(Partie p);
void init(Partie p, int nb);
void afficher(const Partie p);
void demasquer(Partie p, int r, int c);
Statut statut(const Partie p);
int jouable(const Partie p, int r, int c);

void init(Partie p, int nb) {
    remplir(p, nb);
    melanger(p);
}

void remplir(Partie p, int nb) {
    assert(nb >= 0 && nb <= TAILLE * TAILLE);
    for (int r = 0; r < TAILLE; ++r)
        for (int c = 0; c < TAILLE; ++c) {
            p[r][c].etat = MASQUEE;
            if (nb > 0) {
                p[r][c].cont = BOMBE;
                --nb;
            }
            else
                p[r][c].cont = LIBRE;
        }
}

void melanger(Partie p) {
    for (int ri = TAILLE - 1; ri >= 0; --ri)
        for (int ci = TAILLE - 1; ci > 0 || (ci == 0 && ri > 0); --ci) {
            int i = (ri * TAILLE) + ci;
            int j = rand() % (i + 1);
            int rj = j / TAILLE;
            int cj = j % TAILLE;
            Contenu tmp = p[ri][ci].cont;
            p[ri][ci].cont = p[rj][cj].cont;
            p[rj][cj].cont = tmp;
        }
}

static const int DIR[][2] =
{ {1 , 0}, { -1 , 0}, {0 , 1}, {0 , -1}, {1 , 1}, { -1 , 1}, { -1 , -1}, {1 , -1} };
static const int NBDIRS = sizeof(DIR) / sizeof(DIR[0]);

int bombes(const Partie p, int r, int c) {
    assert(0 <= r && r < TAILLE && 0 <= c && c < TAILLE);
    int b = 0;
    for (int d = 0; d < NBDIRS; ++d) {
        int rx = r + DIR[d][0];
        int cx = c + DIR[d][1];
        if (0 <= rx && rx < TAILLE && 0 <= cx && cx < TAILLE && p[rx][cx].cont == BOMBE)
            ++b;
    }
    return b;
}

char caractere(const Partie p, int r, int c) {
    assert(0 <= r && r < TAILLE && 0 <= c && c < TAILLE);
    char ch = '.';
    if (p[r][c].etat == DEMASQUEE) {
        if (p[r][c].cont == BOMBE)
            ch = 'B';
        else {
            int b = bombes(p, r, c);
            ch = b ? '0' + b : ' ';
        }
    }
    return ch;
}

void afficher(const Partie p) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    printf("   ");
    for (int c = 0; c < TAILLE; ++c)
        printf(" %2d", c);
    printf("\n");
    for (int r = 0; r < TAILLE; ++r) {
        printf("%2d", r);
        for (int c = 0; c < TAILLE; ++c)
            printf(" %2c", caractere(p, r, c));
        printf("\n");
    }
}

void demasquer(Partie p, int r, int c) {
    assert(jouable(p, r, c));
    p[r][c].etat = DEMASQUEE;
    if (p[r][c].cont == LIBRE && bombes(p, r, c) == 0)
        for (int d = 0; d < NBDIRS; ++d) {
            int rx = r + DIR[d][0];
            int cx = c + DIR[d][1];
            if (jouable(p, rx, cx))
                demasquer(p, rx, cx);
        }
}

int jouable(const Partie p, int r, int c) {
    return 0 <= r && r < TAILLE && 0 <= c && c < TAILLE && p[r][c].etat == MASQUEE;
}

Statut statut(const Partie p) {
    Statut s = GAGNEE;
    for (int r = 0; r < TAILLE; ++r)
        for (int c = 0; c < TAILLE; ++c)
            if (p[r][c].cont == BOMBE) {
                if (p[r][c].etat == DEMASQUEE)
                    return PERDUE;
            }
            else if (p[r][c].etat == MASQUEE)
                s = EN_COURS;
    return s;
}

int main() {
    srand((unsigned int)time(NULL));
    Partie p;
    init(p, NB_BOMBES);
    afficher(p);

    while (statut(p) == EN_COURS) {
        int r, c;
        printf("Entrez une ligne et une colonne (ex: 2 3) : ");
        while (scanf("%d %d", &r, &c) != 2 || !jouable(p, r, c)) {
            printf("Coordonnées invalides ! Réessayez : ");
            while (getchar() != '\n'); 
        }

        demasquer(p, r, c);
        afficher(p);
    }

    printf("Vous avez %s !\n", statut(p) == GAGNEE ? "gagné" : "perdu");
    return 0;
}
