#ifndef MENU
#define MENU

typedef struct _filter{
    int type;
    char* value;
} filter;

char* nomfichierlecture();
char* nomfichierecriture();
filter* create_filter();
filter* options();
void WireTacosBlink();
void free_filter(filter* f);

#endif
