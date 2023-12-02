#ifndef INCLUDED_LISTA_H
#define INCLUDED_LISTA_H

#include <stdio.h>

typedef struct dna {
    struct dna* prox; // Mod
    char* identificador;
    char* dnaAnimal;
} DnaAnimal;

typedef struct listaAnimal{
    DnaAnimal* ini;
    DnaAnimal* fim;
} ListaAnimal;

typedef struct virus {
    struct virus* prox;
    char* identificador;
    char* dnaVirus;
    int** aparicoes;
} Virus;

typedef struct listaVirus {
    Virus* ini;
    Virus* fim;
} ListaVirus;

ListaVirus* criaListaVirus();
ListaAnimal* criaListaAnimal();
void insereAnimalNoFim(ListaAnimal *listaAnimal, DnaAnimal *noAnimal); // mod
void insereNoFim(ListaVirus *listaVirus, Virus *noVirus);
Virus* criaNoVirus();
DnaAnimal* criaNoDnaAnimal();
void leDNA(char *path);

#endif