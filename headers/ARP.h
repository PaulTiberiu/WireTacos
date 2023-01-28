#ifndef ARPH
#define ARPH


typedef struct _ARP {
    int operation;
    char* srcMAC;
    char* destMAC;
    char* srcIP;
    char* destIP;
} ARP;

ARP* lectureARP(char* c);
ARP* create_ARP();
void free_entete_ARP(ARP* res);

#endif