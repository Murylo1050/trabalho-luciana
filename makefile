FLAGS = -Wall -Wextra -Werror

all: teste 
	./mainn 
	rm -r mainn *.o #gambiarra pode apagar essa linha

in: teste
	./mainn input/dna.txt
	rm -r mainn *.o #gambiarra pode apagar essa linha

debug: 
	gcc -g mainn.c 

teste: mainn.o
	gcc -o mainn mainn.o  

mainn.o: 
	gcc -c mainn.c 

clean: 
	rm -r mainn *.o *.out
