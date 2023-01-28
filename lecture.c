#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/ARP.h"
#include "headers/IP.h"
#include "headers/ethernet.h"
#include "headers/ICMP.h"
#include "headers/HTTP.h"
#include "headers/TCP.h"
#include "headers/format.h"
#include "headers/lecture.h"
#include "headers/menu.h"


int lecture_paquet(FILE *f,char*c){
    /*fonction de lecture d'UN SEUL paquet*/

    int num_ligne;
    char buffer[600];
    char garbage[600];
    char ligne[600];
    int test=0;
    long pos,pos_prec=0;
    
    while(fgets(ligne, 256, f)!=NULL){
        pos=ftell(f);
        if(*ligne != EOF){
            sscanf(ligne, "%x %47[0-9a-fA-F ] %s\n", &num_ligne, buffer,garbage); //on va mettre tout en buffer sauf ce qu'on met dans num_ligne
            if (num_ligne==0){test++;} 
            // on vérifie que l'on ne soit pas passé sur une nouvelle trame SANS saut de ligne
            if (*ligne==13){ return 0;}
             //quand ligne attrape un caractère "CR", code ascii 13, on à atteind la fin du paquet
            if(test>1){
                fseek(f,pos_prec,0); 
                // si on est passé sur une nouvelle trame sans saut de ligne, il faut alors remonnter le flux avant de relancer
                return 0;
            }
            pos_prec = pos;
            strcat(c,buffer);
            strcat(c," ");
        }
        if(*ligne==EOF){return 0;}
    }
    return 1;

}

char* lecture_paquet_sans_frag(char *filename){ 
    /*fonction de lecture d'UN SEUL paquet*/
    FILE *f = fopen(filename, "r");
    
    if (f == NULL) {
        fprintf(stderr, "%s; %s; l.%d: Erreur ouverture fichier: %s\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, filename);
        exit(EXIT_FAILURE);
    }

    char *c = (char *) calloc (100000,1);

    if (c == NULL) {
        fprintf(stderr, "%s; %s; l.%d: Erreur allocation chaine\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        exit(EXIT_FAILURE);
    }
    
    int format=0;
    char buffer[600];
    char garbage[600];
    char ligne[600];
    
    while(fgets(ligne, 256, f)!=NULL){
        sscanf(ligne, "%47[0-9a-fA-F ] %s\n", buffer,garbage); //on va mettre tout en buffer sauf ce qu'on met dans num_ligne
        
        if (strlen(buffer)!=47){format = 1;}
        if (*ligne==13){ break;} //quand ligne attrape un caractère "CR", code ascii 13, on à atteind la fin du paquet
        strcat(c, buffer);
        strcat(c," ");
    }
    format++;
    fclose(f);
    return c;
}

liste* lecture_fichier(char *filename,char** tabadd){
    
    FILE *f = fopen(filename, "r");
    
    if (f == NULL) {
        fprintf(stderr, "%s; %s; l.%d: Erreur ouverture fichier: %s\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, filename);
        exit(EXIT_FAILURE);
    }

    int t=0;
    int i=0;
    liste *res = create_cell_liste();
    liste *tmp = res; 

    while (!t){       
        t = lecture_paquet(f,tmp->paquet);
        i+=addtableau(tmp->paquet, tabadd, i);
        liste *new = create_cell_liste();
        tmp->next = new;
        tmp = tmp->next;
    }
    fclose(f);
    return res;

}


int decapsuler(char* paquet,filter* filtre,int n,FILE* f,char** tabadd,int n2){
    if(!*paquet){return 0;}
    enteteEth* eth = lectureMAC(paquet);
    int type = filtre->type;

    if(!paquet){return 0;}

    if(type == 1){
        int testMac1 = strcmp(eth->src,filtre->value);
        int testMac2 = strcmp(eth->dest,filtre->value);
        if((testMac1)&&(testMac2)){
            free_entete_ethernet(eth);
            return 0;}
    }

    if(type == 2){
        int version = hex_to_int(filtre->value);
        if(eth->version!=version){
            free_entete_ethernet(eth);
            return 0;}
    }


    if((eth->version!=0x0806)&&(eth->version!=0x0800)){
        fprintf(f,"protocole encapsulé par Ethernet non pris en charge... pour l'instant %x \n",eth->version);
        printf("protocole encapsulé par Ethernet non pris en charge... pour l'instant %x\n",eth->version);
        free_entete_ethernet(eth);
        return 1;

    }

    if(eth->version==0x0806){  
         if(type>4){return 0;}
        ARP* arp = lectureARP(eth->data);
        
        if(type==3){
            int testIpsrcARP = strcmp(arp->srcIP,filtre->value);
            int testIpdestARP = strcmp(arp->destIP,filtre->value);
            if(testIpdestARP && testIpsrcARP){
                free_entete_ethernet(eth);
                free_entete_ARP(arp);
                return 0;}
        }

        if(type==4){
            int ARPtype = hex_to_int(filtre->value);
            if (arp->operation!=ARPtype){
                free_entete_ethernet(eth);
                free_entete_ARP(arp);
                return 0;}
        }
        
        fprintf(f,"__________________________________________________|\nn°%d\n",n);
        printFLOWCHART(eth->src,eth->dest,tabadd,f,n2);
        printf("__________________________________________________\nn°%d\n",n);
        printf("\t src : %s -------> %s : dest\n",eth->src,eth->dest);
        if(arp->operation==1){
            printf("\n ARP:\t Who has %s ? tell %s\n",arp->destIP,arp->srcIP);
            fprintf(f,"\n ARP:\t Who has %s ? tell %s\n",arp->destIP,arp->srcIP);
            free_entete_ethernet(eth);
            free_entete_ARP(arp);
            return 1;
        }
        if(arp->operation==2){
            printf("\n ARP: \t%s is at %s\n",arp->srcIP, arp->srcMAC);
            fprintf(f,"\n ARP:\t %s  is at %s\n",arp->destIP,arp->srcMAC);
            free_entete_ethernet(eth);
            free_entete_ARP(arp);
            return 1;
        }
        else{
            free_entete_ethernet(eth);
            free_entete_ARP(arp);
            return 0;
        }
        free_entete_ethernet(eth);
            free_entete_ARP(arp);
    }

    if(eth->version==0x0800){
        enteteIP* ip = lectureIP(eth->data);
        
        if(type==3){
            int testIpsrcIP= strcmp(ip->src,filtre->value);
            int testIpdestIP = strcmp(ip->dest,filtre->value);
            if(testIpdestIP && testIpsrcIP){
                free_entete_ethernet(eth);
                free_entete_ip(ip);
                return 0;}
        }
    
        if(type==5){
            int protocol = hex_to_int(filtre->value);
            if(ip->protocol!=protocol){
                free_entete_ethernet(eth);
                free_entete_ip(ip);
                return 0;}

            }
        
        if(type==4){
            free_entete_ethernet(eth);
            free_entete_ip(ip);
            return 0;}
        if((ip->protocol!=1)&&(ip->protocol!=6)){
            if(type>5){
                free_entete_ethernet(eth);
                free_entete_ip(ip);
                return 0;}

            fprintf(f,"__________________________________________________|\nn°%d\n",n);
            printFLOWCHART(ip->src,ip->dest,tabadd,f,n2);
            printf("\n");
            printf("__________________________________________________\nn°%d\n",n);
            printf("IP: \t src : %s -------> %s : dest\n",ip->src,ip->dest);
            printf("\nprotocole encapsulé par IP non pris en charge ... pour l'instant\n");
            if(ip->protocol==2){
                fprintf(f," (IGMP)\n");
                free_entete_ethernet(eth);
                free_entete_ip(ip);
                return 1;}
            if(ip->protocol==8){
                fprintf(f," (EGP)\n");
                free_entete_ethernet(eth);
                free_entete_ip(ip);
                return 1;}
            if(ip->protocol==9){
                fprintf(f," (IGP)\n");
                free_entete_ethernet(eth);
                free_entete_ip(ip);
                return 1;}
            if(ip->protocol==17){
                fprintf(f," (UDP)\n");
                free_entete_ethernet(eth);
                free_entete_ip(ip);
                return 1;}
            if(ip->protocol==36){
                fprintf(f," (XTP)\n");
                free_entete_ethernet(eth);
                free_entete_ip(ip);
                return 1;}
            if(ip->protocol==46){
                fprintf(f," (RSVP)\n");
                free_entete_ethernet(eth);
                free_entete_ip(ip);
                return 1;}
            else{
                free_entete_ethernet(eth);
                free_entete_ip(ip);
                return 1;}
        }

        if(ip->protocol==1){
            enteteICMP* icmp = lectureICMP(ip->data);
            if(type==6){
                int icmptype = hex_to_int(filtre->value);
                if(icmp->type!=icmptype){
                    free_entete_ethernet(eth);
                    free_entete_ip(ip);
                    free(icmp);
                    return 0;}
                
            }
            if(icmp->type == 8){
                fprintf(f,"__________________________________________________|\nn°%d\n",n);
                printFLOWCHART(ip->src,ip->dest,tabadd,f,n2);
                printf("__________________________________________________\nn°%d\n",n);
                printf("IP: \t src : %s ------->%s : dest\n",ip->src,ip->dest);
                printf("ICMP : Echo (ping) request : id = 0x%x\n",icmp->identifier);
                fprintf(f,"ICMP : Echo (ping) request : id = 0x%x\n",icmp->identifier);
                free_entete_ethernet(eth);
                free_entete_ip(ip);
                free(icmp);
                return 1;
            }
            if(icmp->type == 0){
                fprintf(f,"__________________________________________________|\nn°%d\n",n);
                printFLOWCHART(ip->src,ip->dest,tabadd,f,n2);
                printf("__________________________________________________\nn°%d\n",n);
                printf("IP: \t src : %s ------->%s : dest\n",ip->src,ip->dest);
                printf("ICMP : Echo (ping) reply : id = 0x%x\n",icmp->identifier);
                fprintf(f,"ICMP : Echo (ping) reply : id = 0x%x\n",icmp->identifier);
                free_entete_ethernet(eth);
                free_entete_ip(ip);
                free(icmp);
                return 1;
            }
        }
        if(ip->protocol==6){
            
            if(type==6){return 0;}
            enteteTCP*tcp = lectureTCP(ip->data);

            if(type==7){
                int filterport= (int) strtol(filtre->value,NULL,10);
                if(filterport!=tcp->port_src && filterport!=tcp->port_dst){
                    free_entete_ethernet(eth);
                    free_entete_ip(ip);
                    free_enteteTCP(tcp);
                    return 0;}
            }

            fprintf(f,"__________________________________________________|\nn°%d\n",n);
            printFLOWCHART(ip->src,ip->dest,tabadd,f,n2);
            printf("__________________________________________________\nn°%d\n",n);
            printf("IP: \t src : %s ------->%s : dest\n",ip->src,ip->dest);
            printf("TCP : \t source port :%d  ->  %d : dest port\n",tcp->port_src,tcp->port_dst);
            printf("%s Seq:%lu Ack:%lu Window:%d\n",tcp->reserved_flags, tcp->sequence_nb,tcp->ack_nb,tcp->window);
            fprintf(f,"TCP : \t source port :%d  ->  %d : dest port\n",tcp->port_src,tcp->port_dst);
            fprintf(f,"      \t%s Seq:%lu Ack:%lu Window:%d\n",tcp->reserved_flags,tcp->sequence_nb,tcp->ack_nb,tcp->window);


            if((tcp->port_src==80||tcp->port_dst==80)&&(tcp->data[0]!='\0')){
                HTTP* http = lecture_HTTP(tcp->data);
                printf("HTTP: %s\n",http->ligne);
                fprintf(f,"HTTP: %s\n",http->ligne);
                free_entete_ethernet(eth);
                free_entete_ip(ip);
                free_enteteTCP(tcp);
                free_HTTP(http);
                return 1;
            }

            free_entete_ethernet(eth);
            free_entete_ip(ip);
            free_enteteTCP(tcp);
            return 1;
        }


    }
    free_entete_ethernet(eth);
    return 0;
}


void affichage_liste(liste *l,filter *f,char* filename,char **tabadd,int n2){
    FILE* fichier = fopen(filename,"w");
    int nb;
    int valfiltre;
    int testfiltre = f->type == -1;
    if(testfiltre){
        nb = 0;
        valfiltre = (int) strtol(f->value,NULL,10);  
        while(l != NULL){
            nb++;
            if((nb == valfiltre)&&(testfiltre)){
                decapsuler(l->paquet,f,nb,fichier,tabadd,n2);
            }
            l=l->next;
        }
        return;
    }
    nb=1;
    while(l != NULL){
        
        
        nb += decapsuler(l->paquet,f,nb,fichier,tabadd,n2);
        l=l->next;
    }
    fclose(fichier);
    return;
}



int addtableau(char* paquet, char** tabadd, int i){
    char* mac = calloc(18,sizeof(char));
    char* mac2 = calloc(18, sizeof(char));
    char* protocol = calloc(5, sizeof(char));
    char* garbageip = calloc(50,sizeof(char));
    char* ips = calloc(20,sizeof(char));
    char* ipd = calloc(20,sizeof(char));
    char *data = calloc(10000, sizeof(char));

    sscanf(paquet,"%17[0-9a-fA-F ] %17[0-9a-fA-F ] %5[0-9a-fA-F ] %36[0-9a-fA-F ] %11[0-9a-fA-F ] %11[0-9a-fA-F ] %[0-9a-fA-F ]"
    ,mac , mac2, protocol, garbageip, ips, ipd, data);

    int prot = hex_to_int(protocol);
    char* acopier1;
    char* acopier2;

    if(prot == 0x800){
        acopier1 = IPformat(ips);
        acopier2 = IPformat(ipd);
    }

    if(prot!=0x800){
        acopier1 = MACformat(mac2);
        acopier2 = MACformat(mac);
    }

    int valreturn = 0;
    int test1=1;
    int test2 = 1; 
    int j = 0;

    if(i==0){
        strcpy(tabadd[0],acopier1);
        strcpy(tabadd[1],acopier2);
        free(mac);
        free(mac2);
        free(protocol);
        free(garbageip);
        free(ips);
        free(ipd);
        free(data);
        free(acopier1);
        free(acopier2);
        return 2;
    }

    while(j<i){
        if(!strcmp(tabadd[j],acopier1)){
            test1 = 0;
            break;
        }
        if(tabadd[j][0]=='\0'){
            break;
        }
        j++;
    }

    if(j == i-1 && tabadd[j][0]!='\0'){
        test1 = 0;
        strcpy(tabadd[i],acopier1);
        valreturn ++;
    }

    if(test1){
        strcpy(tabadd[j],acopier1);
        valreturn ++;
    }


    j= 0;
    while(j<i){
        if(!strcmp(tabadd[j],acopier2)){
            test2 = 0;
            break;
        }
        if(tabadd[j][0]=='\0'){
            break;
        }
        j++;
    }

    if(j == i-1 && tabadd[j][0]!='\0'){
        test2 = 0;
        strcpy(tabadd[i],acopier2);
        valreturn ++;
    }

    if(test2){
        strcpy(tabadd[j],acopier2);
        valreturn ++;
    }
    

    free(mac);
    free(mac2);
    free(protocol);
    free(garbageip);
    free(ips);
    free(ipd);
    free(data);
    free(acopier1);
    free(acopier2);
    return valreturn;
}


void printFLOWCHART(char* source, char* dest, char** tabadd,FILE*f,int n2){

    int testi = 1;
    int testj = 1;
    int i = 0;
    int j = 0;
    

    while(testi&&i<n2){
        testi = strcmp(source,tabadd[i]);
        i++;
    }
    while(testj&&j<n2){
        testj = strcmp(dest,tabadd[j]);
        if(!strcmp(source,"ff:ff:ff:ff:ff:ff")){
            j=n2;
            break;
        }
        if(!strcmp(source,"255.255.255.255")){
            j=n2;
            break;
        }
        j++;
    }

    fprintf(f,"\t\t\t\t\t\t");

    int t = 17 - (int) strlen(source);

    if(i < j){
        for(int l = 0; l<(t/2);l++){printf(" ");}
        for(int k = 0; k<=i; k++){ fprintf(f,"        ");}
        fprintf(f," %s",source);
        for(int l=i; l<j; l++){fprintf(f,"-----");}
        fprintf(f,">%s\n",dest);
        return;
    }
        for(int l = 0; l<(t/2);l++){printf(" ");}
        for(int k = 0; k<=j; k++){ fprintf(f,"        ");}
        fprintf(f," %s<",dest);
        for(int l= j; l<i; l++){fprintf(f,"-----");}
        fprintf(f,"%s\n",source);
        return;

}

    


