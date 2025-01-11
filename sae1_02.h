/**
 * @file sae1_02.h
 * @brief Fichier contenant l'initialisation des fonction du jeu de chevalier/monstre
 * @author CAUMOND Raphaël & FERRANDON Gabin
 * @date 08/01/2025
 */

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include <time.h>
typedef struct {
    char pseudo[21];
    int pdv;
    int nbDeg;
    int nbpart;
    int score;
}Joueur;//Liste chaînée ou tableau dynamique

typedef enum {Pierre=1,Feuille,Ciseaux,BonARien,Pouvoir}Arme;

typedef struct niveausuiv{
    int nbrM;
    char lieu[5];
    int nivM;
    struct niveausuiv *suiv;
}Niveau; 

typedef struct {
    Niveau* tete;
    Niveau* queue;
}FileN; //Liste chaînée pour 1 groupe de combats coridore



//Scores : Tableau trié pour chaque joueur
typedef struct {
    int niv;
    char nom[25];
    int pdv;
    int nbDeg;
    int num;
}Monstre;

typedef struct fmonstre{
    Monstre m;
    struct fmonstre *suiv; 
}Fmonstre,*FileM;




/**
 * @brief Charge les scores des joueurs.
 * 
 * @param j Pointeur vers un joueur.
 * @return int* Tableau des scores des joueurs.
 */
int* chargeScore(Joueur *j);

/**
 * @brief Charge une partie sauvegardée à partir d'un fichier.
 * 
 * @param nomFich Nom du fichier contenant la sauvegarde.
 * @return FileN File des niveaux chargés.
 */
FileN chargerPartie(char *nomFich);

/**
 * @brief Charge les joueurs depuis une source externe.
 * 
 * @param nbjoueur Pointeur vers une variable contenant le nombre de joueurs.
 * @return char** Tableau de chaînes de caractères représentant les pseudos des joueurs.
 */
char** chargeJoueurs(int* nbjoueur);

/**
 * @brief Calcule la moyenne des scores d'un joueur.
 * 
 * @param tabScore Tableau des scores.
 * @param j Joueur concerné.
 * @return float Moyenne des scores.
 */
float Moyenne(int tabScore[], Joueur j);

/**
 * @brief Trouve l'indice du maximum dans un tableau.
 * 
 * @param tab Tableau d'entiers.
 * @param taille Taille du tableau.
 * @return int Indice du maximum.
 */
int indMax(int tab[], int taille);

/**
 * @brief Trouve le score minimal pour un joueur donné.
 * 
 * @param tabScore Tableau des scores.
 * @param j Joueur concerné.
 * @return int Score minimal.
 */
int Min(int tabScore[], Joueur j);

/**
 * @brief Initialise une file vide de niveaux.
 * 
 * @return FileN File vide.
 */
FileN fileVide(void);

/**
 * @brief Vérifie si une file de niveaux est vide.
 * 
 * @param f File de niveaux.
 * @return bool true si la file est vide, false sinon.
 */
bool estVide(FileN f);

/**
 * @brief Ajoute un niveau à la file.
 * 
 * @param f File des niveaux.
 * @param nbrM Nombre de monstres dans le niveau.
 * @param lieu Lieu du niveau.
 * @param nivM Niveau des monstres.
 * @return FileN File mise à jour.
 */
FileN ajdq(FileN f, int nbrM, char *lieu, int nivM);

/**
 * @brief Supprime le premier niveau de la file.
 * 
 * @param f File des niveaux.
 * @return FileN File mise à jour.
 */
FileN supprT(FileN f);

/**
 * @brief Ajoute un monstre à la file.
 * 
 * @param f File des monstres.
 * @param m Monstre à ajouter.
 * @return FileM File mise à jour.
 */
FileM ajdqMonstre(FileM f, Monstre m);

/**
 * @brief Supprime le premier monstre de la file.
 * 
 * @param f File des monstres.
 * @return FileM File mise à jour.
 */
FileM supprTMonstre(FileM f);

/**
 * @brief Vérifie si une file de monstres est vide.
 * 
 * @param f File des monstres.
 * @return bool true si la file est vide, false sinon.
 */
bool estVideFmonstre(FileM f);

/**
 * @brief Vérifie si un joueur est valide.
 * 
 * @param j Joueur à vérifier.
 * @return bool true si le joueur est valide, false sinon.
 */
bool verifJoueur(Joueur j);

/**
 * @brief Ajoute un joueur.
 * 
 * @param j Joueur à ajouter.
 */
void ajouterJoueur(Joueur j);

/**
 * @brief Fait un trie dichotomique d'un tableau de chaines de caractères.
 * 
 * @param n taille du tableau.
 */
void triDicho(char* tab[], int n);

/**
 * @brief Fusionne et tri les tableau R et S dans le tableau T.
 * 
 * @param R tableau dont on prend le contenu.
 * @param n taille de R.
 * @param S tableau dont on prend le contenu.
 * @param m taille de S.
 * @param T tableau contenant R et S trié.
 */
void fusion(char* R[], int n, char* S[], int m, char* T[]);

/**
 * @brief Copie le tableau la partie de T entre l'indice i et j dans le tableau R .
 * 
 * @param T tableau dont on prend le contenu.
 * @param i indice du début.
 * @param j indice de fin.
 * @param R Tableau dans lequel on copie.
 */
void copier(char* T[], int i, int j, char* R[]);

/**
 * @brief Sauvegarde un nouveau score pour un joueur.
 * 
 * @param j Joueur concerné.
 * @param nouveau_score Score à sauvegarder.
 */
void sauvegarderNvScore(Joueur j, int nouveau_score);

/**
 * @brief Trouve la position d'insertion pour un nouveau score dans un tableau trié.
 * 
 * @param scores Tableau des scores.
 * @param nb_scores Nombre de scores dans le tableau.
 * @param nouveau_score Nouveau score à insérer.
 * @return int Position d'insertion.
 */
int trouverPositionInsertionScore(int *scores, int nb_scores, int nouveau_score);

/**
 * @brief Ajoute un nouveau joueur.
 * 
 * @param j Joueur à ajouter.
 */
void AjoutNouvJoueur(Joueur j);

/**
 * @brief Demande le nom d'une partie à charger.
 * 
 * @return char* Nom de la partie.
 */
char* demanderPartie(void);

/**
 * @brief Demande le pseudo d'un joueur.
 * 
 * @return char* Pseudo du joueur.
 */
char* DemandePseudo(void);

/**
 * @brief Initialise un joueur avec un pseudo donné.
 * 
 * @param pseudo Pseudo du joueur.
 * @return Joueur Joueur initialisé.
 */
Joueur inititJoueur(char *pseudo);

/**
 * @brief Affiche du texte en rose.
 * 
 * @param texte Texte à afficher.
 */
void AffiRose(char* texte);

/**
 * @brief Affiche du texte en jaune.
 * 
 * @param texte Texte à afficher.
 */
void AffiJaune(char* texte);

/**
 * @brief Affiche du texte en rouge.
 * 
 * @param texte Texte à afficher.
 */
void AffiRouge(char* texte);

/**
 * @brief Affiche la liste des joueurs existants.
 */
void AffichJoueurExistant(void);

/**
 * @brief Affiche du texte en bleu.
 * 
 * @param texte Texte à afficher.
 */
void AffiBleu(char* texte);

/**
 * @brief Affiche du texte en vert.
 * 
 * @param texte Texte à afficher.
 */
void AffiVert(char* texte);

/**
 * @brief Affiche du texte en violet.
 * 
 * @param texte Texte à afficher.
 */
void AffiViolet(char* texte);

/**
 * @brief Affiche du texte en gris.
 * 
 * @param texte Texte à afficher.
 */
void AffiGris(char* texte);

/**
 * @brief Affiche du texte en gras blanc.
 * 
 * @param texte Texte à afficher.
 */
void AffiBlancGras(char* texte);

/**
 * @brief Affiche les statistiques d'un joueur.
 * 
 * @param j Joueur concerné.
 */
void AffichStatJoueur(Joueur j);

/**
 * @brief Affiche et gère les statistiques des joueurs.
 */
void StatJoueur(void);

/**
 * @brief Affiche un tableau d'entiers.
 * 
 * @param Tab Tableau d'entiers.
 * @param taille Taille du tableau.
 */
void afficheTab(int Tab[], int taille);

/**
 * @brief Trie et liste les joueurs par nom.
 * 
 * @param j Joueur concerné.
 */
void ListeParNom(Joueur j);

/**
 * @brief Trie et liste les joueurs par score.
 * 
 * @param j Joueur concerné.
 */
void ListeParScore(Joueur j);

/**
 * @brief Affiche un message de bienvenue.
 */
void Bienvenue(void);

/**
 * @brief Gère la sortie du jeu pour un joueur.
 * 
 * @param j Joueur concerné.
 */
void Sortie(Joueur j);

/**
 * @brief Gère une partie pour un joueur.
 * 
 * @param j Joueur concerné.
 */
void Partie(Joueur j);

/**
 * @brief Gère la fin de partie pour un joueur.
 * 
 * @param j Joueur concerné.
 */
void finPartie(Joueur j);

/**
 * @brief Exécute un niveau pour un joueur donné.
 * 
 * @param j Pointeur vers le joueur.
 * @param niv Pointeur vers le niveau.
 * @return int Résultat de l'exécution.
 */
int executNiveau(Joueur *j, Niveau* niv);

/**
 * @brief Lance le jeu pour un joueur.
 * 
 * @param j Joueur concerné.
 */
void Lancement(Joueur* j);

/**
 * @brief Crée un monstre dans un niveau donné.
 * 
 * @param niv Pointeur vers le niveau.
 * @param num Numéro du monstre.
 * @return Monstre Monstre créé.
 */
Monstre creerMonstre(Niveau* niv, int num);

/**
 * @brief Affiche le menu principal.
 * 
 * @return int Choix de l'utilisateur.
 */
int Menu(void);

/**
 * @brief Affiche le résultat d'un combat.
 * 
 * @param j Pointeur vers le joueur.
 * @param m Pointeur vers le monstre.
 */
void Resultat(Joueur *j, Monstre* m);

/**
 * @brief Gère l'arme d'un monstre en fonction de son niveau.
 * 
 * @param niveau Niveau du monstre.
 * @return int Arme attribuée.
 */
int ArmeMonstre(int niveau);

/**
 * @brief Gère un combat entre un joueur et un monstre.
 * 
 * @param j Joueur concerné.
 * @param m Monstre concerné.
 * @return int Résultat du combat.
 */
int Combat(Joueur j, Monstre m);

/**
 * @brief Gère le choix d'arme d'un joueur.
 * 
 * @param j Joueur concerné.
 * @return int Arme choisie.
 */
int ChoixArmeJ(Joueur j);

/**
 * @brief Calcule le score d'un monstre en fonction de son groupe.
 * 
 * @param m Monstre concerné.
 * @param groupe Groupe du monstre.
 * @return int Score calculé.
 */
int Score(Monstre m, char groupe);

/**
 * @brief Fonction principale du jeu.
 */
void jeu(void);

/**
 * @brief Gère la logique globale du programme.
 */
void global();



/*
LES FONCTIONS A FAIRE :

-Chargement:
    joueurs
    score/joueurs

-Menu principal
-mise en combat
-attaque
-calcul des points
-sauvegarde

DIFFERENTES STRUCTURES A CHOISIR :
-ARMES : tableau
-JOUEURS : différents fichiers
-Score : variable dans le jeu + dans un fichier/joueurs
-Monstres en ligne : liste
-Monstres attanquants en mm temps : tableau

*/