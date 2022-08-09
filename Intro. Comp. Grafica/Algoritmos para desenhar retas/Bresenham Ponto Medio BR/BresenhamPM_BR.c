/*
    Mais eficiente que DDA.
– incremental e cálculo baseado em inteiros
• Em cada iteração determinamos se a reta (real) intersecciona
o próximo pixel acima (“above”) ou abaixo (“below”) da
metade (“midpoint”) do valor de y.
– se acima então A: yi+1 = yi+1
– caso contrário B: yi+1 = yi

Ustiliza a forma implícita da equação de reta: 
axi + byi + c = 0 : (xi, yi) Na reta (o “midpoint”)
axi + byi + c < 0 : (xi, yi) Acima da reta (o ponto do meio)
axi + byi + c > 0 : (xi, yi) Abaixo da reta (o ponto médio) 
A cada iteração, verifica se o “midpoint” está acima ou abaixo da reta

Examina-se o valor de:
di=a(xi + 1) + b(yi + ½) + c
di é uma variável de decisão no passo i
*/

#include<math.h>
#include <GL/glut.h>
#include <stdlib.h>

// Programa C para a Geração de Linha de Bresenham
// Assumimos que :
// 1) A linha é desenhada da esquerda para a direita.
// 2) x1 < x2 e y1 < y2
// 3) A inclinação da linha está entre 0 e 1.
//    Desenhamos uma linha do canto inferior esquerdo ao superior
//    direito.
 
// Função para geração de linha
void bresenham(int x1, int y1, int x2, int y2)
{
  int dx = x2-x1;
  int dy = y2-y1;

//No ponto inicial, a variável de decisão é calculada assim:
  int d = 2* dy - dx; //Valor inicial de d.

  //d é a variável de decisão
  //SÓ DARÁ NEGATIVO SE:  dx > (2*dy)

  //O ponto médio é dito como "zero" e se vê a distância de "d" em relação à ele. "d" é >0 ou <0

  int incE = 2 * dy; // incremento para quando mover E (Embaixo - escolhe o pixel Embaixo do Ponto Médio)
  //d assumirá esse valor quando selecionar o pixel de baixo

  int incNE = 2*(dy-dx); // incremento para quando mover NE (Não Embaixo - escolhe o pixel à cima do Ponto Médio)
 //d assumirá esse valor quando selecionar o pixel de cima
 
  int x=x1, y=y1;

  glVertex2i(x, y); //Desenha o ponto inicial

   for (int x = x1, y = y1; x < x2; x++) //x++ pra andar pra direita
   {
      
      if (d<= 0){
        d+= incE; //Só continue no mesmo eixo X, desenhe á direita.
      }
      else { //d>0
        d+= incNE;
        y++; //E suba. Escolha o pixel de cima (a direita obviamente)
      }
      glVertex2i(x, y); //Desenha o ponto calculado

      
   }
}
 
//-=-=-=-=-=-=-

void init(void);
void display(void);


int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (256, 256); 
  glutInitWindowPosition (100, 100); 
  glutCreateWindow ("Desenhando uma linha");
  init();
  glutDisplayFunc(display); 

  
  glutMainLoop();
  return 0;
}

void init(void){
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glOrtho (0, 256, 0, 256, -1 ,1);
}

void display(void){
  int i;
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);


    int x1 = 20, y1 = 80, x2 = 250, y2 = 250;
    bresenham(x1, y1, x2, y2);

  glEnd();
  glFlush();
  
 


}
