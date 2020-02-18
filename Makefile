all: PPaiMt

PPaiMt: funcoesdearquivo.o funcoesdeimagem.o PPaiMt.c
	gcc PPaiMt.c -o PPaiMt funcoesdearquivo.o funcoesdeimagem.o

funcoesdearquivo.o: funcoesdearquivo.c
	gcc -c funcoesdearquivo.c

funcoesdeimagem.o: funcoesdeimagem.c
	gcc -c funcoesdeimagem.c
	
clean:
	rm -f *.o