Funções implementadas:
-image <inteiro> <inteiro>
	* Utilizada para criar uma imagem com as dimensões especificadas.
	* Recebe dois inteiros positivos como parâmetros, o primeiro representa a largura da imagem a ser criada e o segundo
	parâmetro representa a altura da mesma imagem, ambos em quantidade de pixels.

-clear <inteiro> <inteiro> <inteiro>
	* Utilizada para pintar toda a imagem com uma cor especificada no padrão RGB.
	* Recebe três inteiros maiores ou iguais a 0 e menores ou iguais a 255, os parâmetros representam a quantidade de
	vermelho, verde e azul que a cor informada tem, seguindo o padrão RGB.

-color <inteiro> <inteiro> <inteiro>
	* Utilizada para modificar a cor a ser utilizada por outras funções.
	* Recebe três inteiros maiores ou iguais a 0 e menores ou iguais a 255, os parâmetros representam a quantidade de
	vermelho, verde e azul que a cor informada tem, seguindo o padrão RGB.

-line <inteiro> <inteiro> <inteiro> <inteiro>
	* Utilizada para desenhar uma linha entre dois pontos escolhidos.
	* Recebe quatro inteiros como parâmetros, o primeiro inteiro é a coluna do ponto 1,o segundo inteiro é a linha do ponto 1,
	o terceiro inteiro é a coluna do ponto 2, o quarto inteiro é a linha do ponto 2. Note que o primeiro e o terceiro inteiros
	devem estar entre 0 e a quantidade de colunas, enquanto o segundo e o quarto deverão estar entre 0 e a quantidade de linhas.

-polygon <inteiro> ... <inteiro>
	* Utilizada para desenhar um polígono.
	* Recebe um inteiro que representa a quantidade de vértices do polígono e indica quantos inteiros serão informados após ele
	(a quantidade de inteiro informados após o primeiro será igual ao dobro do valor do primeiro inteiro), cada par de inteiros
	após o primeiro representará as coordenadas de um vértice do polígono. Esses inteiros sequirãoa mesma formatação que os
	inteiros da função line, onde cada par de inteiros representa as coordenadas de um ponto.

-rect <inteiro> <inteiro> <inteiro> <inteiro>
	* Utilizada para desenhar um retângulo.
	* Recebe um par de inteiros que representa as coordenadas do vértice superior esquerdo do retângulo, o terceiro inteiro
	representa a largura e o quarto inteiro representa a altura do retângulo.

-circle <inteiro> <inteiro> <inteiro>
	* Utilizada para desenhar um círculo.
	* Recebe um par de inteiros que representa as coordenadas do centro do círculo e o terceiro inteiro representa o raio do
	círculo.

-fill <inteiro> <inteiro>
	* Utilizada para preencher um espaço com uma cor, como um polígono ou um círculo.
	* Recebe um par de inteiros que representa as coordenadas de um ponto pertencente ao espaço a ser pintado.

-undo
	* Utilizada para desfazer a última ação feita pelo usuário.
	* Esta funcionalidade faz parte do extra.
	* Não necessita de nenhum parâmetro.

-open
	* Utilizada para abrir a imagem que está sendo editado pelo programa.
	* Esta funcionalidade faz parte do extra.
	* Não necessita de nenhum parâmetro.

-save
	* Utilizada para salvar as modificações feitas em uma imagem em um arquivo com extensão ppm.
	* Após a utilização desse comando será solicitado um nome para a imagem a ser criada e será necessário adcionar ".ppm"
	ao final do nome desejado.


 O extra solicitado foi a interatividade com o usuário, a possibilidade de desfazer a última modificação e de abrir a imagem durante
o processo de edição. Todos os requisitos extras foram atendidos.

 Para compilar o código é necessário apenas executar o arquivo makefile presente na pasta do projeto, o programa utiliza a biblioteca
eog, caso ele não esteja instalado o programa pode instalar automáticamente sendo necessário apenas conexão com a internet.

 Os autores do projeto são:
 Clauber Rogério de Oliveira Câmara
	Responsável por:
	Modularização;
	Documentação;
	Funcionalidades:
	Polígono;
	Retângulo;
	Color;
	Clear;

 Alaide Lisandra de Carvalho Melo
	Responsável por:
	Funcionalidades:
	Todas as funcionalidades do arquivo arquivo.c;
	Fill;
	Círculo;
	Linha;
