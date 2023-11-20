#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAILLE 9

// déclaration du type tGrille

typedef int tGrille[TAILLE][TAILLE];

// promesses de fonctions/procédures

void chargerGrille(tGrille g);
void afficherGrille(tGrille g);
void saisir(int *S);
bool possible(int lig, int col, int val, tGrille g);
int verifGrille(tGrille g);


int main(){
    //déclaration des variables
    int numLigne,numColonne,valeur;
    int compt = 0;
    tGrille grille1;
    

    chargerGrille(grille1);

    //boucle principale
    while (compt < (TAILLE*TAILLE))
    {
        afficherGrille(grille1);
        compt = verifGrille(grille1);
        printf("Indice de la case ?\n");
        saisir(&numLigne);
        saisir(&numColonne);

        // décrémentation des coordonnée saisient par l'utilisateur pour correspondre au coordonnées du tableau
        numLigne--;
        numColonne--;


        if (grille1[numLigne][numColonne] !=0)
        {
            printf("Impossible, la case n'est pas libre.\n");
        }else{
            printf("Valeur à insérer ?\n");
            saisir(&valeur);
            if (possible(numLigne,numColonne,valeur,grille1))
            {
                grille1[numLigne][numColonne] = valeur;
                compt += 1;
            }          
        }
    }  
    printf("Grille pleine fin de partie\n");
    return EXIT_SUCCESS;
}




// chargement de la grille

void chargerGrille(tGrille g){
    char nomFichier[30];
    FILE * f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f==NULL){
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    } else {
        fread(g, sizeof(int), TAILLE*TAILLE, f);
    }
    fclose(f);
}

// affiche de la grille

void afficherGrille(tGrille g) {
    // affichage des numeros de colonne espacé tout les 3 chiffres
    printf("    ");
    for (int k = 1; k <= TAILLE; k++){
        if(k > 1 && k % 3 == 1)
        {
            printf(" ");
        }
        printf(" %d ", k);
    }
    printf("\n");
    printf("   ");

    // affichage de la séparation avec + et ----
    for (int i = 0; i < 3; i++)
    {
        printf("+");
        printf("---------");        
    }
    printf("+");
    printf("\n");

    // boucle qui affiche chaque ligne
    for (int i = 0; i < TAILLE; i++){
        printf("%d  ",i+1);
        printf("|");

        // boucle qui affiche chaque colonne
        for (int j = 0; j < TAILLE; j++) {
            if (g[i][j] == 0)
            {
                printf(" . ");
            }else
            {
                printf(" %d ", g[i][j]);
            } 
            if ((j+1) % 3 == 0){ // si la division de j est = 0 alors | est afficher 
                printf("|");
            }
        }
        printf("\n");

        // separation avec + et ---- entre lefor (int j = 0; j < NB_COLONNES; j++) {s bloc de 3 lignes
        if ((i+1) % 3 == 0 && i+1 !=TAILLE) 
        {
            printf("   ");
            for (int i = 0; i < 3; i++)
            {
                printf("+");
                printf("---------");        
            }
            printf("+\n");
        } 
    }
    // affichage du dernier séparateur avec + et ----
    printf("   ");
    for (int i = 0; i < 3; i++)
    {
        printf("+");
        printf("---------");        
    }
    printf("+\n");

}


// saisie des données

void saisir(int *S){
    char ch[10];
    int x;
    do
    {
        printf("Saisissez un chiffre :\n");
        scanf("%s", ch);
        if (sscanf(ch, "%d", &x) !=0){
            // la conversion a réussi, x contient la
            // valeur entière lue au clavier
            *S = x;
        } else {
            //la conversion en entier a échoué
            printf("La saisie a échoué, nb invalide\n");
        }
    } while (*S < 1 || *S > TAILLE);    
}

// vérification des coordonnées et de la valeur
bool possible(int lig, int col, int val, tGrille g){
    bool rep = true;
    int debut_lig = (lig/3)*3;
    int debut_col = (col/3)*3;

    for (int i = 0; i < TAILLE; i++)// verifie les doublons dans la ligne
    {
        if (g[lig][i] == val)
        {
            rep = false;
            printf("il y a déjà cette valeur sur la ligne\n");
        } 
    }
    for (int i = 0; i < TAILLE; i++)// verifie les doublons dans la colonne
    {
        if (g[i][col] == val)
        {
            rep = false;
            printf("il y a déjà cette valeur sur la colonne\n");
        }
    }
    for (int i = debut_lig; i < debut_lig+3 ; i++)
    {
        for (int j = debut_col; j < debut_col+3; j++)
        {
            if (g[i][j] == val)
            {
                printf("valeur deja dans le carre de 3x3\n");
                rep = false;
            }    
        } 
    }
    return rep;  
}

int verifGrille(tGrille g){
    int compt = 0;
    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            if (g[i][j] != 0)
            {
                compt += 1;
            }
        }
    } 
    return compt;
}
