  /**
  Problemas:
• Linhas verticais. (m = INFINITO)
• Lento, pois para todo x tem-se:
uma multiplicação em “floating point”
uma adição em “floating point”
uma chamada de função de arrendondamento (“round”)
 */

#include<math.h>
#include <GL/glut.h>
#include <stdlib.h>

//Função Eq_Reta para geração de linha
void Eq_Reta (int Xi, int Xf, int m1, int b1)
//Passar X_inicial, X_final, m(inclinação), e b;
//Que formam: ax+b = y

{

  int m = m1;
  int b = b1;

  for(int x = Xi; x <= Xf; x++)
  {
    int y = (int)round(m*x + b);
    /*
    A função ROUND arredonda números para o inteiro ou decimal mais próximo.
    Se ele for 2.5, vai para 3, e não para 2.
    */
    glVertex2i(x, y);  // Coloque pixel em (X,Y)
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


  Eq_Reta (0,500, 1, 0); //Vc deverá passar X_inicial, X_final, m(inclinação), e b;
  //Que formam: ax+b = y

  glEnd();
  glFlush();
  
 


}




/*
Se for usar, põem lá em cima nas primeiras linhas
//Função para encontrar o valor absoluto (MÓDULO OU VALOR ABSOLUTO É DESCONSIDERAR O SINAL, PEGAR SÓ O VALOR)
int abs (int n)
{
    return ( (n>0) ? n : ( n * (-1)));
    //? é a condicional ternária: if X then Y else Z   	X ? Y : Z
}
*/
