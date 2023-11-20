FLAGS = -Wall -Wextra -Werror

all: teste 
	./mainn 
	rm -r mainn *.o #gambiarra pode apagar

in: teste
	./mainn input/dna.txt

debug: 
	gcc -g main.c 

teste: mainn.o
	gcc -o mainn mainn.o  

mainn.o: 
	gcc -c mainn.c 

clean: 
	rm -r mainn *.o
