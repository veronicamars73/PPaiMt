#ifndef IMAGEM_H
#define IMAGEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//O struct Pixel é responsável por armazenar os valores referentes à cor de um pixel no padrão RGB
typedef struct pixel{
 int vermelho;
 int verde;
 int azul;
} Pixel;
//O struct Imagem é uma representação da imagem a ser editada pelo programa, ele armazena as dimensões da imagem
//e os valores referentes à cor dos pixels no padrão RGB
typedef struct imagem{
 Pixel **pintura;
 int largura;
 int altura;
} Imagem;


void image( Imagem *desenho);
void clear( Imagem *desenho);
void color(Pixel *coratual);
void pinta(int x, int y, Pixel cordopixel, Imagem *desenho);
void fazLinha(int xi, int yi, int xf, int yf, Pixel coratual, Imagem *desenho);
void line(Pixel coratual, Imagem *desenho);
void polygon(Pixel coratual, Imagem *desenho);
void fazPolygon(int n, int prox_ponto, int **coordenadas, Pixel coratual, Imagem *desenho);
void pintaCirculo(int xc, int yc, int x, int y, Pixel coratual, Imagem *desenho);
void fazCirculo(int xc, int yc, int raio, Pixel coratual, Imagem *desenho);
void circle(Pixel coratual, Imagem *desenho);
void fazRetangulo(int x, int y, int tamanhox, int tamanhoy, Pixel coratual, Imagem *desenho);
void rect(Pixel coratual, Imagem *desenho);
void fazFill(int x, int y, Pixel coratual, Pixel anterior, Imagem *desenho);
void fill(Pixel coratual, Imagem *desenho);
#endif