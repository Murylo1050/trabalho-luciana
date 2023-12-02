#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

ListaVirus* criaListaVirus() {
    ListaVirus* lista = (ListaVirus*)calloc(1,sizeof(ListaVirus));
    
    if (lista) {
        lista -> ini = NULL;
        lista -> fim = NULL;
        return lista;
    }else{
        exit(1);
    }
}

ListaAnimal* criaListaAnimal() {
    ListaAnimal* lista = (ListaAnimal*)calloc(1,sizeof(ListaAnimal));
    
    if (lista) {
        lista -> ini = NULL;
        lista -> fim = NULL;
        return lista;
    }else{
        exit(1);
    }
}


Virus* criaNoVirus() {
    Virus* novo = (Virus*)calloc(1,sizeof(Virus));
    
    if (novo) {
        novo -> prox = NULL;
        return novo;
    } else {
        exit(1);
    }

    return novo;
}

DnaAnimal* criaNoDnaAnimal() {
    DnaAnimal* novo = (DnaAnimal*)calloc(1, sizeof(DnaAnimal));
    
    if (novo) {
        return novo;
    } else {
        exit(1);
    }

    return novo;
}

void insereAnimalNoFim(ListaAnimal *listaAnimal, DnaAnimal *noAnimal) {
    ListaAnimal* lista = listaAnimal;

    if (lista -> ini == NULL) {
        lista -> ini = noAnimal;
        lista -> fim = noAnimal;
    } else {
        lista -> fim -> prox = noAnimal;
        lista -> fim = noAnimal;
    }
}

void insereNoFim(ListaVirus *listaVirus, Virus* noVirus) {

    ListaVirus* lista = listaVirus;
    if (lista -> ini == NULL) {
        lista -> ini = noVirus;
        lista -> fim = noVirus;
    } else {
        lista -> fim -> prox = noVirus;
        lista -> fim = noVirus;
    }
}
/*
nomeOcorrencia pegaDNA(){
    criar no ocorrencia
    Line = primeira linha ">fulano"
    no.nome = line
    line = proxlinha
    char* DNA malloc 70*char
    int contL = 0;

    while(Line[0] != >){
        if(DNA[0] == ""){
            DNA = line 
        }else{
            contL++
            realoc DNA pra 70*contL*char
            concacatena DNA + line
        }
       
        line = proxima LInha
    }

    no.dna = DNA

    retorna  no

    */