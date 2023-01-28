#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/liste.h"

liste *create_cell_liste() {
  liste *cell = (liste *) malloc(sizeof(liste));

  if (cell == NULL) {
    fprintf(stderr, "ERREUR ALLOCATION CREATE_CELL_LISTE\n");
    exit(EXIT_FAILURE);
  }

  cell->paquet = (char *) calloc (10000,1);
  cell->next = NULL;

  return cell;
}

void delete_cell_liste(liste *c) {
  free(c->paquet);
  free(c);
}

void delete_liste(liste *list) {
  liste *tmp=list;
  liste *next;

  while (tmp != NULL) {
    next = tmp->next;
    delete_cell_liste(tmp);
    tmp = next;
  }
}