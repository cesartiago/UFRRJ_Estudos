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
  int angulos;
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f (0.0, 0.0, 0.0);
 

  //TEM QUE TERMINAR A INICIALIZACAO DE LINHAS
  glBegin(GL_LINE_STRIP);
 
    for(int j =0; j < 361; j++) //SERIA 360 PARA GL_POLYGON, mas como só funciona line strip, E ELE NÃO FECHA, VC FORÇA MAIS UM
  {
    angulos = j*3.142/180;
    glVertex2f(128+ cos(angulos), 128+ sin(angulos) );
  }
  glEnd();
  glFlush();

}
