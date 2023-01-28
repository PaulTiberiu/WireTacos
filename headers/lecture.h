#ifndef LECTUREH
#define LECTUREH
#include <stdio.h>
#include "liste.h"
#include "menu.h"

int lecture_paquet(FILE*f,char*c);
char* lecture_paquet_sans_frag(char *filename);
liste* lecture_fichier(char *filename,char** tabadd);
int decapsuler(char* paquet,filter* filtre,int n,FILE* f,char** tabadd,int n2);
void affichage_liste(liste *l,filter *f,char* filename,char **tabadd,int n2);
int addtableau(char* paquet, char** tabadd, int i);
void printFLOWCHART(char* source, char* dest, char** tabadd,FILE* f,int n2);

#endif
