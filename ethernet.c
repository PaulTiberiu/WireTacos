#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/ethernet.h"
#include "headers/lecture.h"
#include "headers/format.h"

enteteEth* create_enteteEth(){
    //crée une trame MAC sans valeur en mémoire 
    enteteEth* res = (enteteEth *) malloc(sizeof (enteteEth));
    if (res == NULL){
        fprintf(stderr, "enteteEth  : erreur d'allocation");
        exit(EXIT_FAILURE);
    }
    res->dest = (char*) calloc(30,sizeof (char));
    res->src = (char*) calloc(30,sizeof (char));
    res->data = (char*) calloc(10000, sizeof(char));
    return res; 
}

enteteEth* lectureMAC(char* c){
    enteteEth * res = create_enteteEth();
    char*dest= calloc(17,sizeof(char));
    char*source= calloc(17,sizeof(char));
    char*type= calloc(5,sizeof(char));
    
    sscanf(c,"%17[0-9a-fA-F ] %17[0-9a-fA-F ] %5[0-9a-fA-F ] %[0-9a-fA-F ]",dest,source,type,res->data);
    char* newdest = MACformat(dest);
    char* newsrc = MACformat(source);
    strcpy(res->dest,newdest);
    strcpy(res->src,newsrc);
    res->version = hex_to_int(type);
    free(newdest);
    free(newsrc);
    free(dest);
    free(source);
    free(type);

    return res;
}


void free_entete_ethernet(enteteEth *eth){
    free(eth->dest);
    free(eth->src);
    free(eth->data);
    free(eth);
}