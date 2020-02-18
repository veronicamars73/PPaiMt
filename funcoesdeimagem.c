#include "funcoesdearquivo.h"
#include <stdlib.h>
#include <stdio.h>

void image(Imagem *desenho){
	//Essa função é responsável por criar uma imagem com as dimensões (altura e largura) fornecidas pelo usuário
	int i, j, k;
	scanf("%d %d", &i, &j);
	desenho->altura = j;
	desenho->largura = i;
	desenho->pintura = calloc(j, sizeof(Pixel*));
	for (k = 0; k < j; ++k){
		desenho->pintura[k] = calloc(i, sizeof(Pixel));
	}
}

void clear(Imagem *desenho){
	//Essa função é responsável por modificar a cor de todos os pixels do desenho por uma fornecida pelo usuário
	int val[3], i, j;
	scanf("%d %d %d", &val[0], &val[1], &val[2]);
	for (i = 0; i < desenho->altura; ++i){
		for (j = 0; j < desenho->largura; ++j){
			desenho->pintura[i][j].vermelho = val[0];
			desenho->pintura[i][j].verde = val[1];
			desenho->pintura[i][j].azul = val[2];
		}
	}
}

void color( Pixel *coratual){
	//Essa função muda o valor da variável coratual para um valor fornecido pelo usuário
	int val[3], i;
	scanf("%d %d %d", &val[0], &val[1], &val[2]);
	coratual->vermelho=val[0];
	coratual->verde=val[1];
	coratual->azul=val[2];
}

void pinta(int x, int y, Pixel cordopixel, Imagem *desenho){
	//Essa função recebe as coordenadas de um ponto no desenho e uma cor
	//em seguida pinta o pixel ao qual as coordendas se referem com a cor fornecida
	desenho->pintura[y][x].vermelho = cordopixel.vermelho;
	desenho->pintura[y][x].verde = cordopixel.verde;
	desenho->pintura[y][x].azul = cordopixel.azul;
}

int abs(int a){
	//Essa função retorna o valor absoluto de um número inteiro
	if (a>0){
		return a;
	}else{
		return -a;
	}
}

void fazLinha(int xi, int yi, int xf, int yf, Pixel coratual, Imagem *desenho){
	//Essa função é responsável por indicar todos os pontos pertencentes à linha entre os pontos (xi, yi) e (xf,yf)
	//Essa função utiliza o algoritmo de Jack Bresenham apresentada no video de Brian Will presente no link: 
	//<https://www.youtube.com/watch?v=IDFB5CDpLDE&feature=youtu.be>
	int varx, vary, x, y, dx, dy,i;
	double movimento;
	x=xi;
	y=yi;
	if(xi<xf){
		varx=xf-xi;
		dx=1;
	}else{
		varx=xi-xf;
		dx=-1;
	}
	if(yi<yf){
		vary=yf-yi;
		dy=1;
	}else{
		vary=yi-yf;
		dy=-1;
	}
	if (x==xf){//Essa condição testa se a linha é horizontal
		if (dy==1){
			//As próximas três linhas desenham uma linha horizontal
			for (i = y; i <= yf; ++i){
				pinta(x,i,coratual,desenho);
			}
		}else{
			//As próximas três linhas desenham uma linha horizontal
			for (i = yf; i <= y; ++i){
				pinta(x,i,coratual,desenho);
			}
		}
	}else{
		if (y==yf){//Essa condição testa se a linha é vertical
			if (dx==1){
				//As próximas três linhas desenham uma linha vertical
				for (i = x; i <= xf; ++i){
					pinta(i,y,coratual,desenho);
				}
			}else{
				//As próximas três linhas desenham uma linha vertical
				for (i = xf; i <= x; ++i){
					pinta(i,y,coratual,desenho);
				}
			}
		}else{
			//As próximas linhas desenham linhas diagonais seguindo o algoritomo de Jack Bresenham
			if (varx>vary){
				movimento = dx / 2.00;
				do{
					pinta(x,y, coratual, desenho);
					movimento = movimento-vary;
					if(movimento<0){
						y = y+dy;
						movimento = movimento + varx;
					}
					x=x+dx;
				}while (x!=xf);
				pinta(x,y, coratual, desenho);
			}else{
				movimento = dy / 2.00;
				do{
					pinta(x,y, coratual, desenho);
					movimento = movimento-varx;
					if(movimento<0){
						x = x + dx;
						movimento = movimento + vary;
					}
					y=y+dy;
				}while (y!=yf);
				pinta(x,y, coratual, desenho);
			}
		}
	}
}

void line(Pixel coratual, Imagem *desenho){
	//Essa função é utilizada para ler as coordenadas do ponto inicial e do final da linha e
	//passar essas informações para a função fazLinha
	int val[4];
	scanf("%d %d %d %d", &val[0], &val[1], &val[2], &val[3]);
	fazLinha(val[0],val[1],val[2],val[3], coratual, desenho);
}

void polygon(Pixel coratual, Imagem *desenho){
	//Essa função é utilizada para ler as coordenadas dos pontos que correspondem aos vértices do polígono e
	//passar essas informações para a função fazPolygon
	//A variável pontos armazena a quantidade de pontos do poligono e a variável coordenadas armazena as coordenadas
	//dos pontos a serem ligados
	int pontos, i, **coordenadas;
	scanf("%d", &pontos);
	coordenadas = (int **)calloc(2, sizeof(int *));
	for ( i = 0; i < 2; ++i){
		coordenadas[i] = (int *)calloc(pontos, sizeof(int));
	}
	for (i = 0; i < pontos; ++i){
		scanf("%d",&coordenadas[0][i]);
		scanf("%d",&coordenadas[1][i]);
	}
	fazPolygon(pontos, 0, coordenadas, coratual, desenho);
	for ( i = 0; i < 2; ++i){
		free(coordenadas[i]);
	}
	free(coordenadas);
}

void fazPolygon(int n, int prox_ponto, int **coordenadas, Pixel coratual, Imagem *desenho){
	//Essa função é responsável por ligar todos os pontos do polígono
	if(prox_ponto==0){
		//A próxima linha desenha a linha entre o primeiro e o último ponto
		fazLinha(coordenadas[0][0], coordenadas[1][0], coordenadas[0][n-1], coordenadas[1][n-1], coratual, desenho);
		//Na próxima linha a função chama a si mesma para desenhar a próxima linha
		fazPolygon(n, prox_ponto+1, coordenadas, coratual, desenho);
		return;
	}else if(n>prox_ponto){
		//A próxima linha desenha a linha entre o ponto prox_ponto e seu antecessor
		fazLinha(coordenadas[0][prox_ponto-1], coordenadas[1][prox_ponto-1], coordenadas[0][prox_ponto], coordenadas[1][prox_ponto], coratual, desenho);
		//Na próxima linha a função chama a si mesma para desenhar a próxima linha
		fazPolygon(n, prox_ponto+1, coordenadas, coratual, desenho);
		return;
	}
	return;
}

void pintaCirculo(int xc, int yc, int x, int y, Pixel coratual, Imagem *desenho){
	//As próximas 8 linhas pintam 8 pontos usando a simetria entre os octantes de Jack Bresenham
	pinta(xc+x, yc+y, coratual, desenho);
	pinta(xc-x, yc+y, coratual, desenho);
	pinta(xc+x, yc-y, coratual, desenho);
	pinta(xc-x, yc-y, coratual, desenho);
	pinta(xc+y, yc+x, coratual, desenho);
	pinta(xc-y, yc+x, coratual, desenho);
	pinta(xc+y, yc-x, coratual, desenho);
	pinta(xc-y, yc-x, coratual, desenho);
}

void fazCirculo(int xc, int yc, int raio, Pixel coratual, Imagem *desenho){
	//Essa função utiliza o algoritmo de Jack Bresenham
	//Essa função calcula todos os pontos pertencentes ao círculo em um octante
	//(xc,yc) correspondêm à coordenada do centro do círculo
	//As fórmulas presentes nessa função foram retiradas do artigo do opengenus iq presente no link:<https://iq.opengenus.org/bresenhams-circle-drawing-algorithm/>
	int x, y;
	double ponto = 3-(2*raio);
	y=raio;
	x=0;
	//O laço de repetição abaixo parará quando alcaçar o fim de um octante
	while(x<=y){
		pintaCirculo(xc, yc, x, y, coratual, desenho);
		x+=1;
		if (ponto<0){
			ponto = ponto + (4*x) + 6;
		}else{
			ponto = ponto + 4*(x - y) + 10;
			y = y-1;
		}
	}
}

void circle(Pixel coratual, Imagem *desenho){
	//Essa função é utilizada para ler as coordenadas do centro do círculo e o raio do mesmo e passar
	//essas informações para a função fazCirculo
	int val[3], i;
	scanf("%d %d %d", &val[0], &val[1], &val[2]);
	fazCirculo(val[0], val[1], val[2], coratual, desenho);
}

void fazRetangulo(int x, int y, int tamanhox, int tamanhoy, Pixel coratual, Imagem *desenho){
	//as próximas quatro linhas desenham as quatro linhas do retângulo
	fazLinha(x, y, x+tamanhox, y, coratual, desenho);
	fazLinha(x, y, x, y+tamanhoy, coratual, desenho);
	fazLinha(x+tamanhox, y, x+tamanhox, y+tamanhoy, coratual, desenho);
	fazLinha(x, y+tamanhoy, x+tamanhox, y+tamanhoy, coratual, desenho);
}

void rect( Pixel coratual, Imagem *desenho){
	// Essa função é utilizada para ler as coordenadas do ponto superior esquerdo do retângulo,
	//a largura e a altura do retângulo e passar essas informações para a função fazRetangulo
	int val[4], i;
	scanf("%d %d %d %d", &val[0], &val[1], &val[2], &val[3]);
	fazRetangulo(val[0], val[1], val[2], val[3] ,coratual, desenho);
}

void fazFill(int x, int y, Pixel coratual, Pixel anterior, Imagem *desenho){
	//Essa função funciona de forma recursiva preenchendo um espaço da imagem 
	//A linha abaixo testa se o ponto (x,y) é uma borda da figura
	if (x < 0 || x >= desenho->altura || y < 0 || y >= desenho->largura){
		return;
	}
	//A linha abaixo testa se o ponto (x,y) é a borda de uma forma
	if (desenho->pintura[x][y].vermelho != anterior.vermelho || desenho->pintura[x][y].verde != anterior.verde || desenho->pintura[x][y].azul != anterior.azul){
		return;
	}
	desenho->pintura[x][y].vermelho = coratual.vermelho;
	desenho->pintura[x][y].verde = coratual.verde;
	desenho->pintura[x][y].azul = coratual.azul;

	//As próximas quatro linhas chamam essa função, de maneira recursiva, utilizando os pontos acima e 
	//dos lados do ponto (x,y)
	fazFill(x+1, y, coratual, anterior, desenho);
	fazFill(x-1, y, coratual, anterior, desenho);
	fazFill(x, y+1, coratual, anterior, desenho);
	fazFill(x, y-1, coratual, anterior, desenho);
}

void fill(Pixel coratual, Imagem *desenho){
	//Essa função identifica o primeiro ponto a ser pintado e a cor nesse ponto e passa essas informações para a 
	//função fazFill
	int val[2], i;
	//A linha abaixo lê o primeiro ponto a ser pintado
	scanf("%d %d", &val[0], &val[1]);
	fazFill(val[0], val[1], coratual, desenho->pintura[val[0]][val[1]], desenho);
}
 