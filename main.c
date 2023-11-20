#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int* vetorDeslocamento(char* virus){
    // Função prefixo para obter a "tabela" de deslocamentos
    int* vetorDeslocamento = (int *)malloc(sizeof(int) * strlen(virus));
    int i = 1; int j = 0;
    
    while (i < strlen(virus)) {
        if (virus[i] == virus[j]) {
            j++;
            vetorDeslocamento[i] = j;
            i++;
           
        } else {
            if (j != 0) {
                j = vetorDeslocamento[j-1];
            } else {
                vetorDeslocamento[i] = 0;
                i++;
            }
        }
    }

    return vetorDeslocamento;
}

int* kmp(char* dna, char* virus){
    int indiceVirus = 0, indiceDNA = 0;
    int tamDNA = strlen(dna), tamVirus = strlen(virus);
    
    int numIndices = 1, numMaxIndices = 3; // Índices utilizados para o vetor com as posições em que o vírus aparece no DNA
    int* indicesMatches = (int *)malloc(sizeof(int)*4);

    int contadorAparicoes = 0; // Contador para a quantidade de vírus em um DNA
    
    int* vetorDesloc = vetorDeslocamento(virus);

    while (indiceDNA <= (int)strlen(dna)) {        
        if (indiceVirus < tamVirus) {
            if (dna[indiceDNA] == virus[indiceVirus]) {
                indiceVirus++; indiceDNA++;
            } else {
                if (indiceVirus == 0) {
                    indiceDNA++;
                } else {
                    indiceVirus = vetorDesloc[indiceVirus - 1];   
                }
            }
        } else {          
            if (numIndices <= numMaxIndices) { 
                indicesMatches[numIndices] = indiceDNA - tamVirus;               
                numIndices++;
                indiceVirus = 0;
                
                contadorAparicoes++;
            } else {
                numMaxIndices += 3;
                indicesMatches = (int*)realloc(indicesMatches, numMaxIndices * sizeof(int));
                indicesMatches[numIndices] = indiceDNA - tamVirus;
                numIndices++;
                indiceVirus = 0;

                contadorAparicoes++;
            }
        } 
    }

    indicesMatches[0] = contadorAparicoes; // A primeira posição do vetor contém a quantidade de vezes que o vírus apareceu
    return indicesMatches;
}

void main(){
    char* dna = "CGATAATGACCAGTATGA";
    char* virus = "ATGA";

    int* teste = kmp(dna,virus);

    printf("Quantidade: %d\nIndice: %d | %d",teste[0],teste[1], teste[2] );
    
}


