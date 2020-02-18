#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "funcoesdeimagem.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void criaArquivo(char nomedoarquivo[], Imagem *desenho, int maximo, FILE *arquivo);
void save( Imagem *desenho, Pixel maximo, FILE *arquivo);
void criaPreArquivo(Imagem *desenho);
void criaPrimeiroArquivo(Imagem *desenho);
void atualizaBackup();
void abreGaleria(char nomedoarquivo[]);
void open(Imagem *desenho, int maximo);
int* lerIntArquivo( int inicio, int vezes, int val[]);
void rotinaBackups(Imagem *desenho);
void apagaBackups();
void desfaz(Imagem *desenho);
int defineComando(char *comando, Imagem *desenho, Pixel *coratual, Pixel maximo, FILE *arquivo);

#endif