#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./headers/IP.h"
#include "./headers/ethernet.h"
#include "./headers/ARP.h"
#include "./headers/lecture.h"
#include "./headers/format.h"


ARP* create_ARP(){
    ARP* res = (ARP*) malloc(sizeof(ARP));
    if (res == NULL){
        fprintf(stderr, "enteteEth : erreur d'allocation");
        exit(EXIT_FAILURE);
    }
    res->srcMAC= (char *) calloc(17,sizeof(char));
    res->destMAC= (char *) calloc(17,sizeof(char));
    res->srcIP= (char *) calloc(11,sizeof(char));
    res->destIP= (char *) calloc(11,sizeof(char));
    return res;
}


ARP* lectureARP(char* c){
    ARP* res =create_ARP();
    char* garbage2=calloc(50,sizeof(char));
    char* srcM=calloc(17,sizeof(char));
    char* dstM=calloc(17,sizeof(char));
    char* srcI=calloc(11,sizeof(char));
    char* dstI=calloc(42,sizeof(char));
    sscanf(c,"%21[0-9a-fA-F ] %x %17[0-9a-fA-F ] %11[0-9a-fA-F ] %17[0-9a-fA-F ] %11[0-9a-fA-F ]"
    ,garbage2,&(res->operation),srcM,srcI,dstM,dstI);

    char*newsrcip = IPformat(srcI);
    strcpy(res->srcIP,newsrcip);
    free(srcI);
    free(newsrcip);
    char*newsrcmac = MACformat(srcM);
    strcpy(res->srcMAC,newsrcmac);
    free(srcM);
    free(newsrcmac);
    char*newdstmac = MACformat(dstM);
    strcpy(res->destMAC,newdstmac);
    free(dstM);
    free(newdstmac);
    char*newdstip = IPformat(dstI);
    strcpy(res->destIP,newdstip);
    free(dstI);
    free(newdstip);

    free(garbage2);
    return res;       

}

void free_entete_ARP(ARP* res){
    free(res->srcMAC);
    free(res->srcIP);
    free(res->destMAC);
    free(res->destIP);
    free(res);
}
