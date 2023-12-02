#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

/* 
lista* pegaVirus(){
    crialista()
    while(){
        cria noVirus
        Line = primeira linha ">fulano"
        noVirus.identificador = line

        line = prox linha que é o dna
        noVirus.dna = line
        
        insereLista(lista,noVirus)
    }
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

}    



*/
//ListaAnimal* leDNA(FILE* file){
 //   ListaAnimal* lista = criaListaAnimal();

    //char* nomeAninimal;
    

    /*
    pegar codigo do animal

    criar no: no -> identificador = codigo do animal
              no -> dnaAnimal = caracteres do arquivo
              Inserir na Lista
    */ 
     
//}







/*
typedef struct dna {
    char* identificador;
    char* dnaAnimal;
    int* ocorrencias;
} dnaAnimal;

*/

void leDNA(char *path) {
    FILE *file = fopen(path, "r");
    char teste = getc(file);
    char* dna = (char *)calloc(70,sizeof(char));

    char* temp;

    ListaAnimal* lista = criaListaAnimal();
    DnaAnimal* noAnimal = NULL;

    while(teste != EOF) {
        if(teste == '>') {
            //Armazena a linha referente ao código/nome do animal no ponteiro *animal
           
            fseek(file, ftell(file)-1, SEEK_SET);
            fscanf(file, "%m[^\n]", &temp);

            if(temp == ">EOF"){
                free(temp);
                printf("Deu certo krl");
                exit(1);
            }else{
                noAnimal = criaNoDnaAnimal();
                noAnimal->identificador = temp;
                printf("%s\n", noAnimal->identificador);
                free(temp);
            }
            

            
        }
        else {
            if(teste == '\n'){ 
                fseek(file, ftell(file)+1, SEEK_SET); // Caso o teste esteja apontando para a quebra de linha o fseek fará que o mesmo  
                                                        // aponte para o próximo endereço do arquivo.                                                                   
            }else {
                // Armazena a linha referente ao dna do animal no ponteiro *dna. 
                // A cada iteração do while uma linha é armazenada no ponteiro.

                fseek(file, ftell(file), SEEK_SET);
                fscanf(file, "%m[^\n]", &noAnimal->dnaAnimal);
                printf("%s\n", noAnimal->dnaAnimal);
                
            }    
        }
        teste = fgetc(file);   

        if(teste == '>') {
            insereAnimalNoFim(lista, noAnimal);
            noAnimal = NULL;
        }else{
            fseek(file, ftell(file)-1, SEEK_SET);
        }
    }

    fclose(file);
}


int* vetorDeslocamento(char* virus) {
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

int* kmp(char* dna, char* virus) {
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

void main(int argc, char *argv[]) {
    char* dna = "CGATAATGACCAGTATGA";
    char* virus = "ATGA";

    int* teste = kmp(dna,virus);

    leDNA(argv[1]);
    
    printf("Quantidade: %d\nIndice: %d | %d",teste[0],teste[1], teste[2] );
    
}


