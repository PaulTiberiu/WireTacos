#ifndef LISTEH
#define LISTEH

//structures

typedef struct _liste {
  char *paquet;
  struct _liste *next;
} liste;

liste *create_cell_liste();
void delete_cell_liste(liste *c);
void delete_liste(liste *list);


#endif