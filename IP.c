#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/IP.h"
#include "headers/ethernet.h"
#include "headers/lecture.h"
#include "headers/format.h"

enteteIP* create_enteteIP(){
    //crée une trame IP sans valeur en mémoire
    enteteIP* res = (enteteIP *) malloc(sizeof (enteteIP));
    if (res == NULL){
        fprintf(stderr, "enteteIP: erreur d'allocation");
        exit(EXIT_FAILURE);
    }
    res->src = (char*) malloc(sizeof (char)*17);
    res->dest = (char*) malloc(sizeof (char)*17);
    res->data = calloc(10000,sizeof(char));
    return res; 
}

char* versionip_ip(enteteIP *ip){
    //lecture de la version de l'IP
    char* res =(char*) calloc(14,14*sizeof(char));
    if (ip->version==4){
            strcat(res,"Version: IPv4");
    }
    else {
        fprintf(stderr, "enteteIP : cette trame n'est pas IPv4, arrêt du programme\n");
        exit(EXIT_FAILURE);
    }
    return res;
}

enteteIP* lectureIP(char*c){
    enteteIP* res = create_enteteIP();
    char* length=calloc(6,sizeof(char));
    char* id=calloc(6,sizeof(char));
    char* frag_off=calloc(6,sizeof(char));
    char* checksum=calloc(6,sizeof(char));
    char* ip_source=calloc(11,sizeof(char));
    char* ip_dest= calloc(11,sizeof(char));
    sscanf(c,"%1x%1x %x %5[0-9a-fA-F ] %5[0-9a-fA-F ] %5[0-9a-fA-F ] %x %x %5[0-9a-fA-F ] %11[0-9a-fA-F ] %11[0-9a-fA-F ] %[0-9a-fA-F ]",
    /*2*/&(res->version),/*3*/&(res->IHL),/*4*/&(res->TOS),/*5*/length,/*6*/id,/*7*/frag_off,&(res->TTL),&(res->protocol),checksum,ip_source,ip_dest,res->data);
    char* nlength = space_erase(length);
    res->total_length = (int) strtol(nlength,NULL,16);
    free(length);
    free(nlength);
    char *new_id = space_erase(id);
    res->identification = (int) strtol(new_id,NULL,16);
    free(id);
    free(new_id);


    char*new_off = space_erase(frag_off);
    res->offset = (int) strtol(new_off,NULL,16);
    free(frag_off);
    free(new_off);

    char *new_check = space_erase(checksum);
    res->header_checksum = (int) strtol(new_check,NULL,16);
    free(checksum);
    free(new_check);
    
    char* newsource= IPformat(ip_source);
    char* newdest= IPformat(ip_dest);
    strcpy(res->src,newsource);
    strcpy(res->dest,newdest);
    free(ip_dest);
    free(ip_source);
    free(newsource);
    free(newdest);

    
    int size = ((res->IHL)*8); // on regarde la taille du header, on fait *4 car on est sur *4 octet, *2 car un octet est rerésenté sur deux caractère
    int j=0;
    if(size>40){
        char* optionlessdata = calloc(5000,sizeof(char));
        for(int i=size+1;i<strlen(res->data);i++){
            optionlessdata[j]=res->data[i];
            j++;
        }
    
    optionlessdata[j]='\0';
    free(res->data);
    res->data = optionlessdata;

    }
    
    return res;
}

void free_entete_ip(enteteIP *ip){
    free(ip->src);
    free(ip->dest);
    free(ip->data);
    free(ip);
}
