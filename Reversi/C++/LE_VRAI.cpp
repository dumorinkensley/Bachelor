#include <iostream>
using namespace std;
#include<stdlib.h>

/******************************
*      VARIABLES GLOBALES     *
******************************/

//COULEURS
#define BLANC 'B'
#define NOIR  'N'
#define GRIS  'G'
#define VIDE  'V'

//JOUEURS
string j1, j2;
char c_j1=NOIR, c_j2=BLANC;
int IA1=0, IA2=0;

//JEU
char grille[8][8];
char test[8][8];

//ERREURS
#define OK 0
#define ERR_SAISIE -1
#define ERR_IMPOSSIBLE -2
#define ERR -3

// DEFINITIONS

void Calcul_Test(){
    int i=0;
    int j;
    int shift_lig;
    int shift_col;
    int a;
    int b;
    int k;
    int ik;
    int jk;

    /**  Initialise la variable de test  **/
    while (i<8){
        j=0;
        while (j<8){
            test[i][j]=VIDE;
            j=j+1;
        }
        i=i+1;
    }

    /**  Parcours la feuille de test  **/
    i=0;
    while (i<8){
        j=0;
        while (j<8){
            if (grille[i][j]!=VIDE or test[i][j]==GRIS){
                j=j+1;
                continue;
            }

            /**  test de posibilité  **/
            shift_lig=-1;
            while (shift_lig<=1){
                shift_col=-1;
                while (shift_col<=1){
                    /**  (shift_lig,shift_col) représente la direction de l'analyse  **/
					/**  (-1,-1) = en haut à gauche  **/
					/**  (-1,0) = en haut  **/
					/**  (-1,1) = en haut à droite  **/
					/**  (0,-1) = à gauche  **/
					/**  (0,1) = à droite  **/
					/**  (1,-1) = en bas à gauche  **/
					/**  (1,0) = en bas  **/
					/**  (1,1) = en bas à droite  **/

                    /**  Cas a exclure  **/
                    if (shift_lig==0 and shift_col==0){
                        shift_col=shift_col+1;
                        continue;
                    }
                    if (i+shift_lig <0 or i+shift_lig>=8){
                        shift_col=shift_col+1;
                        continue;
                    }
                    if (j+shift_col <0 or j+shift_col>=8){
                        shift_col=shift_col+1;
                        continue;
                    }

                    a=grille[i+shift_lig][j+shift_col];

                    /**  S'il n'y a pas de pion à coté on passe à autre chose  **/
                    if (a==VIDE){
                        shift_col=shift_col+1;
                        continue;
                    }

                    /**  Inversion des couleurs  **/
                    if (a==NOIR) {
                        b=BLANC;
                    }
                    if (a==BLANC){
                        b=NOIR;
                    }

                    k=1;
                    /**  Une fois la direction choisi on va voir si on croise un jeton de couleur différente  **/
                    while (i+shift_lig*k>=0 and i+shift_lig*k<8 and j+shift_col*k>=0 and j+shift_col*k<8 and grille[i+shift_lig*k][j+shift_col*k]==a){
                        k=k+1;
                    }

                    /**  Si on est sortie de la boucle parce qu'on a rencontré un jeton de couleur différente (b) alors le placement est possible  **/
                    if (i+shift_lig*k>=0 and i+shift_lig*k<8 and j+shift_col*k>=0 and j+shift_col*k<8 and grille[i+shift_lig*k][j+shift_col*k]==b){
                        if (test[i][j]==a) test[i][j]=GRIS;

                        else test[i][j]=b;
                    }
                    shift_col=shift_col+1;
                }
                shift_lig=shift_lig+1;
            }
            j=j+1;
        }
        i=i+1;
    }
}

void Init(){
	int i=0;
	int j;

	while(i<8){
		j=0;
		while(j<8){
			grille[i][j]=VIDE;
			j=j+1;
        }
		i=i+1;
	}
	grille[3][3]=BLANC;
	grille[3][4]=NOIR;
	grille[4][3]=NOIR;
	grille[4][4]=BLANC;

	Calcul_Test();
}

int Compte_Couleur(char c){
    int i=0;
    int j;
    int res=0;

    while(i<8){
        j=0;
        while(j<8){
            if(grille[i][j]==c) res=res+1;
            j=j+1;
        }
        i=i+1;
    }

    return res;
}

void Plateau(){

    char luc=218,    //left up corner
         ruc=191,    //right up corner
         lbc=192,    //left bottom corner
         rbc=217,    //right bottom corner
         hl=196,     //horizontal line
         vl=179,     //vertical line
         tu=194,     //t up
         tb=193,     //t bottom
         tl=195,     //t left
         tr=180,     //t right
         tm=197,     //t middle
         esp=' ',  //espace
         tab='\t'; //tabulation

    cout << endl;

    cout << tab << esp;
    for(int i=0 ; i<8 ; i++) cout << esp << (char)('A'+i) << esp << esp ;
    cout << endl << endl;

    cout << tab << luc;
    for(int i=0 ; i<8 ; i++) cout << hl << hl << hl << tu ;
    cout << "\b" << ruc;
    cout << tab << " .:REVERSI:." << endl;

    for(int i=0 ; i<8 ; i++){
        cout << esp << esp << esp << (i+1) << tab;
        for(int j=0 ; j<8 ; j++){
            cout << vl << esp ;
            switch(grille[i][j]){
            case(BLANC) : cout << (char)2; break;
            case(NOIR)  : cout << (char)1; break;
            default     : cout << esp;
            }
            cout << esp;
        }
        cout << vl << endl;

        cout << tab;
        cout << tl;
        for(int j=0 ; j<8 ; j++) cout << hl << hl << hl << tm;
        cout << "\b" << tr;

        switch(i) {
        case(0) : cout << tab << (char)184 << "  IUT - S2R  ";break;
        case(2) : cout << tab << (char) 1 << " : " << Compte_Couleur(NOIR);
                  cout << tab << (char) 2 << " : " << Compte_Couleur(BLANC);
                  break;
        case(4) : if(c_j1 == NOIR){
                       cout << tab << (char)1 << esp << j1;
                  }
                  else{
                       cout << tab << (char)1 << esp << j2;
                  }
                  break;
        case(5) : if(c_j1 == NOIR){
                       cout << tab << (char)2 << esp << j2;
                  }
                  else{
                       cout << tab << (char)2 << esp << j1;
                  }
                  break;

        }

        if(i!=7) cout << endl;
    }

    cout << "\r";
    cout << tab << lbc;
    for(int i=0 ; i<8 ; i++) cout << hl << hl << hl << tb ;
    cout << "\b" << rbc << tab;

}

bool Fin(){
    int i=0;
    int j;

    while (i<8){
        j=0;
        while (j<8){
            if (test[i][j]!=VIDE) return false;
            j=j+1;
        }
        i=i+1;
    }
    return true;
}

bool Test_Tour(char c){
    int i=0;
    int j;

    while(i<8){
        j=0;
        while(j<8){
            if(test[i][j]==c or test[i][j]==GRIS) return true;
            j=j+1;
        }
        i=i+1;
    }
    return false;
}

void Placement(int lig, int col, char c){

    char a;
    int k;

    //Positionnement du pion
    grille[lig][col] = c;

    //Retournement des pions
    //Le principe des deux shift est le même que pour la fonction calcul_test
    for(int shift_lig=-1 ; shift_lig<=1 ; shift_lig++){
        for(int shift_col=-1 ; shift_col<=1 ; shift_col++){

            if(shift_lig==0 and shift_col==0) continue;
            if(lig+shift_lig <0 or lig+shift_lig>=8) continue;
            if(col+shift_col <0 or col+shift_col>=8) continue;

            a=grille[lig+shift_lig][col+shift_col];
            if(a==c) continue;
            if(a==VIDE) continue;

            k=1;
            while(lig+shift_lig*k>=0 and lig+shift_lig*k<8 and
                  col+shift_col*k>=0 and col+shift_col*k<8 and
                  grille[lig+shift_lig*k][col+shift_col*k]==a) k++;

            if (lig+shift_lig*k>=0 and lig+shift_lig*k<8 and
                col+shift_col*k>=0 and col+shift_col*k<8 and
                grille[lig+shift_lig*k][col+shift_col*k]==c){
                k=1;
                while(grille[lig+shift_lig*k][col+shift_col*k]!=c){
                    grille[lig+shift_lig*k][col+shift_col*k]=c;
                    k++;
                }
            }
        }
    }

    //Calcul de la feuille de test
    Calcul_Test();
}

int Placer(char c, int IA){

    int lig=0,col=0;
    int t=-64, cmpt;
    char d;
    bool b;
    char grille_sav1[8][8], grille_sav2[8][8];
    char test_sav1[8][8], test_sav2[8][8];


    switch(IA){
    case 1 : //NOETHER IA FACILE
        //On choisi une place au hasard parmi les places possibles

        //On compte le nombre de casse true
        cmpt=0;
        b=false;

        for(int i=0 ; i<8 ; i++){
            for(int j=0; j<8 ; j++){
                if(test[i][j]==c or test[i][j]==GRIS) cmpt++;
            }
        }
        if(cmpt==0) return ERR_IMPOSSIBLE;

        //On choisi une case true au hasard
        t=( (rand()+0.0)/(RAND_MAX+1) )*cmpt;
        cmpt=0;
        for(int i=0 ; i<8 and b==false ; i++){
            for(int j=0; j<8 and b==false ; j++){
                if(test[i][j]==c or test[i][j]==GRIS) cmpt++;
                if(cmpt>t) {
                    b=true;
                    lig = i;
                    col = j;
                }
            }
        }
        break;
    case 2 ://ABEL IA MOYEN
        //On choisi la place qui fait gagner le plus de point

        //On créer une copie de grille et de test
        for(int i=0 ; i<8 ; i++){
            for(int j=0 ; j<8 ; j++){
                grille_sav1[i][j]=grille[i][j];
                test_sav1[i][j]=test[i][j];
            }
        }

        //Pour chaque case possible on place et on calcul les points
        for(int i=0 ; i<8 ; i++){
            for(int j=0 ; j<8 ; j++){
                if(test[i][j]==c or test[i][j]==GRIS){
                    Placement(i, j, c);
                    if(Compte_Couleur(c)>t){
                        lig=i; col=j ; t=Compte_Couleur(c);
                    }

                    //On remet la grille en l'etat
                    for(int i1=0 ; i1<8 ; i1++){
                        for(int j1=0 ; j1<8 ; j1++){
                            grille[i1][j1] = grille_sav1[i1][j1];
                            test[i1][j1] = test_sav1[i1][j1];
                        }
                    }
                }//Fin if
            }
        }
        break;
    case 3 ://GROTHENDIECK IA DIFFICILE
        //On choisi la place qui fait gagner le plus de point au joueur et le moins de point a l'autre

        //On créer une copie de grille et de test
        for(int i=0 ; i<8 ; i++){
            for(int j=0 ; j<8 ; j++){
                grille_sav1[i][j]=grille[i][j];
                test_sav1[i][j]=test[i][j];
            }
        }

        if(c==NOIR) d=BLANC;
        else d=NOIR;

        b=false;
        for(int i=0 ; i<8 ; i++){
            for(int j=0 ; j<8 ; j++){
                if(test[i][j]==c or test[i][j]==GRIS){
                    Placement(i, j, c);

                    //Création d'une nouvelle copie
                    for(int i1=0 ; i1<8 ; i1++){
                        for(int j1=0 ; j1<8 ; j1++){
                            grille_sav2[i1][j1]=grille[i1][j1];
                            test_sav2[i1][j1]=test[i1][j1];
                        }
                    }

                    for(int i1=0 ; i1<8 ; i1++){
                        for(int j1=0 ; j1<8 ; j1++){
                            if(test[i1][j1]==d or test[i1][j1]==GRIS){
                                Placement(i1,j1,d);
                                b=true;
                                if(Compte_Couleur(c)-Compte_Couleur(d)>t){
                                    t = Compte_Couleur(c)-Compte_Couleur(d);
                                    lig = i; col = j;
                                }

                                //On remet la grille a l'état d'avant
                                for(int i2=0 ; i2<8 ; i2++){
                                    for(int j2=0 ; j2<8 ; j2++){
                                        grille[i2][j2]=grille_sav2[i2][j2];
                                        test[i2][j2]=test_sav2[i2][j2];
                                    }
                                }

                            }//Fin if i1
                        }
                    }

                    //On remet la grille a l'état d'avant
                    for(int i1=0 ; i1<8 ; i1++){
                        for(int j1=0 ; j1<8 ; j1++){
                            grille[i1][j1]=grille_sav1[i1][j1];
                            test[i1][j1]=test_sav1[i1][j1];
                        }
                    }
                }//Fin if i
            }
        }

        if(b==false) return Placer(c,2);

        //Les coins sont stratégiques
        if(test[0][0]==c or test[0][0]==GRIS) {lig=0 ; col=0;}
        if(test[0][7]==c or test[0][7]==GRIS) {lig=0 ; col=7;}
        if(test[7][0]==c or test[7][0]==GRIS) {lig=7 ; col=0;}
        if(test[7][7]==c or test[7][7]==GRIS) {lig=7 ; col=7;}

        break;
    default :

        string place;

        cout << "\n\t\t Saisir la position : ";
        cin >> place;

        /****  SAISIE 3.0  ****/
        //Si 2 lettre ou 2 chiffre return Erreur
        if(place.size()!=2) return ERR_SAISIE;
        if ((place[0]>='a' and place[0]<='h' and place[1]>='a' and place[1]<='h' and place[1]>='A' and place[1]<='H') or
            (place[0]>='A' and place[0]<='H' and place[1]>='A' and place[1]<='H' and place[1]>='a' and place[1]<='h') or
            (place[0]>='1' and place[0]<='8' and place[1]>='1' and place[1]<='8')) return ERR_SAISIE;

        // ex: saisie: 6g = G6, Ici l'ordre importe peu quand on saisie
        if ((place[0]>='a' and place[0]<='h') or (place[0]>='A' and place[0]<='H')){
            if (place[0]>='a' and place[0]<='h') col=place[0]-'a';
            else col=place[0]-'A';
        }
        else if ((place[1]>='a' and place[1]<='h') or (place[1]>='A' and place[1]<='H')){
            if (place[1]>='a' and place[1]<='h') col=place[1]-'a';
            else col=place[1]-'A';
        }
        if (place[0]>='1' and place[0]<='8') lig=place[0]-'1';
        else if (place[1]>='1' and place[1]<='8') lig=place[1]-'1';
    }

    if(not(lig<8 and lig>=0 and col<8 and col>=0)) return ERR_SAISIE;
    if(not(test[lig][col]==c or test[lig][col]==GRIS) ) return ERR_IMPOSSIBLE;

    Placement(lig, col, c);
    return OK;
}

void affiche_menu (){
    /****  AFFICHAGE  ****/
    system("cls");
    cout << "\n\t\t\t\t REVERSI";
    cout << "\n\n\t\t 1. Jeu a deux joueurs humains";
    cout << "\n\t\t 2. Jouer contre l'ordinateur";
    cout << "\n\t\t 3. Voir l'ordinateur jouer contre elle meme";
    cout << "\n\t\t 4. Regle du jeu";
    cout << "\n\t\t 5. STOP";
    cout << "\n\n\t\t\t Choix : ";
}

int choix_1 (){
    /** Nom des joueurs **/
    system("cls");
    cout << "\n\t\t\t\t REVERSI\n\n";
    cout << "\t\t Nom du joueur 1 (NOIR) : ";
    cin >> j1;
    cout << "\n\t\t Nom du joueur 2 (BLANC) : ";
    cin >> j2;

    /** INITIALISE LES JOUEURS **/
    IA1=0; // Joueur 1 humain
    IA2=0; // Joueur 2 humain

    return IA1,IA2;
}

void choix_4 (){
    system("cls");
    cout << "\n\t\t\t\t REVERSI\n";
    cout << "\n\t REGLE DU JEU\n";
    cout << "\n - le joueur doit poser un pion de sa couleur";
    cout << "\n   sur une case vide du tableau,";
    cout << "\n   adjacente a un pion adverse.\n";
    cout << "\n - Il doit egalement, en posant son pion,";
    cout << "\n   encadrer un ou plusieurs pions adverses entre";
    cout << "\n   le pion pose et le pion de sa couleur,";
    cout << "\n   deja place sur le tableau.\n\n";
    system("pause");
}

void choix_5(){
    system("cls");
    cout << "\n\t\t\t\t REVERSI\n\n";
    cout << "\n\t\t ***************************************";
    cout << "\n\t\t *                                     *";
    cout << "\n\t\t *   AU REVOIR, A UNE PROCHAINE FOIS ! *";
    cout << "\n\t\t *                                     *";
    cout << "\n\t\t ***************************************\n\n";
}


/***************************
*          MAIN            *
****************************/
int main()
{
    /** DECLARATIONS **/
    string choix="test";
    int switch_IA;
    string switch_j;
    char switch_c;
    string c;
    int adversaire_1;
    int adversaire_2;

    /** PETIT DEBUT **/
    cout << "\n\n\n\t\t\t ***************************";
    cout << "\n\t\t\t *                         *";
    cout << "\n\t\t\t *  BIENVENUE SUR REVERSI  *";
    cout << "\n\t\t\t *                         *";
    cout << "\n\t\t\t ***************************\n\n";
    system("pause");

    /** MENU PRINCIPALE **/
    while (choix[0]!='5'){

        //----------Faire un choix
        system("cls");
        affiche_menu();
        cin >> choix;

        //----------Resaisir si le choix n'existe pas
        while (choix.size()>1 or choix.size()<0 or choix[0]<'1' or choix[0]>'5'){
            system("cls");
            affiche_menu();
            cin >> choix;
            if (choix.size()>1 or choix.size()<0 or choix[0]<'1' or choix[0]>'5'){
                cout << "\n Je n'ai pas compris votre demande\n";
                system("pause");
            }
        }

        //----------Si choix taper sont : 1, 2, 3
        if (choix[0]=='1' or choix[0]=='2' or choix[0]=='3'){

            //----------Choix 1
            if (choix[0]=='1'){
                choix_1();

                switch_IA=IA1;
                switch_c=c_j1;
                switch_j=j1;
            }

            //----------Choix 2
            if (choix[0]=='2'){
                system("cls");
                cout << "\n\t\t\t\t REVERSI\n\n";
                cout << "\t\t Nom du joueur : ";
                cin >> j1;
                cout << "\n\t\t Couleur du joueur (N pour noir, B pour blanc): ";
                cin >> c;

                //----------Resaisie couleur si elle n'existe pas
                while (c.size()!=1){
                    if (c[0]=='N') break;
                    if (c[0]=='n') break;
                    if (c[0]=='B') break;
                    if (c[0]=='b') break;
                    system("cls");
                    cout << "\n\t\t\t\t REVERSI\n\n";
                    cout << "\t\t Nom du joueur : " << j1;
                    cout << "\n\n\t\t Couleur du joueur (N pour noir, B pour blanc): ";
                    cin >> c;
                }

                cout << "\n\t\t Choix de l'adversaire : ";
                cout << "\n\t\t\t 1.Elicaf";
                cout << "\n\t\t\t 2.Neyom";
                cout << "\n\t\t\t 3.Eliciffid";
                cout << "\n\n\t\t\t\t Choix de votre adversaire : ";
                cin >> adversaire_1;

                // Resaisie si ce n'est pas 1, 2 ou 3
                while (adversaire_1>3 or adversaire_1<1){
                    system("cls");
                    cout << "\n\t\t\t\t REVERSI\n\n";
                    cout << "\t\t Nom du joueur : " << j1;
                    cout << "\n\n\t\t Couleur du joueur (N pour noir, B pour blanc): " << c;
                    cout << "\n\n\t\t Choix de l'adversaire : ";
                    cout << "\n\t\t\t 1.Elicaf (facile)";
                    cout << "\n\t\t\t 2.Neyom (moyen)";
                    cout << "\n\t\t\t 3.Eliciffid (difficile)";
                    cout << "\n\n\t\t\t\t Choix de votre adversaire : ";
                    cin >> adversaire_1;
                }

                //  Un nom pour l'adversaire selon le niveau
                if (adversaire_1==1) j2="Elicaf" ;
                if (adversaire_1==2) j2="Neyom" ;
                if (adversaire_1==3) j2="Eliciffid" ;

                //  Si joueur c=NOIR alors il est le joueur 1. Joueur 2 sinon
                if (c[0]=='N' or c[0]=='n'){
                    IA1=0;
                    IA2=adversaire_1;
                    switch_IA=IA1;
                    switch_c=c_j1;
                    switch_j=j1;
                }
                else if (c[0]=='B' or c[0]=='b'){
                    IA1=adversaire_1;
                    IA2=0;
                    switch_IA=IA1;
                    switch_c=c_j2;
                    switch_j=j2;
                }

            }

            //----------Choix 3
            if (choix[0]=='3'){
                system("cls");
                cout << "\n\t\t\t\t REVERSI\n\n";
                cout << "\tChoix de L'IA noire : ";
                cout << "\n\t\t\t 1.Elicaf (facile)";
                cout << "\n\t\t\t 2.Neyom (moyen)";
                cout << "\n\t\t\t 3.Eliciffid (difficile)";
                cout << "\n\n\t\t\t\t Choix : ";
                cin >> adversaire_1;

                while (adversaire_1>3 or adversaire_1<1){
                    system("cls");
                    cout << "\n\t\t\t\t REVERSI\n\n";
                    cout << "\tChoix de L'IA noire : ";
                    cout << "\n\t\t\t 1.Elicaf (facile)";
                    cout << "\n\t\t\t 2.Neyom (moyen)";
                    cout << "\n\t\t\t 3.Eliciffid (difficile)";
                    cout << "\n\n\t\t\t\t Choix : ";
                    cin >> adversaire_1;
                }
                //  Un nom pour l'adversaire selon le niveau
                if (adversaire_1==1) j1="Elicaf" ;
                if (adversaire_1==2) j1="Neyom" ;
                if (adversaire_1==3) j1="Eliciffid" ;

                cout << "\tChoix de L'IA blanche : ";
                cout << "\n\t\t\t 1.Elicaf (facile)";
                cout << "\n\t\t\t 2.Neyom (moyen)";
                cout << "\n\t\t\t 3.Eliciffid (difficile)";
                cout << "\n\n\t\t\t\t Choix : ";
                cin >> adversaire_2;

                while (adversaire_2>3 or adversaire_2<1){
                    system("cls");
                    cout << "\n\t\t\t\t REVERSI\n\n";
                    cout << "\tChoix de L'IA noire : ";
                    cout << "\n\t\t\t 1.Elicaf (facile)";
                    cout << "\n\t\t\t 2.Neyom (moyen)";
                    cout << "\n\t\t\t 3.Eliciffid (difficile)";
                    cout << "\n\n\t\t\t\t Choix : " << adversaire_1;
                    cout << "\n\tChoix de L'IA blanche : ";
                    cout << "\n\t\t\t 1.Elicaf (facile)";
                    cout << "\n\t\t\t 2.Neyom (moyen)";
                    cout << "\n\t\t\t 3.Eliciffid (difficile)";
                    cout << "\n\n\t\t\t\t Choix : ";
                    cin >> adversaire_2;
                }
                // Un nom pour l'adversaire selon le niveau
                if (adversaire_2==1) j2="Elicaf" ;
                if (adversaire_2==2) j2="Neyom" ;
                if (adversaire_2==3) j2="Eliciffid" ;

                IA1=adversaire_1;
                IA2=adversaire_2;
                switch_IA=IA1;
                switch_c=c_j1;
                switch_j=j1;
            }

            //----------LANCEMENT DE LA PARTIE
            cout << "\n La partie va commencer ...\n\n";
            system("pause");
            system("cls");
            Init();
            while (Fin()==false){
                system("cls");
                Plateau();

                //----------SI UN JOUEUR NE PEUT PAS JOUER ON PASSE A L'AUTRE
                if (Test_Tour(switch_c)==false){
                    cout << "\n " << switch_j << " (" << switch_c << ")" << " ne peut pas jouer\n";
                    //----------CHANGE DE PARAMETRE  DU JOUEUR IA
                    if (switch_IA==IA1) switch_IA=IA2;
                    else if (switch_IA==IA2) switch_IA=IA1;
                    //----------CHANGE LE TOUR DU JOUEUR
                    if (switch_c==c_j1) switch_c=c_j2;
                    else if (switch_c==c_j2) switch_c=c_j1;
                    //----------CHANGE LE NOM DU JOUEUR
                    if (switch_j==j1) switch_j=j2;
                    else if (switch_j==j2) switch_j=j1;
                    system("pause");
                    system("cls");
                    Plateau();
                }

                //----------AFFICHE LE NOM DU JOUEUR JOUANT
                cout << "C'est a " << switch_j << " (" << switch_c << ")" << " de jouer ";

                //----------PLACE LES PIONS SAISIE
                Placer(switch_c,switch_IA);

                //----------Si il y a une erreur on recommence la saisie position

                //----------CHANGE DE PARAMETRE  DU JOUEUR IA
                if (switch_IA==IA1) switch_IA=IA2;
                else if (switch_IA==IA2) switch_IA=IA1;
                //----------CHANGE LE TOUR DU JOUEUR
                if (switch_c==c_j1) switch_c=c_j2;
                else if (switch_c==c_j2) switch_c=c_j1;
                //----------CHANGE LE NOM DU JOUEUR
                if (switch_j==j1) switch_j=j2;
                else if (switch_j==j2) switch_j=j1;

                //----------ARRETE LA PARTIE 0 PIONS D'UNE COULEUR OU PLUS PERSONNE PEUT JOUER
                if (Compte_Couleur(BLANC)==0 or Compte_Couleur(NOIR==0) or (Test_Tour(BLANC)==false and Test_Tour(NOIR)==false)) break;
            }

            //----------PARTIE TERMINER
            system("cls");
            Plateau();
            if (Compte_Couleur(BLANC)>Compte_Couleur(NOIR)) cout << j2 << " (" << c_j2 << ")" << " a gagner\n";
            if (Compte_Couleur(BLANC)<Compte_Couleur(NOIR)) cout << j1 << " (" << c_j1 << ")" << " a gagner\n";
            if (Compte_Couleur(BLANC)==Compte_Couleur(NOIR)) cout << " Egalite\n";
            system("pause");

        }

        //----------CHOIX N°4
        if (choix[0]=='4'){
            choix_4();
        }
    }
    //----------FIN DU JEU
    if (choix[0]=='5'){
        choix_5();
    }

    return 0;
}
