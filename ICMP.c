#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/format.h"
#include "headers/lecture.h"
#include "headers/ICMP.h"

enteteICMP* create_enteteICMP(){
    //crée un entete ICMP sans valeur en mémoire
    enteteICMP* res = (enteteICMP *) malloc(sizeof (enteteICMP));
    if (res == NULL){
        fprintf(stderr, "enteteICMP: erreur d'allocation");
        exit(EXIT_FAILURE);
    }
    return res; 
}

enteteICMP* lectureICMP(char*c){
    enteteICMP* res = create_enteteICMP();
    char* checksum=calloc(11,sizeof(char));
    char* identifier=calloc(11,sizeof(char));
    char* sequence_nb=calloc(11,sizeof(char));
    sscanf(c,"%2x %2x %5[0-9a-fA-F ] %5[0-9a-fA-F ] %5[0-9a-fA-F ] ",&(res->type),/*2*/&(res->bit_0),/*3*/checksum,/*4*/identifier,/*5**/sequence_nb);
        
    res->checksum=hex_to_int(checksum);
    free(checksum);
    res->identifier=hex_to_int(identifier);
    free(identifier);
    res->sequence_nb=hex_to_int(sequence_nb);
    free(sequence_nb);
    return res;
}