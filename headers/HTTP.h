#ifndef HTTPH
#define HTTPH


typedef struct _HTTP{
    char* ligne;
   char* data;
} HTTP;


HTTP* create_HTTP();
HTTP* lecture_HTTP(char* http);
void free_HTTP(HTTP *http);


#endif
