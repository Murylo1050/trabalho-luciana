#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lerArquivo(char *path) {
    FILE *file = fopen(path, "r");

    char *dna = NULL, *animal = NULL;
    char teste = getc(file);
    int escalar = 1;

    while(teste != EOF) {
        if(teste == '>' ) {
            //Armazena a linha referente ao código/nome do animal no ponteiro *animal
            fseek(file, ftell(file)-1, SEEK_SET);
            fscanf(file, "%m[^\n]", &animal);
            printf("%s\n", animal);
        }
        else {
            if(teste == '\n') 
                fseek(file, ftell(file)+1, SEEK_SET); // Caso o teste esteja apontando para a quebra de linha o fseek fará que o mesmo  
                                                      // aponte para o próximo endereço do arquivo.                                                                   
            else {
                // Armazena a linha referente ao dna do animal no ponteiro *dna. 
                // A cada iteração do while uma linha é armazenada no ponteiro.
                fseek(file, ftell(file), SEEK_SET);
                fscanf(file, "%m[^\n]", &dna);
                printf("%s\n", dna);
            }    
        }
        teste = fgetc(file);   
    }
    free(dna);
    free(animal);
    fclose(file);
}

void main (int argc, char *argv[]){
    if(argc < 2)
        printf("Ta faltando argumento, mano!\n");
    else 
        lerArquivo(argv[1]);
}
