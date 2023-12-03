#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
    char* transa = "xSexox";
    char* sexo = (char *)calloc(sizeof(transa),sizeof(char));
    
    strcpy(sexo,"Sexox");
    
    printf("%s",transa);
}