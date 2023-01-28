#ifndef TCPH
#define TCPH

//structures
typedef struct _enteteTCP{
    int port_src;
    int port_dst;
    unsigned long sequence_nb;
    unsigned long ack_nb;
    int THL;
    char* reserved_flags;
    int window;
    int checksum;
    int urgent_pointer;
    char* data;
} enteteTCP;

enteteTCP* create_enteteTCP();
enteteTCP* lectureTCP(char* c);
void free_enteteTCP(enteteTCP *tcp);

#endif
