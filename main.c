#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

ListaVirus* leVirus(char* path) {
    FILE *file = fopen(path, "r"); 
    char teste = getc(file);
    char* dna = (char *)calloc(70,sizeof(char));

    char* temp; 
    /* 
    Variável responsável por armazenar de forma temporária a primeira
    linha do arquivo, e caso aconteça, as concatenações com as outras linhas.
    */ 

    ListaVirus* lista = criaListaVirus();
    Virus* noVirus = NULL;

    while(teste != EOF) {
        if(teste == '>') {
            fscanf(file, "%m[^\n]", &temp);
            
            if(strcmp(temp,">EOF") == 0 ) {
                free(temp);
                return lista;
            } else {
                noVirus = criaNoVirus();
                noVirus->identificador = (char *)calloc(71,sizeof(char));
                strcpy(noVirus->identificador,temp);
                free(temp);
            }
        } else {
            if(teste == '\n') { 
                fseek(file, ftell(file)+1, SEEK_SET); 

            } else {
                fscanf(file, "%m[^\n]", &noVirus->dnaVirus);
            }    
        }
        teste = fgetc(file);   

        if(teste == '>') {
            insereVirusNoFim(lista, noVirus);
            noVirus = NULL;
        } else {
            fseek(file, ftell(file)-1, SEEK_SET);
        }
    }

    fclose(file);

    return lista;
}

ListaAnimal* leAnimal(char *path) {
    FILE *file = fopen(path, "r");
    char teste = getc(file);
    char* dna;
    char* temp;

    ListaAnimal* lista = criaListaAnimal();
    DnaAnimal* noAnimal = NULL;

    while(teste != EOF) {
        if(teste == '>') {
            //Armazena a linha referente ao código/nome do animal no ponteiro *animal
           
            fscanf(file, "%m[^\n]", &temp);
            dna = (char *)calloc(70,sizeof(char));
            
            if(strcmp(temp,">EOF") == 0 ) {
                free(temp);
                return lista;
            } else {
                noAnimal = criaNoDnaAnimal();

                noAnimal->identificador = (char *)calloc(71,sizeof(char));
                strcpy(noAnimal->identificador,temp);
                free(temp);
            } 
        } else {
            if(teste == '\n') { 
                fseek(file, ftell(file)+1, SEEK_SET);    
                /*                
                Caso o teste esteja apontando para a quebra de linha, o fseek fará que o mesmo aponte
                para o próximo endereço do arquivo                
                */                                                              
            } else {
                /*
                Armazena a linha referente ao DNA do animal no ponteiro *dna.
                A cada iteração do while uma linha é armazenada no ponteiro.
                */
                if(dna[0] == 0) {
                    fscanf(file, "%m[^\n]", &temp);
                    dna = strcpy(dna, temp);
                } else {
                    dna = (char *)realloc(dna,(strlen(dna) * sizeof(char)) + (70 * sizeof(char)) );
                    fscanf(file, "%m[^\n]", &temp);
                    strcat(dna,temp);
                }                
            }    
        }
        
        teste = fgetc(file);   

        if(teste == '>') {
            noAnimal->dnaAnimal = dna;
            insereAnimalNoFim(lista, noAnimal);
            noAnimal->indice = lista->qtd;
            lista->qtd++;
            noAnimal = NULL;
        } else {
            fseek(file, ftell(file)-1, SEEK_SET);
        }
    }

    fclose(file);

    return lista;
}

int* vetorDeslocamento(char* virus) {
    // Função prefixo para obter a "tabela" de deslocamentos
    int* vetorDeslocamento = (int *)calloc(strlen(virus),sizeof(int));
    int i = 1; int j = 0;
    
    while(i < strlen(virus)) {
        if(virus[i] == virus[j]) {
            j++;
            vetorDeslocamento[i] = j;
            i++;           
        } else {
            if(j != 0) {
                j = vetorDeslocamento[j-1];       
            } else {
                vetorDeslocamento[i] = 0;
                i++;
            }
        }
    }

    return vetorDeslocamento;
}

void kmp(ListaAnimal* listaAnimal, ListaVirus* listaVirus) {
    int indiceVirus , indiceAnimal;   
     // Contador para a quantidade de vírus em um DNA
       
    DnaAnimal* auxAnimal = listaAnimal->ini;
    Virus* auxVirus = listaVirus->ini;
    int cont;

    while(auxVirus != NULL) {
        
        char* dnaVirus = auxVirus->dnaVirus;
        int* vetorDesloc = vetorDeslocamento(dnaVirus);
        int contadorAparicoes; // Contador para a quantidade de vírus em um DNA
        cont = 0; 
        
        auxVirus->aparicoes = (int **)calloc(listaAnimal->qtd,sizeof(int *));

        while(auxAnimal != NULL) {
            indiceVirus = 0; indiceAnimal = 0;
            char* dnaAnimal = auxAnimal->dnaAnimal;
            int tamDNA = strlen(dnaAnimal), tamVirus = strlen(dnaVirus);
            contadorAparicoes = 0;
            int* indicesMatches = (int *)calloc(4,sizeof(int));
                    int numIndices = 1, numMaxIndices = 3; 
                    // Índices utilizados para o vetor com as posições em que o vírus aparece no DNA
            
            while(indiceAnimal <= tamDNA) {        
                if(indiceVirus < tamVirus) {
                    if(dnaAnimal[indiceAnimal] == dnaVirus[indiceVirus]) {
                        indiceVirus++; indiceAnimal++;
                    } else {
                        if(indiceVirus == 0) {
                            indiceAnimal++;
                        } else {
                            indiceVirus = vetorDesloc[indiceVirus - 1];   
                        }
                    }
                } else {          
                    if(numIndices <= numMaxIndices) { 
                        indicesMatches[numIndices] = indiceAnimal - tamVirus;               
                        numIndices++;
                        indiceVirus = 0;
                        
                        contadorAparicoes++;
                    } else {
                        numMaxIndices += 3;
                        indicesMatches = (int*)realloc(indicesMatches, numMaxIndices * sizeof(int));
                        indicesMatches[numIndices] = indiceAnimal - tamVirus;
                        numIndices++;
                        indiceVirus = 0;

                        contadorAparicoes++;
                    }
                }               
            }

            indicesMatches[0] = contadorAparicoes;
            auxVirus->aparicoes[cont] = (int *)calloc(numIndices,sizeof(int));
            for(int i = 0; i < numIndices; i++) {
                auxVirus->aparicoes[cont][i] = indicesMatches[i];
            }
            cont++;        
                
            auxAnimal = auxAnimal->prox;
            free(indicesMatches);
        }
        auxVirus = auxVirus->prox;
        auxAnimal = listaAnimal->ini;
    }

    auxVirus = listaVirus->ini;
    
    int j = 0;
    int i = 0;
    int qtdAnimais = listaAnimal->qtd;
    
    while(auxVirus != NULL) {
        printf("\n%s",auxVirus->identificador);

        for(i = 0; i < qtdAnimais ; i++) {
            if(auxVirus->aparicoes[i][0] != 0) {
                DnaAnimal* auxAnimal = buscaIndice(listaAnimal,i);
                printf("\n[%s] ",auxAnimal->identificador);
            }
            for(j = 0; j <= auxVirus->aparicoes[i][0]; j++) {
                if(auxVirus->aparicoes[i][0] == 0) {
                    break;
                } else {
                    if(j == 0) {
                        printf("no. de ocorrencias: %d posicoes: ", auxVirus->aparicoes[i][0]);
                    } else {
                        printf("%d ",auxVirus->aparicoes[i][j]);
                    }
                }
            }                    
        }
        
        printf("\n");
        auxVirus = auxVirus->prox;
        }
  
    // A primeira posição do vetor contém a quantidade de vezes que o vírus apareceu
    free(auxAnimal);
    free(auxVirus);
}

void main(int argc, char *argv[]) {
    ListaAnimal* animais = leAnimal(argv[1]);
    ListaVirus*  virus = leVirus(argv[2]);
    kmp(animais,virus);   
}