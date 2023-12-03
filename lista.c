#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

ListaVirus* criaListaVirus() {
    ListaVirus* lista = (ListaVirus*)calloc(1,sizeof(ListaVirus));
    
    if(lista) 
        return lista;
    else 
        exit(1);    
}

ListaAnimal* criaListaAnimal() {
    ListaAnimal* lista = (ListaAnimal*)calloc(1,sizeof(ListaAnimal));
    
    if(lista)
        return lista;
    else 
        exit(1);    
}

Virus* criaNoVirus() {
    Virus* novo = (Virus*)calloc(1,sizeof(Virus));
    
    if(novo) 
        return novo;
    else 
        exit(1);
}

DnaAnimal* criaNoDnaAnimal() {
    DnaAnimal* novo = (DnaAnimal*)calloc(1, sizeof(DnaAnimal));
    
    if(novo) 
        return novo;
    else 
        exit(1);
}

void insereAnimalNoFim(ListaAnimal *listaAnimal, DnaAnimal *noAnimal) {
    ListaAnimal* lista = listaAnimal;

    if(!lista -> ini) {
        lista -> ini = noAnimal;
        lista -> fim = noAnimal;
        noAnimal->indice = 1;
    } else {
        noAnimal->indice = lista->fim->indice + 1; 
        lista -> fim -> prox = noAnimal;
        lista -> fim = noAnimal;
    }
}

void insereVirusNoFim(ListaVirus *listaVirus, Virus* noVirus) {
    ListaVirus* lista = listaVirus;
    
    if(!lista -> ini) {
        lista -> ini = noVirus;
        lista -> fim = noVirus;
    } else {
        lista -> fim -> prox = noVirus;
        lista -> fim = noVirus;
    }
}

DnaAnimal* buscaIndice(ListaAnimal *listaAnimal, int indice) {
    DnaAnimal *auxAnimal = listaAnimal->ini;

    while(auxAnimal && auxAnimal->indice != indice) 
        auxAnimal = auxAnimal->prox;
    
    return auxAnimal;
}