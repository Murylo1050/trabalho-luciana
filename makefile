FLAGS = -Wall -Wextra -Werror

all: teste 
	# rm -r main *.o #gambiarra pode apagar essa linha

in: teste
	./main input/dna.txt input/virus.txt
	rm -r main *.o #gambiarra pode apagar essa linha

debug: 
	gcc -g main.c lista.c

teste: main.o lista.o
	gcc -o main main.o lista.o

main.o: main.c lista.h
	gcc -c main.c 

lista.o: lista.c lista.h	
	gcc -c lista.c

clean: 
	rm -r main *.o *.out
