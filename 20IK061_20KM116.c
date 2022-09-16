#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*ILUNGA KAYEMBE RAPHAEL & KALANGA MUWAYA JEANNE*/
typedef struct personne{
    char nom[31];
    char numero[11];
}personne;
/*fonction Acquisition*/
int Acquisition(personne *appelant){
    char name[31], number[11];
    int i, lettre = 0;
    printf("Tapez le nom: ");
    scanf("%30s", name);
    printf("Tapez le numero: ");
    scanf("%10s", number);

    if(strlen(name) <= 30 && strlen(number) == 10 && number[0] == '0'){
        if(number[1] == '8' || number[1] == '9'){
            for(i = 0; i < 30; i++){
                if(name[i] >= 'a' && name[i] <= 'z')
                    name[i] = name[i] - 32;
            }
            for(i = 0; i < 10; i++){
                if(number[i] < '0' || number[i] > '9' )
                    lettre = 1;
            }
            if(lettre == 0){
                strcpy(appelant->nom, name);
                strcpy(appelant->numero, number);
                return 1;
            }
            else if(lettre == 1)
            {
                puts("Erreur de saisie!!!\a\n");
                return 0;
            }
        }
        else{
            puts("Erreur de saisie!!!\a\n");
        }
    }
    else{
        puts("Erreur de saisie!!!\a\n");
        return 0;
    }

}

/*fonction Ajoute*/

int Ajoute(personne **Annuaire, personne *appelant, int *nombre_personne, int *taille){
    personne *temp, temporaire;
    int deux_nom = 0, i, j;
    /* reallocation si le tableau est plein*/
    if(*nombre_personne == *taille){
        *taille = *taille + 5;
        printf("\a");
        temp = realloc((*Annuaire), sizeof(personne) * *taille);
        if(temp == NULL){
            puts("Erreur reaollocation\a");
            EXIT_FAILURE;
        }
        *Annuaire = temp;
    }
    /*ajout d'une personne dans l'annuaire*/
    for(i = 0; i <= *nombre_personne; i++){
        if(strcmp(appelant->nom, (*Annuaire)[i].nom) == 0){
            strcpy((*Annuaire)[i].numero, appelant->numero);
            deux_nom++;
        }
    }

    if(deux_nom == 0){
        (*Annuaire)[*nombre_personne] = *appelant;
    }
    /*mise en odre alphabetique*/
    for(i = 0; i <= *nombre_personne; i++){
        for(j = 0; j <= *nombre_personne; j++){
            if(strcmp((*Annuaire)[i].nom, (*Annuaire)[j].nom) < 0){
                temporaire = (*Annuaire)[i];
                (*Annuaire)[i] = (*Annuaire)[j];
                (*Annuaire)[j] = temporaire;
            }
        }
    }
    *nombre_personne = *nombre_personne + 1;
    if(deux_nom == 0)
        return 0;
    else
        return 1;

}

void Affiche(personne *Annuaire, int nombre_personne, int RetourAjoute){
    int i, vide = 0, borne = nombre_personne - RetourAjoute;
    puts("******** Contenue de l'annuaire *************\n");
    for(i = 0; i < borne; i++){
        if(strcmp(Annuaire[i].nom, "") != 0 && strcmp(Annuaire[i].numero, "") != 0)
            printf("\t%s: %s\n", Annuaire[i].nom, Annuaire[i].numero);
            vide++;
    }
    if(vide == 0)
        puts("\tl'annuaire est vide");
    puts("----------------------------------------------\n");
}

void RechercheTel(personne *Annuaire, int nombre_personne){
    int i, trouver = 0;
    char nom[31];
    printf("Tapez le nom: ");
    scanf("%30s", nom);
    for(i = 0; i < 30; i++){
        if(nom[i] >= 'a' && nom[i] <= 'z')
            nom[i] = nom[i] - 32;
    }
    for(i = 0; i <= nombre_personne; i++){
        if(strcmp(nom, Annuaire[i].nom) == 0){
            printf("\t Voici le numero de %s ==> %s\n", nom, Annuaire[i].numero);
            trouver++;
            break;
        }
    }
    if(trouver == 0)
        puts("\n\tPas de personne a ce nom !!!\n");
}

void RechercheNom(personne *Annuaire, int nombre_personne){
    int i, trouver = 0;
    char numero[11];
    printf("Tapez le numero: ");
    scanf("%10s", numero);

    for(i = 0; i <= nombre_personne; i++){
        if(strcmp(numero, Annuaire[i].numero) == 0){
            printf("\tVoici nom a ce numero ==> %s\n", Annuaire[i].nom);
            trouver++;
            break;
        }
    }
    if(trouver  == 0)
        puts(" \n\t Pas de ce numero dans l'annuaire !!! \n");
}

void Efface(personne *Annuaire, int nombre_personne){
    int i, indice, trouver = 0;
    char nom[31];
    printf("Tapez le nom a suprimer: ");
    scanf("%30s", nom);
    for(i = 0; i < 30; i++){
        if(nom[i] >= 'a' && nom[i] <= 'z')
            nom[i] = nom[i] - 32;
    }

    for(i = 0; i <= nombre_personne; i++){
        if(strcmp(nom, Annuaire[i].nom) == 0){
            indice = i;
            ++trouver;
            break;
        }
    }
    if(trouver != 0 && indice != nombre_personne){
        Annuaire[indice] = Annuaire[indice + 1];
        strcpy(Annuaire[indice + 1].nom, "");
        strcpy(Annuaire[indice + 1].numero, "");
    }
    else if(trouver != 0 && indice == nombre_personne){
        strcpy(Annuaire[indice].nom, "");
        strcpy(Annuaire[indice].numero, "");
    }
    else
        puts("\n\t Pas de personne avec ce nom !!! \n");
}

void Menu(){
    puts("1 = Ajouter une personne a l'annuaire\n2 = Afficher le contenu de l'annuaire dans l'ordre alphabetique\n3 = Supprimer une personne de l'annuaire\n4 = Consulter le numero de telephone d'une personne\n5 = Trouver a qui appartient un certain numero\n6 = Sortir du programme\n");
    printf("Tapez ici votre choix -->: ");
}
int main()
{
    personne *Annuaire, appelant;
    int taille = 2, RetourAcquisition, RetourAjoute, nombre_personne = 0, i, choix;
    Annuaire =  malloc(sizeof(personne) * taille);

    if(Annuaire == NULL){
        puts("Erreur d'allocation\a");
        EXIT_FAILURE;
    }
    puts("************************************ BIENVENU AU MENU ******************************************");

    while(1){
        Menu();
        scanf("%d", &choix);
        while(choix < 1 ||  choix > 6){
            printf("Erreur!!! Le choix doit etre une valeur dans l'interval [1-6]. Tapez: ");
            scanf("%d", &choix);

        }
        if(choix == 1){
            RetourAcquisition = Acquisition(&appelant);
            if(RetourAcquisition == 1){
                system("cls");
                RetourAjoute = Ajoute(&Annuaire, &appelant, &nombre_personne, &taille);
            }
        }
        if(choix == 2){
            system("cls");
            Affiche(Annuaire, nombre_personne, RetourAjoute);
        }
        if(choix == 3){
            system("cls");
            Efface(Annuaire, nombre_personne);
        }
        if(choix == 4){
            system("cls");
            RechercheTel(Annuaire, nombre_personne);
        }
        if(choix == 5){
            system("cls");
            RechercheNom(Annuaire, nombre_personne);
        }
        if(choix == 6)
            break;
    }
    free(Annuaire);
    puts("************************************* Fin du programme... ***************************");
    return 0;
}