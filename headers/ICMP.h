#ifndef ICMPH
#define ICMPH

//structure

typedef struct _enteteICMP{
    int type;
    int bit_0;
    int checksum;
    int identifier;
    int sequence_nb;
} enteteICMP;

//fonctions

enteteICMP* create_enteteICMP();
enteteICMP* lectureICMP(char*c);

#endif