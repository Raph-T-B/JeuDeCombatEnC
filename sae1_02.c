/**
 * @file sae1_02.h
 * @brief Fichier contenant l'initialisation des fonction du jeu de chevalier/monstre
 * @author CAUMOND Raphaël & FERRANDON Gabin
 * @date 08/01/2025
 */

#include"sae1_02.h"


int* chargeScore(Joueur *j){
    FILE* flot;
    int score,*TabScore,ind;
    char nomFich[26];
    strcpy(nomFich,"joueurs/\0");
    strcat(nomFich,j->pseudo);
    strcat(nomFich,".txt\0");
    flot=fopen(nomFich,"r");
    if(flot==NULL){
        printf("Probleme d'ouverture fichier score de : %s \n",nomFich);
        return NULL;
    }
    fscanf(flot,"%d",&j->nbpart);
    TabScore=(int*)malloc(j->nbpart*sizeof(int));
    if (TabScore==NULL){
        printf("Erreur de malloc !\n");
        free(TabScore);
        exit(1);
    }
    if (j->nbpart==0)TabScore[0]=0;
    else{
        for(ind=0;ind<j->nbpart;ind++){
            fscanf(flot,"%d",&TabScore[ind]);
        }
    }
    fclose(flot);
    return TabScore;
}


FileN chargerPartie(char *nomFich) {
    FILE *flot;
    int taille=0,nbM=0,nivM=1;
    char lieu[6];
    FileN l;
    l=fileVide();
    flot = fopen(nomFich,"r");
    if (flot==NULL) {
        printf("Problème dans l'ouverture du fichier %s\n",nomFich);
        exit(1);
    }
    fscanf(flot,"%d",&taille);
    if (taille==0){
        printf("Pb: pas de niveau dans cette partie.");
        exit(2);
    }
    for (int i=0;i<taille;i++) {
        fscanf(flot,"%d%s%d",&nbM,lieu,&nivM);
        l=ajdq(l,nbM,lieu,nivM);
    }
    fclose(flot);
    return l;
}

char** chargeJoueurs(int* nbjoueur){
    int ind;
    char nom[25],**tab,*test;
    FILE *flot;
    flot=fopen("joueurs/joueurs.don","r");
    if(flot==NULL){
        AffiRouge("PB d'ouverture fichier joueurs\n");
        exit(1);
    }
    fscanf(flot,"%d",nbjoueur);
    tab=(char**)malloc(*nbjoueur*sizeof(char*));
    if (tab==NULL){
        AffiRouge("Probleme de malloc1\n");
        free(tab);
        exit(1);
    }
    for(ind=0;ind<*nbjoueur;ind++){
        fscanf(flot,"%s",nom);
        tab[ind]=(char*)malloc((strlen(nom))*sizeof(char));
        if (tab[ind]==NULL){
            AffiRouge("Probleme de malloc2\n");
            free(tab[ind]);
            exit(1);
        }
        strcpy(tab[ind],nom);
    }
    fclose(flot);
    return tab;
}


FileN fileVide(void) {
    FileN f;
    f.queue=NULL;
    f.tete=NULL;
    return f;
}

bool estVide(FileN f) {
    return f.tete == NULL;
}

FileN ajdq(FileN f, int nbrM, char *lieu, int nivM) {
    Niveau *nouveau;
    nouveau=(Niveau*)malloc(sizeof(Niveau));
    if (nouveau == NULL) {
        printf("Problème d'allocation mémoire\n");
        free(nouveau);
        exit(1);
    }
    nouveau->nbrM = nbrM;
    strcpy(nouveau->lieu, lieu);
    nouveau->lieu[sizeof(nouveau->lieu) - 1] = '\0';
    nouveau->nivM = nivM;
    nouveau->suiv = NULL;
    if (estVide(f)) {
        f.queue=nouveau;
        f.tete=nouveau;
        return f ;
    }
    f.queue->suiv=nouveau;
    f.queue=nouveau;
    return f;
}

FileN supprT(FileN f) {
    Niveau *aux;
    if(f.tete==NULL){
        f.tete=NULL;
        f.queue=NULL;
        return f;
    }
    if(f.tete==f.queue){
        aux=f.tete;
        f.tete=NULL;
        f.queue=NULL;
        free(aux);
        return f;
    }
    aux=f.tete;
    f.tete=f.tete->suiv;
    free(aux);
    return f;
}

FileM ajdqMonstre(FileM f,Monstre m) {
    Fmonstre* monstre;
    monstre=(Fmonstre*)malloc(sizeof(Fmonstre));
    if(monstre==NULL){
        AffiRouge("Probleme de malloc ajdqMonstre\n");
    }
    monstre->m=m;
    if (f==NULL){
        f=monstre;
        f->suiv=monstre;
        return f;
    }
    monstre->suiv=f->suiv;
    f->suiv=monstre;
    f=monstre;
    return f;
}

FileM supprTMonstre(FileM f){
    Fmonstre* aux;
    if(f==NULL)return NULL;
    if(f->suiv==f->suiv->suiv){
        free(f);
        return NULL;
    }
    aux=f->suiv;
    f->suiv=f->suiv->suiv;
    free(aux);
    return f;
}

bool estVideFmonstre(FileM f) {
    return f == NULL;
}


bool verifJoueur(Joueur j){
    char** tab;
    int nb,ind;
    tab=chargeJoueurs(&nb);
    for(ind=0;ind<nb;ind++){
        if(strcmp(tab[ind],j.pseudo)==0)return true;
    }
    return false;
}

void ajouterJoueur(Joueur j){
    int ind,taille;
    char** tab,*pseudo;
    FILE* flot;
    pseudo=(char*)malloc(21*sizeof(char));
    if(pseudo==NULL){
        AffiRouge("PB de malloc pour le joueur ..");
        exit(1);
    }
    strcpy(pseudo,j.pseudo);
    tab=chargeJoueurs(&taille);
    if (tab == NULL) {
        printf("Erreur lors du chargement des joueurs.\n");
        return;
    }
    flot=fopen("joueurs/joueurs.don","w");
    if (flot == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier joueurs.don.\n");
        return;
    }
    tab[taille]=pseudo;
    taille=taille+1;
    fprintf(flot,"%d\n",taille);
    triDicho(tab,taille);
    for(ind=0;ind<taille;ind++){
        fprintf(flot,"%s\n",tab[ind]);
        }
    fclose(flot);
}

void copier(char* T[], int i, int j, char* R[]) {
 int K = 0;
 while (i < j) {
 R[K] = T[i];
 i = i + 1;
 K = K + 1;
 }
}

void fusion(char* R[], int n, char* S[], int m, char* T[]) {
 int K = 0, indR = 0, indS = 0;
 while (indS < m && indR < n) {
 if (strcmp(R[indR], S[indS]) < 0) {
 T[K] = R[indR];
 indR = indR + 1;
 }
 else {
 T[K] = S[indS];
 indS = indS + 1;
 }
 K=K+1;
 }
 while (indR < n) {
 T[K] = R[indR];
 indR = indR + 1;
 K = K + 1;
 }
 while (indS < m) {
 T[K] = S[indS];
 indS = indS + 1;
 K = K + 1;
 }
}

void triDicho(char* tab[], int n) {
 char** R;
 char** S;
 if(n<=1)return;
 R = (char**)malloc((n / 2) * sizeof(char*));
 S = (char**)malloc((n - n / 2) * sizeof(char*));
 if(R==NULL || S==NULL)return;
 copier(tab,0,n/2,R);
 copier(tab,n/2,n,S);
 triDicho(R,n/2);
 triDicho(S,n-n/2);
 fusion(R,n/2,S,n-n/2,tab);
 free(R);
 free(S);
}


float Moyenne(int tabScore[],Joueur j){
    float moy=0;
    int ind;
    for (ind=0;ind<j.nbpart;ind++){
        moy=moy+tabScore[ind];
    }
    moy=moy/j.nbpart;
    return moy;
}


int indMax(int tab[],int taille){ 
    int max=tab[0],ind,indicef=0;
    for(ind=1;ind<taille;ind++){
        if(tab[ind]>max){
            max=tab[ind];
            indicef=ind;
        }
    }
    return indicef;
}


int Min(int tabScore[],Joueur j){
    int min=tabScore[0],ind;
    for(ind=1;ind<j.nbpart;ind++){
        if(tabScore[ind]<min){
            min=tabScore[ind];
        }
    }
    return min;
}

void AffiGris(char* texte){
    printf("\033[30;01m%s\033[00m",texte);
}
void AffiRouge(char* texte){
    printf("\033[31;01m%s\033[00m",texte);
}
void AffiVert(char* texte){
    printf("\033[32;01m%s\033[00m",texte);
}
void AffiJaune(char* texte){
    printf("\033[33;01m%s\033[00m",texte);
}
void AffiBleu(char* texte){
    printf("\033[34;01m%s\033[00m",texte);
}
void AffiRose(char* texte){
    printf("\033[35;01m%s\033[00m",texte);
}
void AffiViolet(char* texte){
    printf("\033[36;01m%s\033[00m",texte);
}
void AffiBlancGras(char* texte){
    printf("\033[37;01m%s\033[00m",texte);
}

void AffichStatJoueur(Joueur j){
    int* TabScore,indmax;
    TabScore=chargeScore(&j);
    char string[50];
    if(j.nbpart==0){AffiRouge("Ce joueur n'a pas encore jouer de parties \n\n");return;}
    AffiGris("\n-----\n");
    sprintf(string,"Joueur : %s\n----\n",j.pseudo);
    AffiRose(string);
    AffiJaune("Nombre de parties jouées :");
    sprintf(string,"%d\n",j.nbpart);
    AffiBlancGras(string);
    AffiRouge("Pire score :");
    sprintf(string,"%d\n",Min(TabScore,j));
    AffiBlancGras(string);
    AffiVert("Meilleur score :");
    sprintf(string,"%d\n",TabScore[0]);
    AffiBlancGras(string);
    AffiBleu("Moyenne : ");
    sprintf(string,"%1.f\n",Moyenne(TabScore,j));
    AffiBlancGras(string);
    AffiGris("-----\n\n\n");
}

void AffichJoueurExistant(void){
    AffiRose("Affichage des joueurs existant :\n");
    char** tab;
    int ind,taille;
    tab=chargeJoueurs(&taille);
    for(ind=0;ind<taille;ind++){
        printf("%s\n",tab[ind]);
    }
    printf("\n");
}

void ListeParNom(Joueur j){
    AffiRose("Affichage des joueurs trié par nom :\n");
    char** tab;
    int ind,taille;
    tab=chargeJoueurs(&taille);
    for(ind=0;ind<taille;ind++){
        if(strcmp(j.pseudo,tab[ind])==0)AffiBleu(j.pseudo);
        else printf("%s",tab[ind]);
        printf("\n");
    }
    printf("\n");
}

void ListeParScore(Joueur j){
    AffiRose("Affichage des joueurs trié par score :\n");  
    char** tabNom;
    Joueur joueur;
    int *tabScoreJoueur,*tabScoreGlobal,max,maxj,passe=0,nbjoueur,ind;
    tabScoreJoueur=chargeScore(&j);
    maxj=tabScoreJoueur[0];
    tabNom=chargeJoueurs(&nbjoueur);
    tabScoreGlobal=(int*)malloc(nbjoueur*sizeof(int));
    for(ind=0;ind<nbjoueur;ind++){
        strcpy(joueur.pseudo,tabNom[ind]);
        tabScoreJoueur=chargeScore(&joueur);
        max=tabScoreJoueur[0];
        free(tabScoreJoueur);
        tabScoreGlobal[ind]=max;
    }
    for(ind=0;ind<nbjoueur;ind++){
        max=indMax(tabScoreGlobal,nbjoueur);
        if(strcmp(j.pseudo,tabNom[max])==0){
            AffiBleu(j.pseudo);
            printf(" : %d\n",tabScoreGlobal[max]);
        }
        else printf("%s : %d\n",tabNom[max],tabScoreGlobal[max]);
        tabScoreGlobal[max]=-1;
    }
    free(tabScoreGlobal);
    printf("\n");
}
void afficheTab(int Tab[],int taille){
    int i;
    for(i=0;i<taille;i++){
        printf("%d\t",Tab[i]);
    }
    printf("\n");
}

void Bienvenue(void){
    AffiViolet(" BBBB  III  EEEEE  N   N  V   V  EEEEE  N   N  U   U  EEEEE  !!\n");
    AffiViolet(" B   B  I   E      NN  N  V   V  E      NN  N  U   U  E      !!\n");
    AffiViolet(" BBBBB  I   EEEE   N N N  V   V  EEEE   N N N  U   U  EEEE   !!\n");
    AffiViolet(" B   B  I   E      N  NN  V   V  E      N  NN  U   U  E        \n");
    AffiViolet(" BBBB  III  EEEEE  N   N   VVV   EEEEE  N   N  UUUUU  EEEEE  !!\n\n\n");

}


int Menu(void){
    char choix[200];
    AffiViolet("|-_-_-_-_-_-|Menu|-_-_-_-_-_-|\n");
    AffiJaune("\t 1. Jouer une partie prédéfinie\n");
    AffiJaune("\t 2. Afficher la liste des joueurs triée par nom\n");
    AffiJaune("\t 3. Afficher la liste des joueurs triée par meilleur score\n");
    AffiJaune("\t 4. Afficher les statistiques d'un joueur\n");
    AffiJaune("\t 5. Afficher vos statistiques\n");
    AffiJaune("\t 6. Changer de joueur\n");
    AffiGris("\t 9. Quitter\n");
    AffiViolet("|-_-_-_-_-_-_-_-_-_-_-_-_-_-|\n");
    AffiBlancGras("Choix : ");
    fgets(choix,200,stdin);
    while(choix[0]!='1' && choix[0]!='2' && choix[0]!='3' && choix[0]!='4'&& choix[0]!='5' && choix[0]!='6' && choix[0]!='9'){
        AffiBlancGras("Votre choix n'était pas bon, réessayez : ");
        fgets(choix,200,stdin);
    }
    printf("\n");
    return ((int)choix[0]-48);
}




void Sortie(Joueur j){
    AffiViolet("Merci d'avoir jouer, à la prochaine fois !\n");
    exit(0);
}

void finPartie(Joueur j){
    char string[70];
    if (j.pdv<=0)AffiRouge("\n Vous êtes mort .... \n\n");
    else AffiVert("\n Vous avez Gagné la partie !! \n\n");
    sprintf(string,"Enregistrement de la Partie avec votre score : %d points\n",j.score);
    AffiGris(string);
    sauvegarderNvScore(j,j.score);
    AffiGris("Enregistré !\n\n\n");
}

void Partie(Joueur j){
    char* nomFich; 
    nomFich=demanderPartie();
    FileN partie;
    partie=chargerPartie(nomFich);
    while (!estVide(partie) && j.pdv>0){
        if(partie.tete==NULL){
            printf("est égale à null\n\n");
        }
        executNiveau(&j,partie.tete);
        partie=supprT(partie);

    }
    finPartie(j);
}

Monstre creerMonstre(Niveau* niv,int num){
    Monstre m;
    m.num=num;
    m.niv=niv->nivM;
    if (niv->nivM==1){
        m.nbDeg=1;
        strcpy(m.nom,"Petit Poulet \0");
        m.pdv=4;
    }
    if (niv->nivM==2){
        m.nbDeg=1;
        strcpy(m.nom,"Poulet \0");
        m.pdv=6;
    }
    if (niv->nivM==3){
        m.nbDeg=2;
        strcpy(m.nom,"Chevalier Poulet \0");
        m.pdv=4;
    }
    return m;
}

void ChoixBonus(Joueur* j){
    char string[40],choix[30];
    AffiJaune("\nVous avez gagner la manche, choisissez un bonus :\n");
    AffiBleu("|1)--> Se soigner de 5 pdv\n|2)--> Faire 1 point de dégat supplémentaire\n");
    AffiBlancGras("Choix : ");
    fgets(choix,30,stdin);
    while(choix[0]!='1' && choix[0]!='2'){
        AffiBlancGras("Votre choix n'était pas bon, recommence : ");
        fgets(choix,30,stdin);
    }
    printf("\n");
    if(choix[0]=='1')j->pdv=j->pdv+5;
    else j->nbDeg=j->nbDeg+1;
}



int executNiveau(Joueur *j,Niveau* niv){
    int ind,numM=1,ajtscore,numMmax;
    char string[200];
    Monstre m;
    FileM f;
    f=NULL;
    if (strcmp(niv->lieu,"coul")==0){
        sprintf(string,"\n\nVous arrivez dans un couloir, %d monstres de niveau %d apparaissent, vous allez les combattres 1 par 1 !\n",niv->nbrM,niv->nivM);
        AffiViolet(string);
        for( ind=0 ; ind < niv->nbrM ; ind++){
            m=creerMonstre(niv,numM);
            while(j->pdv>0 && m.pdv>0 ){
                Resultat(j,&m);
            }
            if (m.pdv<=0){
                sprintf(string,"---------------------------- Le monstre %s%d est mort ! ----------------------------\n\n",m.nom,m.num);
                AffiVert(string);
                ajtscore=Score(m,'C');
                j->score=j->score+ajtscore;
                sprintf(string,"-- Vous gagnez %d points grâce à ce monstre ! \nVos points : %d \n\n",ajtscore,j->score);
                AffiViolet(string);
                numM=numM+1;
            }
            else return -1;
        }
    }
    else{
        sprintf(string,"\n\nVous arrivez dans une plaine, %d monstres de niveau %d apparaissent, vous allez les combattres en même temps !!\n",niv->nbrM,niv->nivM);
        AffiViolet(string);
        for( ind=0 ; ind < niv->nbrM ; ind++){
            m=creerMonstre(niv,numM);
            numM=numM+1;
            f=ajdqMonstre(f,m);
        }
        while(!estVideFmonstre(f)){
            Resultat(j,&f->suiv->m);
            if (f->suiv->m.pdv<=0){
                sprintf(string,"---------------------------- Le monstre %s%d est mort ! ----------------------------\n\n",f->suiv->m.nom,f->suiv->m.num);
                AffiVert(string);
                ajtscore=Score(f->suiv->m,'P');
                j->score=j->score+ajtscore;
                sprintf(string,"-- Vous gagnez %d points grâce à ce monstre ! \nVos points : %d \n\n",ajtscore,j->score);
                AffiViolet(string);
                f=supprTMonstre(f);
            }
            else{
                f=ajdqMonstre(f,f->suiv->m);
                f=supprTMonstre(f);
            }
            if(j->pdv<=0) return -1;
            
        }
    }
    ChoixBonus(j);
    return 0;
}

void Lancement(Joueur *j){
    int choix;
    choix=Menu();
    if (choix==9) Sortie(*j);
    if (choix==1) Partie(*j);
    if (choix==2) ListeParNom(*j);
    if (choix==3) ListeParScore(*j);
    if (choix==4) StatJoueur();
    if (choix==5) AffichStatJoueur(*j);
    if (choix==6){strcpy(j->pseudo,DemandePseudo()); inititJoueur(j->pseudo);}
}

void StatJoueur(void){
    Joueur j;
    bool exist;
    AffichJoueurExistant();
    AffiJaune("Quel est le nom du chevalier que dont vous voulez consulter les statistiques ? :");
    fgets(j.pseudo,21,stdin);
    j.pseudo[strlen(j.pseudo)-1]='\0';
    exist=verifJoueur(j);
    if(exist){
        AffichStatJoueur(j);
        return;
    }
    AffiRouge("Le joueur n'existe pas ...\n\n");
    
}

char* DemandePseudo(void){
    char* pseudo,string[200],choix[10];
    pseudo=(char*)malloc(21*sizeof(char));
    if(pseudo==NULL){
        AffiRouge("PB de malloc pour le pseudo ...");
        exit(1);
    }
    AffiJaune("Bonjour Chevalier, quel est votre nom de chevalier (taile max de 20)? :");
    fgets(pseudo,21,stdin);
    pseudo[strlen(pseudo)-1]='\0';
    AffiJaune("Votre nom de joueur est : ");
    AffiBleu(pseudo);
    AffiJaune(", êtes vous certain que ce soit bon ? (O/N) : ");
    fgets(choix,10,stdin);
    while(choix[0]!='O'){
        AffiJaune("Bonjour Chevalier, quel est votre nom de chevalier (taile max de 20)? :");
        fgets(pseudo,21,stdin);
        pseudo[strlen(pseudo)-1]='\0';
        AffiJaune("Votre nom de joueur est : ");
        AffiBleu(pseudo);
        AffiJaune(", êtes vous certain que ce soit bon ? (O/N) : ");
        fgets(choix,10,stdin); 
    }
    return pseudo;
}

int ChoixArmeJ(Joueur j){
    char string[40],arme[200];
    sprintf(string,"%s , %d pdv (%dpts) : \n",j.pseudo,j.pdv,j.score);
    AffiRose(string);
    AffiJaune("Choisis ton arme Parmis P,F,C (Pierre\\Feuille\\Ciseaux)\n(seule la 1ere lettre donnée sera prise en compte) : ");
    fgets(arme,30,stdin);
    while(arme[0]!='C' && arme[0]!='F' && arme[0]!='P'){
        AffiJaune("Aucune arme de ce style, réessayez parmis P,F,C : ");
        fgets(arme,200,stdin);
    }
    if(arme[0]=='P')return Pierre;
    if(arme[0]=='F')return Feuille;
    return Ciseaux;
}

int ArmeMonstre(int niveau){
    int ran;
    if(niveau==1)ran=rand()%4+1;
    if(niveau==2)ran=rand()%3+1;
    if(niveau==3)ran=rand()%5+1;
    if(ran==1)return Pierre;
    if(ran==2)return Feuille;
    if(ran==3)return Ciseaux;
    if(ran==4)return BonARien;
    if(ran==5)return Pouvoir;
    return ran;
}

int Combat(Joueur j,Monstre m){
    int armeJ,armeM;
    char string[100];
    armeJ=ChoixArmeJ(j);
    armeM=ArmeMonstre(m.niv);
    if(armeM==armeJ){
        sprintf(string,"Le monstre (%s%d)-> %dpdv a choisi la même arme !!\n",m.nom,m.num,m.pdv);
        AffiViolet(string);
        return 2;
    }
    sprintf(string,"Le monstre (%s%d)-> %dpdv a choisi l'arme : ",m.nom,m.num,m.pdv);
    AffiViolet(string);
    if(armeM==Pouvoir){AffiBleu("Magique\n");return 0;}
    if(armeM==Pierre){
        AffiBleu("Pierre\n");
        if (armeJ==Ciseaux)return 0;}
    if(armeM==Feuille){
        AffiBleu("Feuille\n");
        if(armeJ==Pierre)return 0;}
    if(armeM==Ciseaux){
        AffiBleu("Ciseaux\n");
        if(armeJ==Feuille)return 0;}
    if(armeM==BonARien)AffiBleu("bonne à rien\n");
    return 1;
}

int Score(Monstre m,char groupe){
    if(groupe == 'C')return 50*m.niv;
    return 100*m.niv;
}

void Resultat(Joueur *j,Monstre* m){
    int result,score;
    char string[100];
    result=Combat(*j,*m);
    if (result==2)AffiRouge("Egalité !\n\n\n");
    else {if (result==1){
                j->score=j->score+10;
                m->pdv=m->pdv-j->nbDeg;
                AffiVert("Attaque gagnée !\t\t\t\t(+10pts)\n");
                sprintf(string,"Le monstre (%s%d) n'a plus que %dpdv\n\n\n",m->nom,m->num,m->pdv);
                AffiViolet(string);
            }
            else{ 
                j->pdv=j->pdv-m->nbDeg;
                sprintf(string,"Attaque perdue.. \t\t\t\t(-%dpdv)\n",m->nbDeg);
                AffiRouge(string);
                sprintf(string,"Vous n'avez plus que %d pdv\n\n\n",j->pdv);
                AffiViolet(string);
            }
        }
}

void jeu(void){
    char armes[5]={'C','P','F','O','#'};
    int score,typeMonstre;
    FileN FilMonstres;
    Monstre *TabMonstres[50];
    
}

int trouverPositionInsertionScore(int *scores, int nb_scores, int nouveau_score) {
    for (int i = 0; i < nb_scores; i++) {
        if (nouveau_score > scores[i]) {
            return i;
        }
    }
    return nb_scores;
}

void AjoutNouvJoueur(Joueur j) {
    FILE *fichier;
    bool exist;
    char nomFich[40];
    sprintf(nomFich,"joueurs/%s.txt",j.pseudo);
    exist=verifJoueur(j);
    if(!exist){
        fichier = fopen(nomFich,"w");
        fprintf(fichier,"0\n");
        fclose(fichier);
        ajouterJoueur(j);
    }
}

void sauvegarderNvScore(Joueur j, int nouveau_score) {
    char nomFich[50];
    int MAX_SCORES=100;
    FILE *fichier;
    sprintf(nomFich,"joueurs/%s.txt",j.pseudo);
    fichier = fopen(nomFich, "r+");
    if (fichier == NULL) {
        fclose(fichier);
        fichier = fopen(nomFich, "w");
        fprintf(fichier,"1\n");
        fprintf(fichier,"%d\n",nouveau_score);
        fclose(fichier);
        return;
    }

    int nb_parties;
    if (fscanf(fichier, "%d", &nb_parties) != 1) { // erreur si elle lit plusieurs nombres
        printf("Erreur : format de fichier incorrect.\n");
        fclose(fichier);
        return;
    }

    int scores[MAX_SCORES];
    int nb_scores = 0;

    while (fscanf(fichier, "%d", &scores[nb_scores]) == 1 && nb_scores < MAX_SCORES) {
        nb_scores++;
    }

    int position;
    position = trouverPositionInsertionScore(scores, nb_scores, nouveau_score);

    for (int i = nb_scores; i > position; i--) {
        scores[i] = scores[i - 1];
    }
    scores[position] = nouveau_score;
    nb_scores++;
    nb_parties++;
    fseek(fichier, 0, SEEK_SET);
    fprintf(fichier, "%d\n", nb_parties);
    for (int i = 0; i < nb_scores; i++) {
        fprintf(fichier, "%d\n", scores[i]);
    }

    fclose(fichier);
}


char* demanderPartie(void) { 
    char choix[200],*nomFich;
    int choixint;
    nomFich=(char*)malloc(30*sizeof(char));
    if (nomFich == NULL) {
        printf("Erreur : Allocation mémoire échouée.\n");
        free(nomFich);
        exit(1);
    }
    printf("Veuillez choisir le niveau de la partie (1, 2, 3, ou 4) : ");
    fgets(choix,200,stdin);
    choixint=(int)choix[0]-48;
    while(choixint>4 || choixint<1){
        AffiBlancGras("Choix invalide. Veuillez entrer un nombre entre 1 et 4 :");
        fgets(choix,200,stdin);
        choixint=(int)choix[0]-48;
    }
    sprintf(nomFich, "partie%d.txt", choixint);
    return nomFich;
}

Joueur inititJoueur(char *pseudo) {
    Joueur j;
    int score=0,nbpart=0;
    strncpy(j.pseudo, pseudo, 20);
    j.pseudo[20] = '\0';
    j.pdv = 20;
    j.nbDeg = 1;
    chargeScore(&j);
    j.score = 0;
    return j;
}




void global(void) {
    Bienvenue();
    srand(time(NULL));
    Joueur j;
    AffichJoueurExistant();
    strcpy(j.pseudo,DemandePseudo());
    int choix=0;
    AjoutNouvJoueur(j);
    AffiRouge("\n\nA partir d'ici, les réponses attendues sont en MAJUSCULE !\n\n");
    while(true){
        j = inititJoueur(j.pseudo);
        Lancement(&j);
    }
}