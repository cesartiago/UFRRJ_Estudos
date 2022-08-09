/*
Custo: incremento, adição em floating point (x é um inteiro, mas y é floating point)
e chamada da função de arredondamento
“round(y)” para cada valor de x.
*/

#include<math.h>
#include <GL/glut.h>
#include <stdlib.h>

//Função para encontrar o valor absoluto (MÓDULO OU VALOR ABSOLUTO É DESCONSIDERAR O SINAL, PEGAR SÓ O VALOR)
int abs (int n)
{
    return ( (n>0) ? n : ( n * (-1)));
    //? é a condicional ternária: if X then Y else Z   	X ? Y : Z
}
//Função DDA para geração de linha
void DDA(int X0, int Y0, int X1, int Y1)
{
    //Calculae dx e dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;
 
    //Calcular as etapas (steps) necessárias para gerar pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    //? é a condicional ternária: if X then Y else Z   	X ? Y : Z
    /*
    Se |dx| > |dy| Retorne |dx|
    Do contrário retorne |dy|
    */
 
    //Calcular o incremento em x & y para cada etapa
    float Xinc = dx / (float) steps; //(CASTING/CONVERSÃO DE INT PRA FLOAT)
    float Yinc = dy / (float) steps;
    //steps = o maior entre  |dx| e |dy|
    //Como Xincremento e Yincremento = (seu valor atual) DIVIDIDO POR steps:
    //ASSIM pelo menos 1 deles sempre vai dar = 1. E o outro pode dar quebrado (0,algo)

    //Coloque pixel para cada etapa
    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++)
    {
        glVertex2i(X, Y);  // Coloque pixel em (X,Y)
        X += Xinc;           // incremento em x a cada passo
        Y += Yinc;           // incremento em y a cada passo
      //Repete-se
    }
}

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


  DDA(0,0, 250, 200);

  glEnd();
  glFlush();
  
 


}

