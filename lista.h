/*
    Número do grupo: 09
    Nome dos integrantes: Nathan Rodrigues de Souza Monteiro, 
                          Lucas Emanuel Lopes Tavares, 
                          Isadora Fernandes Santos, 
                          Murylo Dias de Oliveira Rubim
*/

#ifndef INCLUDED_LISTA_H
#define INCLUDED_LISTA_H

#include <stdio.h>

typedef struct dna {
    struct dna* prox; 
    int indice;
    char* identificador;
    char* dnaAnimal;
} DnaAnimal;

typedef struct listaAnimal{
    int qtd;
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
void insereVirusNoFim(ListaVirus *listaVirus, Virus *noVirus);
Virus* criaNoVirus();
DnaAnimal* criaNoDnaAnimal();
DnaAnimal* buscaIndice(ListaAnimal *listaAnimal, int indice);

#endif