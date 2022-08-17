#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>



void init(void);
void display(void);


int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  //MEXEU AQUI, MEXA NO GLORTHO: FAÇA A ALTERAÇÃO DE 256 PARA 480
  glutInitWindowSize (480, 480); //Tamanho da tela, assim, os limites são 480 pra cima e pro lado
  glutInitWindowPosition (100, 100); 
  glutCreateWindow ("Desenhando um poligono regular");
  init();
  glutDisplayFunc(display); 
  
  glutMainLoop();
  return 0;
}

void init(void){
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glOrtho (0, 480, 0, 480, -1 ,1);
}

void display(void){
  int i;
  int lados = 0;
  int xVertexSupTrian, yVertexSupTrian; //É também o centro do hexágono regular. VALOR DEFINIDO MAIS ABAIXO

   float angulos;
   
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_LINES); //Inicializa linhas - uma linha a cada dois comandos de glVertex2i
  
      //Nosse linha base inicial:
      glVertex2i(220,240);  glVertex2i(260,240); //Ponto Inicial e dps o ponto final da nossa reta
        //COMO NOS DESENHOS DE ARQUITETURA (GD), a intercessão dos círculos pode ser feita na ponta de reta, com o compasso aberto com o mesmo comprimento da reta, nos dará esse vértice superior do triângulo
      /*MAS, usarei pítagoras para achar o vértice superior. Nosso segmetno de reta, tem comprimento = 260-220 = 40. Metade é = 20.
      O meio dele é em x= 240 e y = 240. Assim, já sabemos x (o meio) e somemos +*/
       int pitagoras = sqrt( pow (40,2) - pow(20,2) );
       xVertexSupTrian = 240; //MEIO
       yVertexSupTrian = 240 + pitagoras;
      
      //Lado esquerdo do triângulo:
      glVertex2i(xVertexSupTrian, (yVertexSupTrian)); //CALCULANDO
      glVertex2i(220,240); //ATÉ O VÉRTICE 1
      //Lado direito do triângulo
      glVertex2i(xVertexSupTrian, (yVertexSupTrian)); //CALCULANDO
      glVertex2i(260,240);

      //BISSETRIZ DO QUADRADO (45º): ela fica bem no meio dele, por ele ter todos os lados e ângulos iguais à 90°
      //meio = (240,240).

      int xfBissetriz = 240 ; int yfBissetriz = (240 + 20); //centro + METADE do tamanho do segmento de reta. Aqui, pegamos o ponto final "f" desse bissetriz.
      //É O CENTRO DO RETÂNGULO
      //glVertex2i(240,240); conferindo
      //glVertex2i(240,yfBissetriz); conferindo

      /*
      Agora começa a jogada: a MEDIATRIZ (o seg. de reta q tem a metade do tam.) gera o PONTO MÉDIO 
      entre O CENTRO "o4" do quadrado (aqui chamados de "xf e yf Bissetriz")
      e o centro do "o6" do hexágono (que é o mesmo que o "o3" do triângulo
      que chamamos aqui de VertexSupTrian) <-----.
      ESSE PONTO MÉDIO É O CENTRO DO PENTAGONO "o5"
      E TAMBÉM, DELE ATÉ O PONTO "o6/o3" ou "o4", NÓS TEMOS A DISTÂNCIA QUE SE REPETIRÁ PARA DESENHARMOS
      OS OUTROS POLÍGONOS.
      PASSE ESSA DISTÂNCIA SEMPRE PRA CIMA, DO PONTO DE CIMA PRA CIMA. ATÉ CHEGAR NO "oNÚMERO" que vc quer.
      Ex.: octógno = "o8"
      */
     int yPontoMedio = (yVertexSupTrian - yfBissetriz);

glEnd();
glFlush();
    glBegin(GL_LINES);
     
     //DESENHA QUADRADO
      //Esq
     glVertex2i(220,240);
     glVertex2i(220,280);
      //Dir.
     glVertex2i(260,240);
     glVertex2i(260,280);
     //Teto
    glVertex2i(220,280);  glVertex2i(260,280);
    
    //"o6" já temos. É o "o3", ou seja, seu centro "o" é o vértice do triângulo equilátero, que já temos

//A PARTIR DO "o7" QUE SOMAMOS COM O PONTO MÉDIO

  /* !!!   CÓDIGO REAL   !!!!!!!!
          int yo7 = yVertexSupTrian + yPontoMedio;
          int yon =0;
          
          //x sempre será = xfBissetriz;

          int contador = lados;
          for(lados > 6; contador < 7; lados--)
        {
          yon += yPontoMedio; //Incrementa o ponto medio
        }
  */

//Agora que complica: COMEÇAMOS A DESENHAR TUDO QUE TEM LADO > 4. iNTERSECÇÃO DOS CÍRCULOS

//Circulo no qual inscrevemos as figuras geoḿetricas primeiro:
//Ja temos o centro "on" pra todas as figuras: o3 (sup. triang), o4, o5, o6 (= o3), o7 etc...
//o5:
glBegin(GL_LINE_STRIP);
 
    for(int l =0; l < 361; l++) //SERIA 360 PARA GL_POLYGON, mas como só funciona line strip, E ELE NÃO FECHA, VC FORÇA MAIS UM
  {
    angulos = l*3.142/180;
    int o5= yVertexSupTrian - yPontoMedio;
    int tam_o5 = sqrt( pow ( (240-220)  ,2) - pow( (o5-240) ,2) );
    glVertex2f(o5+ tam_o5*cos(angulos)*40, o5+ tam_o5*sin(angulos)*40 ); //240 sempre será "x" nesses casos (o meio)
  }
  glEnd();
  glFlush();

  //SE FOSSE FAZER o7 NA MAO, FORA DO LOOP:

  glBegin(GL_LINE_STRIP);
 
    for(int m =0; m < 361; m++) //SERIA 360 PARA GL_POLYGON, mas como só funciona line strip, E ELE NÃO FECHA, VC FORÇA MAIS UM
  {
    angulos = m*3.142/180;
    int o7= yVertexSupTrian + yPontoMedio; //(o5 +2*ypontomedio)
    glVertex2f(240+ cos(angulos)*40, o7+ sin(angulos)*40 ); //240 sempre será "x" nesses casos (o meio)
  }
  glEnd();
  glFlush();



//Fazer círculo a partir da ponta inferior esq. a ponta superior esq.
//e outra da inf. dir. à sup. direita do quadrado.
//ONDE ELE INTERCEPTAR COM O circulo no qual inscrevemos as figuras geoḿetricas TRAÇADO A PARTIR DO CENTRO DA FIGURA, TEREMOS OS
//PONTOS DAS DIAGONAIS DAS FIGURAS.

glEnd();
glFlush();
//TEM QUE TERMINAR A INICIALIZACAO DE LINHAS
  glBegin(GL_LINE_STRIP);
 
    for(int j =0; j < 361; j++) //SERIA 360 PARA GL_POLYGON, mas como só funciona line strip, E ELE NÃO FECHA, VC FORÇA MAIS UM
  {
    angulos = j*3.142/180;
    glVertex2f(220+ cos(angulos)*40, 240+ sin(angulos)*40 );
  }
  glEnd();
  glFlush();

  glBegin(GL_LINE_STRIP);
    for(int k =0; k < 361; k++) //SERIA 360 PARA GL_POLYGON, mas como só funciona line strip, E ELE NÃO FECHA, VC FORÇA MAIS UM
  {
    angulos = k*3.142/180;
    
    glVertex2f(260+ cos(angulos)*40, 240+ sin(angulos)*40 );
  }





  glEnd();
  glFlush();
}
