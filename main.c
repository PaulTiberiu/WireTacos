#include "headers/ARP.h"
#include "headers/IP.h"
#include "headers/ethernet.h"
#include "headers/ICMP.h"
#include "headers/TCP.h"
#include "headers/HTTP.h"
#include "headers/lecture.h"
#include "headers/format.h"
#include "headers/menu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

    char ** tableau_adresse =(char**) calloc(10000,sizeof(char*));
    for(int i=0;i<10000;i++){
        tableau_adresse[i] = (char*)calloc(50,sizeof(char));
    }

    WireTacosBlink();
    char*fichier_lu = nomfichierlecture();
    liste *l=lecture_fichier(fichier_lu,tableau_adresse);
    int n = 0;
    while(tableau_adresse[n][0]!='\0'){
          n++;
    }
  
    int i = 0;
    char*fichier_ecriture = nomfichierecriture();
    filter* filtre = options();
    liste* tmp = l;
    affichage_liste(l,filtre,fichier_ecriture,tableau_adresse,n);
    
    delete_liste(l);
    
    for(int i=0;i<10000;i++){
        free(tableau_adresse[i]);
    }
    free(fichier_lu);
    free(fichier_ecriture);
    free(tableau_adresse);
    free_filter(filtre);

    return 0;
} 
