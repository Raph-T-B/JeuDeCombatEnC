#include"sae1_02.h"

// Verified
void testchargAffichScore(void){
    Joueur j;
    strcpy(j.pseudo,"drxzm");
    AffichStatJoueur(j);
} 
// Verified
void testChargerPartie(void) { ///////// Verifier la fonction de charger partie -> regarder si pas changé au merge -> git hub
    FileN f;
    char string[30];
    char nomFich[20];
    strcpy(nomFich,"partie1.txt");
    f=chargerPartie(nomFich);
    while(estVide(f)!=true) {
        sprintf(string,"%d, %s, %d\n",f.tete->nbrM,f.tete->lieu,f.tete->nivM);
        AffiRouge(string);
        f=supprT(f);
        if (f.tete==f.queue)f.queue=NULL;
    }
    return;
}

void testchargeJoueur(void){
    char** tab;
    int nbjoueur;
    tab=chargeJoueurs(&nbjoueur);
    printf("joueurs :\n%s\n%s\n",tab[0],tab[1]);
}

void testajoutJoueur(void){
    Joueur j;
    strcpy(j.pseudo,"drxzm");
    ListeParNom(j);
    strcpy(j.pseudo,"poulet");
    ajouterJoueur(j);
    ListeParNom(j);
    strcpy(j.pseudo,"amie");
    ajouterJoueur(j);
    ListeParNom(j);
    strcpy(j.pseudo,"zoulette");
    ajouterJoueur(j);
    ListeParNom(j);
    strcpy(j.pseudo,"mimolette");
    ajouterJoueur(j);
    ListeParNom(j);
}


// Verified
void testAjoutQueue(void){
    FileN f;
    f=fileVide();
    char string[30];
    f=ajdq(f,3,"coul",2);
    f=ajdq(f,3,"plai",1);
    f=ajdq(f,1,"coul",3);
    f=ajdq(f,5,"plai",4);
    while(estVide(f)!=true) {
        sprintf(string,"%d, %s, %d\n",f.tete->nbrM,f.tete->lieu,f.tete->nivM);
        AffiRouge(string);
        f.tete=f.tete->suiv;
        if (f.tete==f.queue)f.queue=NULL;
    }
}
// Verified
void testSupprTete(void){
    FileN f;
    char string[30];
    f=ajdq(f,3,"coridor",2);
    f=ajdq(f,3,"plaine",1);
    f=ajdq(f,1,"coridor",3);
    f=ajdq(f,5,"plaine",4);
    f=supprT(f);
    f=supprT(f);
    while(estVide(f)!=true) {
        sprintf(string,"%d, %s, %d\n",f.tete->nbrM,f.tete->lieu,f.tete->nivM);
        AffiRouge(string);
        f.tete=f.tete->suiv;
        if (f.tete==f.queue)f.queue=NULL;
    }
}
// Verified
void testMin(void){
    Joueur j;
    j.nbpart=3;
    int tab[3]={110,300,20};
    int tab2[3]={15,300,20};
    int tab3[3]={110,10,20};
    if(Min(tab,j)!=20){
        printf("Probleme de la fonction Min() test1\n");exit(1);
    }
    if(Min(tab2,j)!=15){
        printf("Probleme de la fonction Min() test2\n");exit(1);
    }
    if(Min(tab3,j)!=10){
        printf("Probleme de la fonction Min() test3\n");exit(1);
    }
}
// Verified
void testMoy(void){
    Joueur j;
    j.nbpart=3;
    float moy;
    int tab[3]={110,300,20};
    int tab2[3]={15,300,20};
    int tab3[3]={50,150,70};
    if(((int)(Moyenne(tab,j)*10))!=1433){
        printf("Probleme de la fonction Moyenne() test1\n");exit(1);
    }
    if(((int)(Moyenne(tab2,j)*10))!=1116){
        printf("Probleme de la fonction Moyenne() test2\n");exit(1);
    }
    if(((int)(Moyenne(tab3,j)*10))!=900){
        printf("Probleme de la fonction Moyenne() test3\n");exit(1);
    }
}
// Verified
void testMax(void){
    Joueur j;
    j.nbpart=3;
    int tab[3]={110,300,20};
    int tab2[3]={15,300,2000};
    int tab3[3]={110,10,20};
    if(indMax(tab,3)!=1){
        printf("Probleme de la fonction MaxScoreJoueur() test1\n");exit(1);
    }
    if(indMax(tab2,3)!=2){
        printf("Probleme de la fonction MaxScoreJoueur() test2\n");exit(1);
    }
    if(indMax(tab3,3)!=0){
        printf("Probleme de la fonction MaxScoreJoueur() test3\n");exit(1);
    }
}
// Verified
void testChoixArmeJ(void){
    Joueur j;
    int *Tab,arme;
    strcpy(j.pseudo,"drxzm");
    j.score=50;
    arme=ChoixArmeJ(j);
    printf("arme : %d\n",arme);
}
// Verified
void testChoixArmeM(void){
    int arme;
    arme=ArmeMonstre(5);
    if(arme==1 || arme==2 || arme==3 || arme==4 || arme==5){
        return;
    }
    else {
        printf("Probleme de test choixArmeMonstre \n");
        exit(1);
    }
}

// Verified
void testCombat(void){
    int res; 
    Joueur j;
    Monstre m;
    int arme;
    strcpy(m.nom,"petit_poulet");
    m.niv=1;
    strcpy(j.pseudo,"drxzm");
    j.score=50;
    res=Combat(j,m); 
    printf("resultat :%d\n",res); 
}
// Verified
void testResultat(void){
    Joueur j;
    Monstre m;
    int arme;
    m.nbDeg=1;
    strcpy(m.nom,"petit_poulet");
    m.niv=1;
    strcpy(j.pseudo,"drxzm");
    j.score=0;
    Resultat(&j,&m);
    m.niv=2;
    m.nbDeg=2;
    Resultat(&j,&m);
    m.niv=3;
    m.nbDeg=4;
    Resultat(&j,&m);
    printf("nbr points : %d\n",j.score);
}

void testlancement(){
    Joueur j;
    strcpy(j.pseudo,"drxzm");
    j.score=0;
    Lancement(j);
}

void testPositionInsertionScore(void) {
    int scores[100]={180,110,30};
    int nb_scores=3;
    int nouveau_score=120;
    int emplacement;
    emplacement=trouverPositionInsertionScore(scores,nb_scores,nouveau_score);
    printf("Il faut l'inserer à l'emplacement : %d du tableau score\n",emplacement);
    printf("nb attendu : 1\n");
}

// Verified
void testSauvegarderNvScore(void) {
    Joueur j;
    strcpy(j.pseudo,"poulet");
    int nouveau_score = 50;
    sauvegarderNvScore(j, nouveau_score);
}

// Verified
void testDemanderPartie() {
    printf("Test de demanderPartie :\n");
    char *fichier = demanderPartie();
    printf("Fichier retourné : %s\n", fichier);
    free(fichier);
}
// Verified
void testinititJoueur() {
    char*pseudo="swayd";
    Joueur j;
    j=inititJoueur(pseudo);
    printf("%dpdv,%dnbDeg%dnbPart,%dscore\n",j.pdv = 20,j.nbDeg = 1,j.nbpart = 0,j.score = 0);
}


void testPartie(){
    Joueur j;
    j.pdv=20;
    j.nbDeg=1;
    strcpy(j.pseudo,"drxzm");
    Partie(j);
}

void testAffiGris(void) {
    AffiGris("Texte en gris\n");
}

void testAffiRouge(void) {
    AffiRouge("Texte en rouge\n");
}

void testAffiVert(void) {
    AffiVert("Texte en vert\n");
}

void testAffiJaune(void) {
    AffiJaune("Texte en jaune\n");
}

void testAffiBleu(void) {
    AffiBleu("Texte en bleu\n");
}

void testAffiRose(void) {
    AffiRose("Texte en rose\n");
}

void testAffiViolet(void) {
    AffiViolet("Texte en violet\n");
}

void testAffiBlancGras(void) {
    AffiBlancGras("Texte en blanc gras\n");
}

void testAffichStatJoueur(void) {
    Joueur j;
    strcpy(j.pseudo, "swayd");
    j.nbpart = 5;
    AffichStatJoueur(j);
}

void testListeParNom(void) {
    Joueur j;
    strcpy(j.pseudo, "swayd");
    ListeParNom(j);
}

void testListeParScore(void) {
    Joueur j;
    strcpy(j.pseudo, "swayd");
    ListeParScore(j);
}

void testAfficheTab(void) {
    int Tab[] = {10, 20, 30, 40, 50};
    int taille = sizeof(Tab) / sizeof(Tab[0]);
    printf("10\t20\t30\t40\t50\n");
    afficheTab(Tab, taille);
}

void testBienvenue() {
    Bienvenue();
}

void testSortie() {
    Joueur j = {"swayd", 20, 1, 2, 200};
    Sortie(j);
}

void testFinPartie() {
    Joueur j = {"swayd", 20, 1, 2, 200};
    finPartie(j);
}

void testExecutNiveau() {
    Joueur j = {"swayd", 20, 1, 2, 200};
    Niveau niv = {2,"coul" , 1};
    int result = executNiveau(&j, &niv);
}

void testCreerMonstre() {
    Niveau niv = {2,"coul" , 1};
    Monstre m = creerMonstre(&niv,1);
}

void testMenu() {
    int choix = Menu();
}

void testScore() {
    Joueur j = {"swayd", 20, 1, 2, 200};
    printf("Score du joueur %s : %d\n", j.pseudo, j.score);
}

void testJeu() {
    Joueur j = {"swayd", 20, 1, 2, 200};
    Lancement(j);
}

void test_chargeScore() {
    Joueur j;
    strcpy(j.pseudo, "swayd");
    int* scores = chargeScore(&j);
    for (int i = 0; i < j.nbpart; i++) {
        printf("%d\n",scores[i]);
    }
    free(scores);
}

void test_fileVide() {
    FileN f = fileVide();
}

void test_estVide() {
    FileN fVide = fileVide();
    FileN fNonVide = fileVide();
    fNonVide=ajdq(fNonVide, 1, "Lieu", 1);
    if(estVide(fVide) == 1)printf("Vide\n");
    if(estVide(fNonVide) == 0)printf("nonVide\n");
}

void test_verifJoueur() {
    Joueur j;
    strcpy(j.pseudo, "nouveauJoueur");
    if(verifJoueur(j) == 0)printf("Bon nombre de joueur\n");
    ajouterJoueur(j);
    if(verifJoueur(j) == 1)printf("Bon nombre de joueur\n");
}

void testdemandePseudo(void){
    char* pseudo;
    pseudo=DemandePseudo();
    printf("\n\nle pseudo en sortie : %s\n\n",pseudo);
}

void testStatJoueur(void){
    StatJoueur();
}

void testAjoutNouvJoueur(void){
    Joueur j;
    strcpy(j.pseudo,"lilou");
    AjoutNouvJoueur(j);
}

int main(void){
    //testMin();
    //testMax();
    //testMoy();
    //testChoixArmeM();
    //testAjoutQueue();
     //testSupprTete();
    //testChargerPartie();
    //testchargAffichScore();
    //testchargeJoueur();
    //testChoixArmeJ();
    //testCombat();
    //testajoutJoueur();
    //Bienvenue();
    //testlancement();
    //testResultat();
    //testAjoutQueue();
    //testChargerPartie();
    //testChargerJoueur();
    //testPositionInsertionScore();
    //testSauvegarderNvScore();
    //testDemanderPartie();
    //testPartie();
    //testChargerJoueur();
    //testAffiGris();
    //testAffiRouge();
    //testAffiVert();
    //testAffiJaune;
    //testAffiBleu;
    //testAffiRose;
    //testAffiViolet();
    //testAffiBlancGras();
    //testAffichStatJoueur();
    //testListeParNom();
    //testListeParScore();
    //testAfficheTab();
    //testBienvenue();
    //testSortie();
     //testFinPartie();
    //testExecutNiveau();
    //testCreerMonstre();
    //testMenu();
    //testScore();
    //testJeu();
    //test_chargeScore();
    //test_fileVide();
    //test_estVide();
    //test_verifJoueur();
    //testDemandePseudo();
    //testAjoutNouvJoueur();
    //StatJoueur();
    global();
    return 0;
}

//fini tes fonctions test
