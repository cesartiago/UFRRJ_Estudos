#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
//  ========== autor/criado por: Tiago césar ==========
//  ========== evitar por letras maiusculas ==========

double divisorEq;



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
   //glOrtho (-130, 130, -130, 130, 0,130); //Quanto varia x0,x y0,y z0,z NA JANELA DE VISÃO. Com (0,0) sendo o centro no meio da tela
    
    
   gluLookAt( -140, 128, 128, 128, 128, 128, 0, 0, 1 );
   
        // ^ Os primeiros 3 valores são da posição do olho do observador (X,Y,Z)
        // ^ Os 3 segundos são do ponto de REFERÊNCIA EM QUE SE ESTÁ OLHANDO (PARA ONDE SE OLHA A PARTIR DA MINHA POSIÇÃO?) (X,Y,Z)
        // ^ Os 3 ultimos, falam da direção do vetor pra cima (QUE DIZ QUAL PONTO ESTA ACIMA DA CAMERA) (O PONTO 0,0,1). Eu quero Z acima de mim
   // ^Função boa e muuito útil!o 
   //?aQUI como ESCOLHEMOS O ÂNGULO DE VISÃO - ZERE UM DOS 3 PRIMEIROS Q FICA PLANO XY ETC "2D"?

    //FAZ FICAR RODANDO EM CÍRCULO ->: glRotated( angle, 0, 0, 1 );
    
    glBegin( GL_LINES );
    
        glColor3f(0.0f, 1.0f, 0.0f); //Cor (R,G,B) Verde
        glVertex3d( 0, 0, 0); glVertex3d( 0, 0, 680); //EIXO Z VERDE

        glColor3f(0.0f, 0.0f, 1.0f); //Cor (R,G,B) Azul
        glVertex3d( 0, 0, 0); glVertex3d( 0, 680, 0); //EIXO Y AZUL

        glColor3f(1.0f, 0.0f, 0.0f); //Cor (R,G,B) Vermelho
        glVertex3d( 0, 0, 0); glVertex3d( 680, 0, 0); //EIXO X VERMELHO

/*
        glColor3f(0.3f, 0.5f, 0.5f); //Cor (R,G,B) cIANO?
        glVertex3d( 0, 0, 0); glVertex3d( 680, 680, 680); //angulo em Z VERDE
*/
        //Linhas cianos pro chão
        glColor3f(0.1f, 0.1f, 0.1f); //Cor (R,G,B) cinza
        glVertex3d(128, 0, 0); glVertex3d( 128, 128, 0);
        //Estamos no cálculo 2: eixo y, no gluLookAt está sendo o deitado
        glVertex3d(100, 0, 0); glVertex3d( 100, 128, 0);
        glVertex3d(156, 0, 0); glVertex3d( 156, 128, 0);

        //Paredinha
        glVertex3d(128, 0, 0); glVertex3d( 128, 0, 50);
        //Estamos no cálculo 2: eixo y, no gluLookAt está sendo o deitado
        glVertex3d(100, 0, 0); glVertex3d( 100, 0, 50);
        glVertex3d(156, 0, 0); glVertex3d( 156, 0, 50);



   
    glEnd();

    


    

                    //--------------------Caso queira------------------//
                    glColor3f(0.0f, 1.0f, 0.0f); //Cor (R,G,B) Verde
                    double angulos;
  //TEM QUE TERMINAR A INICIALIZACAO DE LINHAS
  glBegin(GL_POINTS);
 
  double j2; //Contador
  double lados;
  lados = 7; //TEM QUE SER DOUBLE. Q AÍ NUḾ DE LADOS COMO 7 FECHARÃO. Se não, a divisão PROVAVELMENTE será forçada a ser int, só por causa do int em seu divisor...
  double angDiv = 360/lados; //Angulo do circulo dividido pelo nuemoro de lados do poligono

    for(j2 =0; j2 < 361; j2++) //SERIA 360 PARA GL_POLYGON, mas como só funciona line strip, E ELE NÃO FECHA, VC FORÇA MAIS UM
  {
    angulos = j2*3.14159265358979323846/180;
    glVertex3f(128+ 64*cos(angulos), 128+ 64*sin(angulos), 128 );
    glVertex3f(128,128+ 64*cos(angulos), 128+ 64*sin(angulos));
    glVertex3f(128+ 64*cos(angulos),128, 128+ 64*sin(angulos));
  }
  
  glEnd();
  //glFlush();

                    //-------------------- FIM DO POLIGONO------------------//




                    //-------------------- INICIO DO RAY TRACE ------------------//
    double a [256], b[256], c[256], d[256], x1[256], y1[256], faca_raiz [256], x2[256], y2[256], z1[256], z2[256];

    /*
    a[i]=1;
    b[i]=16;
    c[i]=0;
    d[i]=138;
    */
    //y=ax+b
    //z=cx+d

    for (int i = 0; i<256; i++){
        //Primeiro com z = 0 e a = 1; Depois, troco o z pra "j"
        a[i]=1;
        c[i]=0;
        d[i]=0;

        //o valor de y ser + ou - irá trasnaldar as retas em y
        b[i]=i;

        divisorEq = ((a[i]*a[i]) + (c[i]*c[i])+1);
            //condição para existir interseção
          if ( divisorEq != 0){
   
        //Nosso delta:
        faca_raiz [i] = 256*(a[i]*a[i])*d[i]  -(a[i]*a[i]) *(d[i]*d[i])   -28672*(a[i]*a[i]) +32768*a[i] +32768*a[i]*c[i]  +2*a[i]*b[i]*c[i]*d[i]  -256*a[i]*b[i]  -256*a[i]*b[i]*c[i]  -256*a[i]*c[i]*d[i] +256*b[i] +256*b[i]*(c[i]*c[i])  +32768*c[i]  +256*d[i] -(b[i]*b[i])- (b[i]*b[i])*(c[i]*c[i]) -28672*(c[i]*c[i])  -256*c[i]*d[i] -(d[i]*d[i])- 28672;
            
      

        //x(n)
        
            if (faca_raiz [i]  >= 0){
                //Se delta for negativo, não há interseção real

            
            x1[i]= (-a[i]*b[i] -c[i]*d[i] +128*a[i] +128*c[i] +128 +sqrt (faca_raiz [i]))/divisorEq;
            x2[i]= (-a[i]*b[i] -c[i]*d[i] +128*a[i] +128*c[i] +128 -sqrt (faca_raiz [i]))/divisorEq;

            y1[i]=a[i]*x1[i]+b[i];
            z1[i]=c[i]*x1[i]+d[i];

            y2[i]=a[i]*x2[i]+b[i];
            z2[i]=c[i]*x2[i]+d[i];
            

            //COMPARE E DESENHE O MENOR Z

            
            
            //y[i]=;
            if (z1[i] <= z2[i]){
                glBegin(GL_POINTS);
    
                glColor3f(1.0f, 0.5f, 0.0f); //Cor (R,G,B) Laranja
                glVertex3d( x1[i], y1[i], z1[i]);
                glVertex3d( x2[i], y2[i], z2[i]);
                glEnd();
                glFlush();

                }
            if (z1[i] > z2[i]){
                glBegin(GL_POINTS);

                glColor3f(0.0f, 0.0f, 1.0f); //Cor (R,G,B) Azul
                glVertex3d( x2[i], y2[i], z2[i]);
                glVertex3d( x1[i], y1[i], z1[i]);
                glEnd();
                glFlush();

            }
            }
            //else {printf("Nao ha interceccao - ");}
        }
        //else {printf("Nao ha interceccao - ");}
    
                //Ainda dentro do loop for (int i)
                for (int j = 0; j<256; j++){
                    //Trocamos agr o z pra "j"
                    //y=ax+b
                    //z=cx+d

                    d[i]=j;//PAREI AQUI
                    //O valor de "d", ou seja, z, irá subir e descer as retas

                    divisorEq = ((a[i]*a[i]) + (c[i]*c[i])+1);
                        //condição para existir interseção
                    if ( divisorEq != 0){
            
                    //Nosso delta:
                    faca_raiz [i] = 256*(a[i]*a[i])*d[i]  -(a[i]*a[i]) *(d[i]*d[i])   -28672*(a[i]*a[i]) +32768*a[i] +32768*a[i]*c[i]  +2*a[i]*b[i]*c[i]*d[i]  -256*a[i]*b[i]  -256*a[i]*b[i]*c[i]  -256*a[i]*c[i]*d[i] +256*b[i] +256*b[i]*(c[i]*c[i])  +32768*c[i]  +256*d[i] -(b[i]*b[i])- (b[i]*b[i])*(c[i]*c[i]) -28672*(c[i]*c[i])  -256*c[i]*d[i] -(d[i]*d[i])- 28672;
                        
                

                    //x(n)
                    
                        if (faca_raiz [i]  >= 0){
                            //Se delta for negativo, não há interseção real

                        
                            x1[i]= (-a[i]*b[i] -c[i]*d[i] +128*a[i] +128*c[i] +128 +sqrt (faca_raiz [i]))/divisorEq;
                            x2[i]= (-a[i]*b[i] -c[i]*d[i] +128*a[i] +128*c[i] +128 -sqrt (faca_raiz [i]))/divisorEq;

                            y1[i]=a[i]*x1[i]+b[i];
                            z1[i]=c[i]*x1[i]+d[i];

                            y2[i]=a[i]*x2[i]+b[i];
                            z2[i]=c[i]*x2[i]+d[i];
                            

                            //COMPARE E DESENHE O MENOR Z

                            
                            
                            //y[i]=;
                            if (z1[i] <= z2[i]){
                            glBegin(GL_POINTS);
                
                            glColor3f(1.0f, 0.5f, 0.0f); //Cor (R,G,B) Laranja
                            glVertex3d( x1[i], y1[i], z1[i]);
                            glVertex3d( x2[i], y2[i], z2[i]);
                            glEnd();
                            glFlush();
                            }
                            if (z1[i] > z2[i]){
                                glBegin(GL_POINTS);

                            glColor3f(0.0f, 0.0f, 1.0f); //Cor (R,G,B) Azul
                            glVertex3d( x2[i], y2[i], z2[i]);
                            glVertex3d( x1[i], y1[i], z1[i]);
                            glEnd();
                            glFlush();

                            }
                        }

                        //else {printf("Nao ha interceccao - ");}
                    }
                    //FIM DO IF DIVISOR

                    //else {printf("Nao ha interceccao - ");}
                    

                   
                } //FIM DO FOR (int j)

        }

        //fim do ray trace



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