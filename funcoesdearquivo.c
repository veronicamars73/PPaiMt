#include "funcoesdeimagem.h"
#include <stdio.h>
#include <stdlib.h>


void criaArquivo(char nomedoarquivo[], Imagem *desenho, int maximo, FILE *arquivo){
	//Essa função é responsável por salvar a imagem ppm com base nas informações da variável desenho
	int i,j;
	//A linha abaixo começa a escrever no arquivo com o nome informado pelo usuário
	arquivo = fopen(nomedoarquivo, "w");
	//As linhas seguintes editam o arquivo no modelo ppm
	fprintf(arquivo, "P3\n");
	fprintf(arquivo, "%d %d\n", desenho->largura, desenho->altura);
	fprintf(arquivo, "%d\n", maximo);
	for (i = 0; i < desenho->altura; ++i){
		for (j = 0; j < desenho->largura; ++j){
			fprintf(arquivo, "%d %d %d\n", desenho->pintura[i][j].vermelho, desenho->pintura[i][j].verde, desenho->pintura[i][j].azul);
		}
	}
	fclose(arquivo);
}

void save(Imagem *desenho, Pixel maximo, FILE *arquivo){
	//Essa função é respomsável por ler o nome desejado para o arquivo de imagem e passa essa informação para a função
	//criaArquivo
	char nomedoarquivo[200];
	printf("Digite o nome do arquivo: ");
	scanf("%s", nomedoarquivo);
	puts(nomedoarquivo);
	criaArquivo(nomedoarquivo, desenho, maximo.verde, arquivo);
}

void criaPreArquivo(Imagem *desenho){
	//Essa função cria o arquivo "prearquivo2.ppm" que armazena o estado atual da imagem que está sendo editada
	FILE *prearquivo;
	criaArquivo("prearquivo2.ppm", desenho, 255, prearquivo);
}

void criaPrimeiroArquivo(Imagem *desenho){
	//Essa função cria o arquivo "prearquivo.ppm" que armazena o estado da imagem que está sendo editada uma função
	//antes do estado atual
	FILE *prearquivo;
	criaArquivo("prearquivo.ppm", desenho, 255, prearquivo);
	system("cp prearquivo.ppm prearquivo2.ppm");
}

void atualizaBackup(){
	system("cp prearquivo2.ppm prearquivo.ppm");
}

void abreGaleria(char nomedoarquivo[]){
	//Essa função é responsável por abrir a imagem que está sendo editada
	//As linhas seguintes criam um script que instala a biblioteca eog e abre a imagem que está sendo editada
	FILE *arquivo;
	arquivo = fopen("abreimg.sh", "w");
	fprintf(arquivo, "#!/bin/bash\n");
	fprintf(arquivo, "sudo apt-get install eog\n");
	fprintf(arquivo, "eog ");
	fputs(nomedoarquivo, arquivo);
	fclose(arquivo);
	system("chmod 777 abreimg.sh");
	//A linha abaixo executa o script criado
	system("./abreimg.sh");
}

void open(Imagem *desenho, int maximo){
	//Essa função é responsável por executar a função abreGaleria
	FILE *bckup;
	abreGaleria("prearquivo2.ppm");
}

void rotinaBackups(Imagem *desenho){
	//Essa função controla as funções envolvidas no backup e na funcionalidade de desfazer um comando
	/*
	A função atualizaBackup copia o conteúdo do arquivo "prearquivo2.ppm" no arquivo "prearquivo.ppm" fazendo 
	ele armazenar o estado da imagem editada uma ação anterior a ação atual, já a função criaPreArquivo cria um 
	arquivo ppm chamado "prearquivo2.ppm" que armazenaa o estado atual da imagem editada.
	Por exemplo, caso o usuário utilize a funcionalidade do círculo e em seguida a funcionalidade do polígono, nesse
	caso o arquivo "prearquivo.ppm" estará armazenando apenas o círculo, enquanto o arquivo "prearquivo2.ppm" possui 
	o círculo e o polígono.
	*/
	atualizaBackup();
	criaPreArquivo(desenho);
}

void apagaBackups(){
	//Essa função remove os arquivos "prearquivo.ppm" e "prearquivo2.ppm" utilizados durante a execução do programa
	system("rm prearquivo.ppm");
	system("rm prearquivo2.ppm");
}

void desfaz(Imagem *desenho){
	//Essa função desfaz o último comando feito feito pelo usuário
	/*
	Como explicado na função rotinaBackups o arquivo "prearquivo2.ppm" armazena o estado atual da imagem editada
	e o arquivo "prearquivo.ppm" armazena o estado da imagem editada uma ação antes,
	A linha abaixo copia o conteúdo do arquivo "prearquivo.ppm" para o arquivo "prearquivo2.ppm", ou seja, o 
	estado atual da imagem torna-se igual ao armazenado em "prearquivo.ppm", desfazendo assim a última ação feita 
	pelo usuário.
	*/
	system("cp prearquivo.ppm prearquivo2.ppm");
	FILE *arquivo_bk;
	int i, j, val[3];
	char lixo[4];
	//As linhas abaixo modificam o valor da variável desenho para que fique de acordo com as informações presentes
	//no arquivo "prearquivo2.ppm"
	arquivo_bk = fopen("prearquivo2.ppm", "r");
	fscanf(arquivo_bk, "%s", lixo);
	fscanf(arquivo_bk, "%d %d %d", &val[0], &val[1], &val[2]);
	for (i = 0; i < desenho->altura; ++i){
		for (j = 0; j < desenho->largura; ++j){
			fscanf(arquivo_bk, "%d %d %d", &val[0], &val[1], &val[2]);
			desenho->pintura[i][j].vermelho = val[0];
			desenho->pintura[i][j].verde = val[1];
			desenho->pintura[i][j].azul = val[2];
		}
	}
	fclose(arquivo_bk);
}

int defineComando(char *comando, Imagem *desenho, Pixel *coratual, Pixel maximo, FILE *arquivo){
	//Essa função é responsável por identificar qual funcionalidade do programa o usuário quer ter acesso e
	//direcioná-lo até ela
	if(strcmp(comando,"image")==0){
		image(desenho);
		criaPrimeiroArquivo(desenho);
		return 1;
	}else{
		if (strcmp(comando,"clear")==0){
			clear(desenho);
			rotinaBackups(desenho);
			return 1;
		}else{
			if(strcmp(comando,"color")==0){
				color(coratual);
				rotinaBackups(desenho);
				return 1;
			}else{
				if(strcmp(comando,"line")==0){
					line(*coratual, desenho);
					rotinaBackups(desenho);
					return 1;
				}else{
					if (strcmp(comando,"polygon")==0){
						polygon(*coratual, desenho);
						rotinaBackups(desenho);
						return 1;
					}else{
						if (strcmp(comando,"circle")==0){
							circle(*coratual, desenho);
							rotinaBackups(desenho);
							return 1;
						}else{
							if (strcmp(comando,"rect")==0){
								rect( *coratual, desenho);
								rotinaBackups(desenho);
								return 1;
							}else{
								if (strcmp(comando,"fill")==0){
									fill(*coratual, desenho);
									rotinaBackups(desenho);
									return 1;
								}else{
									if (strcmp(comando,"save")==0){
										save(desenho, maximo, arquivo);
										apagaBackups();
										return 0;
									}else{
										if (strcmp(comando,"open")==0){
											open(desenho, maximo.verde);
											return 1;
										}else{
											if (strcmp(comando,"undo")==0){
												desfaz(desenho);
												return 1;
											}else{
												printf("Comando Inválido\n");
												return 1;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}