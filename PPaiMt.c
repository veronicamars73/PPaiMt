#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesdeimagem.h"
#include "funcoesdearquivo.h"

int main()
{
	//A variável arquivo_imagem é o arquivo de imagem que será editado 
	FILE *arquivo_imagem;
	//A variável maximo armazena o valor máximo possível para as cores no arquivo
	//A variável coratual (Extremamente usada nas funções de imagem) armazena a cor utilizada na próxima ação 
	Pixel maximo, coratual;
	//A variável test indica a condição de parada do programa
	int i, test=1;
	//A variável desenho representa o desenho a ser editado, ela armazena o valor de cada pixel da imagem e as dimensões dela
	Imagem desenho;
	//A variável comando armazena o comando lido
	char *comando;
	maximo.vermelho=255;maximo.verde=255;maximo.azul=255;
	comando = calloc(8, sizeof(char));
	
	while(test){
		printf("Digite o comando: ");
		scanf("%s", comando);
		test = defineComando(comando, &desenho, &coratual, maximo, arquivo_imagem);
	}
	for (i = 0; i < desenho.altura; ++i){
		free(desenho.pintura[i]);
	}
	free(desenho.pintura);
	return 0;
}