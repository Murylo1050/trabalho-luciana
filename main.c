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
ListaVirus* leVirus(char* path){
     FILE *file = fopen(path, "r");
    char teste = getc(file);
    char* dna = (char *)calloc(70,sizeof(char));

    char* temp;

    ListaVirus* lista = criaListaVirus();
    Virus* noVirus = NULL;

    while(teste != EOF) {
        if(teste == '>') {
            //Armazena a linha referente ao código/nome do animal no ponteiro *animal
           
            fseek(file, ftell(file)-1, SEEK_SET);
            fscanf(file, "%m[^\n]", &temp);
            
            if( strcmp(temp,">EOF") == 0 ){
                free(temp);
                printf("Deu certo krl");
                exit(1);
            }else{
                noVirus = criaNoVirus();
                noVirus->identificador = temp;
                printf("%s\n", noVirus->identificador);
                free(temp);
            }
            

            
        }
        else {
            if(teste == '\n') { 
                fseek(file, ftell(file)+1, SEEK_SET); // Caso o teste esteja apontando para a quebra de linha o fseek fará que o mesmo  
                                                        // aponte para o próximo endereço do arquivo.                                                                   
            } else {
                // Armazena a linha referente ao dna do animal no ponteiro *dna. 
                // A cada iteração do while uma linha é armazenada no ponteiro.

                //fseek(file, ftell(file), SEEK_SET);
                fscanf(file, "%m[^\n]", &noVirus->dnaVirus);
                printf("%s\n", noVirus->dnaVirus);
                
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


ListaAnimal* leDNA(char *path) {
    FILE *file = fopen(path, "r");
    char teste = getc(file);
    char* dna;

    char* temp;

    ListaAnimal* lista = criaListaAnimal();
    DnaAnimal* noAnimal = NULL;

    while(teste != EOF) {
        lista->qtd++;
        if(teste == '>') {
            //Armazena a linha referente ao código/nome do animal no ponteiro *animal
           
            fseek(file, ftell(file)-1, SEEK_SET);
            fscanf(file, "%m[^\n]", &temp);
            dna = (char *)calloc(70,sizeof(char));
            
            if(strcmp(temp,">EOF") == 0 ) {
                free(temp);
                printf("Deu certo krl");
                exit(1);
            } else {
                noAnimal = criaNoDnaAnimal();
                noAnimal->identificador = temp;
                printf("%s\n", noAnimal->identificador);
                free(temp);
            } 
        } else {
            if(teste == '\n') { 
                fseek(file, ftell(file)+1, SEEK_SET); // Caso o teste esteja apontando para a quebra de linha o fseek fará que o mesmo  
                                                        // aponte para o próximo endereço do arquivo.                                                                   
            } else {
                // Armazena a linha referente ao dna do animal no ponteiro *dna. 
                // A cada iteração do while uma linha é armazenada no ponteiro.

                //fseek(file, ftell(file), SEEK_SET);

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
            printf("%s\n",dna);
            noAnimal->dnaAnimal = dna;
            insereAnimalNoFim(lista, noAnimal);
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
    int* vetorDeslocamento = (int *)malloc(sizeof(int) * strlen(virus));
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
    
    int numIndices = 1, numMaxIndices = 3; // Índices utilizados para o vetor com as posições em que o vírus aparece no DNA
    int* indicesMatches = (int *)calloc(4,sizeof(int));

     // Contador para a quantidade de vírus em um DNA
    
    

    DnaAnimal* auxAnimal = listaAnimal->ini;
    Virus* auxVirus = listaVirus->ini;

    int cont;
    while(auxVirus->prox != NULL){
        indiceVirus = 0; indiceAnimal = 0;
        int numIndices = 1, numMaxIndices = 3; 
        char* dnaVirus = auxVirus->dnaVirus;
        int* vetorDesloc = vetorDeslocamento(dnaVirus);
        int contadorAparicoes = 0; // Contador para a quantidade de vírus em um DNA
        cont = 0; 

        auxVirus->aparicoes = (int **)calloc(listaAnimal->qtd,sizeof(int *));

        while(auxAnimal->prox != NULL){
            char* dnaAnimal = auxAnimal->dnaAnimal;
            int tamDNA = strlen(dnaAnimal), tamVirus = strlen(dnaVirus);
            
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
                
                indicesMatches[0] = contadorAparicoes;
                auxVirus->aparicoes[cont] = indicesMatches;
            }
            cont++;

            printf("%s\n [%s] no. de ocorrencias: %d posições: ", auxVirus->identificador, auxAnimal->identificador, indicesMatches[0]);
            for(int i = 1; i < numIndices; i++) {
                printf("%d",indicesMatches[i]);
            }
        }

        
    }


     // A primeira posição do vetor contém a quantidade de vezes que o vírus apareceu
    free(auxAnimal);
    free(auxVirus);
}

void main(int argc, char *argv[]) {
    
    ListaAnimal* animais = leDNA(argv[1]);
    ListaVirus*  virus = leVirus(argv[2]);
    kmp(animais,virus); // dps colcoar o le dna e ler virus ai dentro

    
    
    //printf("Quantidade: %d\nIndice: %d | %d",teste[0],teste[1], teste[2] );
    
}


