#ifndef ETHERNETH
#define ETHERNETH

//structures
typedef struct _enteteEth{
    char* src;
    char* dest;
    int version;
    char* data;
} enteteEth;

enteteEth* create_enteteEth();
enteteEth* lectureMAC(char* c); 
void free_entete_ethernet(enteteEth *eth);

#endif