#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/TCP.h"
#include "headers/format.h"
#include "headers/lecture.h"


enteteTCP* create_enteteTCP(){
    //crée un entete TCP sans valeur en mémoire 
    enteteTCP* res = (enteteTCP *) malloc(sizeof (enteteTCP));
    if (res == NULL){
        fprintf(stderr, "enteteTCP  : erreur d'allocation");
        exit(EXIT_FAILURE);
    }
    res->data = (char*) calloc(10000,sizeof (char));
    res->reserved_flags = (char*) calloc(1000,sizeof (char));

    return res; 
}

enteteTCP* lectureTCP(char* c){ 
    enteteTCP* res = create_enteteTCP();
    char* port_src=calloc(11, sizeof(char));
    char* port_dst=calloc(11, sizeof(char));
    char* sequence_nb=calloc(20,sizeof(char));
    char* ack_nb=calloc(17, sizeof(char));
    char* window=calloc(11, sizeof(char));
    char* checksum=calloc(11, sizeof(char));
    char* urgent_pointer=calloc(11, sizeof(char));
    char* flagsraw = calloc(15, sizeof(char));
    char* flagsdecrypt = calloc(100,sizeof(char));


    sscanf(c, "%5[0-9a-fA-F ] %5[0-9a-fA-F ] %11[0-9a-fA-F ] %11[0-9a-fA-F ] %1x %4[0-9a-fA-F ] %5[0-9a-fA-F ] %5[0-9a-fA-F ] %5[0-9a-fA-F ] %[0-9a-fA-F ] ",
    /*1*/port_src,/*2*/port_dst,/*3*/sequence_nb,/*4*/ack_nb,/*5*/&(res->THL),/*6*/flagsraw,/*7*/window,/*8*/checksum,/*9*/urgent_pointer,res->data);
    
    res->port_src=hex_to_int(port_src);
    res->port_dst=hex_to_int(port_dst);
    free(port_src);
    free(port_dst);
    char* newseq = space_erase(sequence_nb);
    char* newack = space_erase(ack_nb);
    free(sequence_nb);
    free(ack_nb);
    res->sequence_nb = (unsigned long) strtol(newseq,NULL,16);
    res->ack_nb = (unsigned long) strtol(newack,NULL,16);
    free(newseq);
    free(newack);
    int flags = hex_to_int(flagsraw);
    free(flagsraw);
    int flagtab[6];
    int i = 0;
    while(i<6){
        flagtab[i] = flags & 1 ;
        flags = flags >> 1;
        i++;
    }
    if(flagtab[0]==1){strcat(flagsdecrypt," FIN");}
    if(flagtab[1]==1){strcat(flagsdecrypt," SYN");}
    if(flagtab[2]==1){strcat(flagsdecrypt," RST");}
    if(flagtab[3]==1){strcat(flagsdecrypt," PSH");}
    if(flagtab[4]==1){strcat(flagsdecrypt," ACK");}
    if(flagtab[5]==1){strcat(flagsdecrypt," URG");}

    strcpy(res->reserved_flags,flagsdecrypt);
    free(flagsdecrypt);



    res->window=hex_to_int(window);
    res->checksum=hex_to_int(checksum);
    res->urgent_pointer=hex_to_int(urgent_pointer);
    free(window);
    free(checksum);
    free(urgent_pointer);
    if(res->THL > 5 ){
        char * newdata = space_erase(res->data);
        free(res->data);
        res->data = newdata;
        int pos = ((res->THL-5)*8);
        int j = 0;
        for(int i=pos;i<strlen(res->data);i++){
            res->data[j]=res->data[i];
            j++;
        }
        res->data[j]='\0';
    }
  


    return res;
}

void free_enteteTCP(enteteTCP *tcp){
    free(tcp->data);
    free(tcp->reserved_flags);
    free(tcp);
}