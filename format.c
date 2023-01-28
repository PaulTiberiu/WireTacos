#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/format.h"

char* space_erase(char*src){

    size_t size=(long)strlen(src);
    char* res= calloc(size+1,sizeof(char));
    int i=0;
    int j=0;

    while(i<size){
        if(src[i]!=' '){
            res[j]=src[i];
            j++;
        }
        i++;
    }
    res[i]='\0';
    return res;

}

char* MACformat(char*src){

    size_t size=(long)strlen(src);
    char* res= calloc(size+1,sizeof(char));
    int i=0;
    
    while(i<size){
        if(src[i]==' '){
            res[i]=':';
        }
        else{
            res[i]=src[i];
        }
        i++;
    }
    res[i]='\0';
    return res;

}

char* IPformat(char* src){

    char* res= calloc(16,sizeof(char));
    int v1,v2,v3,v4;
    sscanf(src, "%x %x %x %x",&v1,&v2,&v3,&v4);
    sprintf(res,"%d.%d.%d.%d",v1,v2,v3,v4);
    return res;

}

int hex_to_int(char*string){
    //prend en paramètre un string non formaté et renvoie sa valeur en entier
    char*new = space_erase(string);
    int res =(int) strtol(new,NULL,16);
    free(new);
    return res;
}

char hex_to_char(char* string){
    char res = (char) strtol(string,NULL,16);
    return res;
}

int stringcompare(char* s1, char* s2){
    int i=0;
    while(i<17){
        if(s1[i]!=s2[i]){
            return 0;
        }
        i++;
    }
    return 1;
}