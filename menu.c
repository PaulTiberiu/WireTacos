#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/HTTP.h"
#include "headers/ethernet.h"
#include "headers/ICMP.h"
#include "headers/IP.h"
#include "headers/format.h"
#include "headers/TCP.h"
#include "headers/menu.h"

filter* create_filter(){
    filter* res =(filter*) malloc(sizeof(filter));
    res->type=0;
    res->value = calloc(256,sizeof(char));
    return res;
}

char* nomfichierlecture(){ 
    char *filename = (char*) calloc(100,sizeof (char));
    printf("Bonjour! Bienvenue dans WireTacos!\n");

    while(1){
        printf("Veuillez entrer le fichier que vous voulez analyser dans le format (ex: nom_fichier.txt) \n");
        scanf("%256s",filename);
        FILE *f = fopen(filename, "r");
        if (f == NULL) {
            fprintf(stderr, "Erreur ouverture fichier. Veuillez entrer un fichier valide, votre fichier est: %s\n\n",filename);
            continue;
        }
        fclose(f);
        return filename;
    }
    
}


char* nomfichierecriture(){ 
    char *filename = (char*) calloc(100,sizeof (char));
    
    printf("Veuillez entrer le nom du fichier d'output (il sera au format.txt) \n");
    scanf("%256s",filename);
    strcat(filename,".txt");
    return filename;
}

filter* options() {
  

    char j,k,k1;
    char i;
    char buffer[256];
    char buffer2[256];
    char buffer3[256];
    char buffer4[256];
    filter* res= create_filter();

    while(1){
        printf("Voulez-vous ajouter des filtres? (y/n)\n");
        scanf("%s",buffer);
        i=buffer[0];

        switch(i) {

            case 'n':
                return res;
                break;
        
            case 'y':
                printf("------------------------------------------------------\n");
                printf("Quel filtre voulez-vous ajouter?\n" );
                printf("1-Ethernet\n");
                printf("2-IPv4\n");
                printf("3-ARP\n");
                printf("4-ICMP\n");
                printf("5-TCP\n");
                printf("6-Numero de la trame (dans le fichier)\n");
                scanf("%s",buffer2);
        	j=buffer2[0];

                

            switch(j) {

                case '1':
                    printf("------------------------------------------------------\n");
                    printf("1 - mac addr == ? \n");
                    printf("2 - protocol == ? (RAPPEL : ce programme supporte IPv4 et ARP)\n");
                    scanf("%s",buffer3);
        	    k=buffer3[0];

                    

                    switch(k){

                        case '1':
                            printf("------------------------------------------------------\n");
                            printf("entrez votre addresse MAC en format hexadecimal (ex: ff:ff:ff:ff:ff:ff) : \n");
                            scanf("%256s",res->value);
                            res->type = 1;
                            return res;
                            break;
                        
                        case '2':
                            printf("------------------------------------------------------\n");
                            printf("entrez la valeur du protocol en hexadecimal \n 0x");
                            scanf("%256s",res->value);
                            res->type = 2;
                            return res;
                            break;

                        default : 
                            printf("------------------------------------------------------\n");
                	    printf("Veuiller entrer une valeur valide\n");
                            printf("------------------------------------------------------\n");
                            continue;
                    }

                    break;
                
                case '2': 
                    printf("------------------------------------------------------\n");
                    printf("1 - ip addr == ? \n");
                    printf("2 - protocol == ? (RAPPEL : ce programme supporte ICMP et TCP)\n");
                    scanf("%s",buffer4);
        	    k1=buffer4[0];


                    switch(k1){

                        case '1':
                            printf("------------------------------------------------------\n");
                            printf("entrez votre addresse ip sous forme de decimale pointe : \n");
                            scanf("%256s",res->value);
                            res->type = 3;
                            return res;
                            break;
                        
                        case '2':
                            printf("------------------------------------------------------\n");
                            printf("entrez la valeur du protocol en hexadecimal \n 0x");
                            scanf("%256s",res->value);
                            res->type = 5;
                            return res;
                            break;

                        default : 
                            printf("------------------------------------------------------\n");
                	    printf("Veuiller entrer une valeur valide\n");
                            printf("------------------------------------------------------\n");
                            continue;
                    }

                    break;

                case '3':
                    printf("------------------------------------------------------\n");
                    printf("type arp == ? \n");
                    printf("------------------------------------------------------\n");
                    printf("entrez la valeur du type en hexadecimal \n 0x");
                    scanf("%256s",res->value);
                    res->type = 4;
                    return res;
                    break;

                case '4':
                    printf("------------------------------------------------------\n");
                    printf("type icmp == ? \n");

                    printf("------------------------------------------------------\n");
                    printf("entrez la valeur du type en hexadecimal \n 0x");
                    scanf("%256s",res->value);
                    res->type = 6;
                    return res;

                    break;

                case '5':
                    printf("------------------------------------------------------\n");
                    printf("numero port tcp == ? \n");
                    
                    printf("------------------------------------------------------\n");
                    printf("entrez le numero de port en decimal \n 0d");
                    scanf("%256s",res->value);
                    res->type = 7;
                    return res;
                    break;


                case '6':
                    printf("------------------------------------------------------\n");
                    printf("numero de la trame  == ? \n");

                    printf("------------------------------------------------------\n");
                    printf("entrez le numero de la trame (dans le fichier) \n ");
                    scanf("%256s",res->value);
                    res->type = -1;
                    return res;
                    break;

                default:
                    printf("------------------------------------------------------\n");
                    printf("Veuiller entrer une valeur valide\n");
                    printf("------------------------------------------------------\n");
                    continue;
            }

            default:
                printf("------------------------------------------------------\n");
                printf("Veuiller entrer une valeur valide\n");
                printf("------------------------------------------------------\n");
                continue;
    }

    return 0;
    }
}

void WireTacosBlink(){
    printf("\033[H\033[2J\033[1m\033[7m\033[5m _       ___         ______                     \n");
    printf("| |     / (_)_______/_  __/___   ____ ___   ____\n");
    printf("| | /| / / / ___/ _ \\/ / / __ `/ ___/ __ \\/ ___/\n");
    printf("| |/ |/ / / /  /  __/ / / /_/ / /__/ /_/ (__  ) \n");
    printf("|__/|__/_/_/   \\___/_/  \\__,_/\\___/\\____/____/  \n\033[0m");
    printf("\033[7m WireTacos v1.2 \033[0m \n\u00a9 IORDACHE - AUDIGIER\n");

}

void WireTacos(){
    printf(" _       ___         ______                     \n");
    printf("| |     / (_)_______/_  __/___ ______  _____\n");
    printf("| | /| / / / ___/ _ \\/ / / __ `/ ___/ __ \\/ ___/\n");
    printf("| |/ |/ / / /  /  __/ / / /_/ / /__/ /_/ (__  ) \n");
    printf("|__/|__/_/_/   \\___/_/  \\__,_/\\___/\\____/____/  \n");
}

void free_filter(filter* f){
    free(f->value);
    free(f);
}
