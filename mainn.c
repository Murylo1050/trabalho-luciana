#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main (int argc, char *argv[]){
    FILE* file = fopen(argv[1], "r");

    char *dna, *animal, teste = getc(file);
    int posicao = 1, escalar = 1;

   while(teste != EOF) {
        if(teste == '>') {
            printf("\nEntrou!\n");
            fseek(file, ftell(file)-1, SEEK_SET); 
            fscanf(file, "%m[^\n]", &animal);
            printf("%s\n", animal);
        }
        else {
            printf("\nEntrou222\n");
            fseek(file, ftell(file)-1, SEEK_SET);
            fscanf(file, "%m[^\n]", &dna);
            printf("%s\n", dna);
        }
    
        posicao = 70 * escalar;
        ++escalar;
        teste = getc(file);
    }

    // while(getc(file) != EOF) {
    //     if(teste == '>') {
    //         fscanf(file, "%m[^\n]", &animal);
    //         printf("%s\n", animal);
    //     }
        
    //     fseek(file, ftell(file)+1, SEEK_SET);
    //     fscanf(file, "%m[^\n]", &dna);
    //     printf("%s\n", dna);
    
    //     posicao = 70 * escalar;
    //     ++escalar;

    // }

    fclose(file);
}
