#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

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
  double angulos;
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f (0.0, 0.0, 0.0);
 

  //TEM QUE TERMINAR A INICIALIZACAO DE LINHAS
  glBegin(GL_LINE_STRIP);
 
  double j; //Contador
  double lados;
  lados = 7; //TEM QUE SER DOUBLE. Q AÍ NUḾ DE LADOS COMO 7 FECHARÃO. Se não, a divisão PROVAVELMENTE será forçada a ser int, só por causa do int em seu divisor...
  double angDiv = 360/lados; //Angulo do circulo dividido pelo nuemoro de lados do poligono
  double ponto = 0; //marca o numero de pontos (ou seja, de vezes que o loop gerou resultado na conta. PODIA USAR OUTRAS VÁRIAVEIS...)
  double x_poligono [(int)lados];
  double y_poligono [(int)lados];

  double t;
  //Linha 1: com pontos x1,yi e x2,y2
    
    double xLinha = (1-t)*0 + t*256;
    double yLinha = (1-t)*0 + t*256;

    for(j =0; j < 361; j+= angDiv) //SERIA 360 PARA GL_POLYGON, mas como só funciona line strip, E ELE NÃO FECHA, VC FORÇA MAIS UM
  {
    angulos = j*3.14159265358979323846/180;
    glVertex2f(128+ 50*cos(angulos), 128+ 50*sin(angulos) );

    ponto ++;
    x_poligono [(int)ponto] = 128+ 50*cos(angulos); //TEMOS O X E O Y (AQUI O X)
    y_poligono [(int)ponto] = 128+ 50*sin(angulos); //AQUI TEMOS O Y

    //Armazeno os pontos em 2 vetores, x e y.
  }



}

  /*
  for (int k = 0; k<lados; k++){

    
    double vetorABx = x_poligono [k+1] - x_poligono [k]; //Descobrindo vetor AB de cada reta para a sua equacao parametrica
    double vetorABy = y_poligono [k+1] - y_poligono [k];

      //Compare em função de t
    double retaxPoligono = x_poligono + vetorABx*t ; //Fazer com o ponto inicial a direita na equacao.
    double retayPoligono = y_poligono + vetorABy*t;
    
        
      if (retaxPoligono == xLinha && retayPoligono == yLinha){
          
      }
    

    }
    */

    
  
  
  glEnd();
  glFlush();

}
