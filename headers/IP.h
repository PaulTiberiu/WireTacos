#ifndef IPH
#define IPH

typedef struct _enteteIP{
    int version;
    int IHL;
    int TOS;
    int total_length;
    int identification;
    int offset;
    int TTL;
    int protocol;
    int header_checksum;
    char* src; 
    char* dest;
    char* data;
} enteteIP;

enteteIP* create_enteteIP();
char* versionip_ip(enteteIP *ip);
enteteIP* lectureIP(char*c);
void free_entete_ip(enteteIP *ip);

#endif
