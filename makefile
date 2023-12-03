# Número do grupo: 09
# Nome dos integrantes: Nathan Rodrigues de Souza Monteiro, 
#                       Lucas Emanuel Lopes Tavares, 
#                       Isadora Fernandes Santos, 
#                       Murylo Dias de Oliveira Rubim


CC = gcc
FLAGS = -Wall -Wextra -Werror

all: teste # Target responsável por chamar o target teste, 
	./main # e em seguita executa o executável main.

teste: main.o lista.o          			  # O teste chama os targets main.o e lista.o
	$(CC) $(FLAGS) -o main main.o lista.o # compila os objetos main.o e lista.o 
					           			  # e os transforma em um executável chamado main

main.o: main.c lista.h
	$(CC) $(FLAGS) -c main.c # compila o main.c 

lista.o: lista.c lista.h	
	$(CC) $(FLAGS) -c lista.c # compila a lista.c

clean: 
	rm -r main *.o *.out # remove do respectivo diretório todos os .o e .out 
						 # de forma recursiva
