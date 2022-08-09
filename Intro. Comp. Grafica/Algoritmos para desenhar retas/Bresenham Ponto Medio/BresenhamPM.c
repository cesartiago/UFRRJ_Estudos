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
   int incrementoEdown = 2 * (y2 - y1); //incremento para mover pra E (pra Em Baixo)
   int incrementoNEup = incrementoEdown - (x2 - x1); //incremento para mover pra NE (CIMA = NÃO Em Baixo)
   for (int x = x1, y = y1; x <= x2; x++)
   {
      
      glVertex2i(x, y); //Desenha
 
      //Adicionar inclinação para aumentar o ângulo formado
      incrementoNEup += incrementoEdown;
 
      // O erro de inclinação atingiu o limite, tempo para
      // incrementar y e atualizar o erro de inclinação.
      if (incrementoNEup >= 0)
      {
         y++;
         incrementoNEup  -= 2 * (x2 - x1);
      }
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
