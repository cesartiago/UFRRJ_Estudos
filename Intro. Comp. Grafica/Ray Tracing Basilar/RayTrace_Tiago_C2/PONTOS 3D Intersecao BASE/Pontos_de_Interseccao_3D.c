#include <GL/glut.h>



double angle = 0.0;
void timer( int value )
{
    angle += 1.0;
    glutTimerFunc( 16, timer, 0 );
    glutPostRedisplay();
}

void display()
{
    glClearColor( 0, 0, 0, 0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    double w = glutGet( GLUT_WINDOW_WIDTH );
    double h = glutGet( GLUT_WINDOW_HEIGHT );
    gluPerspective( 60.0, w / h, 0.1, 1000.0 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
   glOrtho (-640, 640, -640, 640, 0,640); //Quanto varia x0,x y0,y z0,z NA JANELA DE VISÃO. Com (0,0) sendo o centro no meio da tela
    
    
   //gluLookAt( 100, 100, 100, 0, 0, 0, 0, 0, 1 ); //aQUI ESCOLHEMOS O ÂNGULO DE VISÃO - ZERE UM DOS 3 PRIMEIROS Q FICA PLANO XY ETC "2D"
        // ^ O VALOR PREENCHIDO COMO "100" FALA DO LIMITE DA TELA 
   // ^Função boa e muuito útil!

    //FAZ FICAR RODANDO EM CÍRCULO ->: glRotated( angle, 0, 0, 1 );

    
    glBegin( GL_LINES );
    
        glColor3f(1.0f, 0.0f, 0.0f); //Cor (R,G,B) Vermelho
        glVertex3d( 128/2, 128/2, 128); glVertex3d( 50, 50, 50);

        glVertex3d( 50, 50, 50); glVertex3d( 50, 100, 50);

        glColor3f(0.0f, 1.0f, 0.0f); //Cor (R,G,B) Verde
        glVertex3d( 0, 0, 0); glVertex3d( 0, 0, 100); //EIXO Z VERDE

        glColor3f(0.0f, 0.0f, 1.0f); //Cor (R,G,B) Azul
        glVertex3d( 0, 0, 0); glVertex3d( 0, 100, 0); //EIXO Y AZUL

        glColor3f(1.0f, 0.0f, 0.0f); //Cor (R,G,B) Vermelho
        glVertex3d( 0, 0, 0); glVertex3d( 100, 0, 0); //EIXO X VERMELHO

        glColor3f(0.0f, 1.0f, 0.0f); //Cor (R,G,B) Verde
        glVertex3d( 0, 0, 0); glVertex3d( 100, 100, 100); //angulo em Z VERDE
        
   
    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3d( 128/2, 128/2, 128); glVertex3d( 50, 50, 50);

        glVertex3d( 50, 50, 50); glVertex3d( 50, 100, 50);

      
        glVertex3d( 0, 0, 0); glVertex3d( 0, 0, 100); //EIXO Z VERDE

        
        glVertex3d( 0, 0, 0); glVertex3d( 0, 100, 0); //EIXO Y AZUL

       
        glVertex3d( 0, 0, 0); glVertex3d( 100, 0, 0); //EIXO X VERMELHO

        
        glVertex3d( 0, 0, 0); glVertex3d( 100, 100, 100); //angulo em Z VERDE
    glEnd();

                    //--------------------Caso queira------------------//
                    glColor3f(0.0f, 1.0f, 0.0f); //Cor (R,G,B) Verde
                    double angulos;
  //TEM QUE TERMINAR A INICIALIZACAO DE LINHAS
  glBegin(GL_POINTS);
 
  double j; //Contador
  double lados;
  lados = 7; //TEM QUE SER DOUBLE. Q AÍ NUḾ DE LADOS COMO 7 FECHARÃO. Se não, a divisão PROVAVELMENTE será forçada a ser int, só por causa do int em seu divisor...
  double angDiv = 360/lados; //Angulo do circulo dividido pelo nuemoro de lados do poligono

    for(j =0; j < 361; j++) //SERIA 360 PARA GL_POLYGON, mas como só funciona line strip, E ELE NÃO FECHA, VC FORÇA MAIS UM
  {
    angulos = j*3.14159265358979323846/180;
    glVertex2f(128+ 50*cos(angulos), 128+ 50*sin(angulos) );
  }
  
  glEnd();
  glFlush();

                    //-------------------- FIM DO POLIGONO------------------//


    glutSwapBuffers(); //ISSO TEM Q TÁ AQUI, NÃO TIRA
}

int main( int argc, char *argv[] )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( 640, 480 );
    glutCreateWindow( "Special key" );
    glutDisplayFunc( display );
    //Eu testei adicionar na mão: reshape
    glutTimerFunc( 0, timer, 0 );
    glutMainLoop();
}