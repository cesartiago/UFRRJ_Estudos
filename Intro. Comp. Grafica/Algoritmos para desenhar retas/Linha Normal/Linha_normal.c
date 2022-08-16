#include <GL/glut.h>
#include <stdlib.h>

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
  glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_LINES); //Inicializa linhas - uma linha a cada dois comandos de glVertex2i
  glVertex2i(40,200);  glVertex2i(200,10); //Ponto Inicial e dps o ponto final da nossa reta
  glVertex2i(20,5); glVertex2i(200,55);
  glEnd();
  glFlush();
}
