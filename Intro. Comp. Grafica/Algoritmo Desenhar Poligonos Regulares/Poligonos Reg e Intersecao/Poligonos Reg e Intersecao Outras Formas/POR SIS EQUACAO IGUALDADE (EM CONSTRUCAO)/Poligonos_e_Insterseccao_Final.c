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
  lados = 3; //TEM QUE SER DOUBLE. Q AÍ NUḾ DE LADOS COMO 7 FECHARÃO. Se não, a divisão PROVAVELMENTE será forçada a ser int, só por causa do int em seu divisor...
  double angDiv = 360/lados; //Angulo do circulo dividido pelo nuemoro de lados do poligono
  double ponto = 0; //marca o numero de pontos (ou seja, de vezes que o loop gerou resultado na conta. PODIA USAR OUTRAS VÁRIAVEIS...)
  double x_poligono [(int)lados];
  double y_poligono [(int)lados];
  double dominioXi;
  double dominioXf;

  double a,b,c,d,e,f;
  double x,y;

  double f_de_x_polig = 0;
  double xReta;
  double yReta;

  double intercessao [3];
  int indice = 0;

  char vetor_de_char_ou_string[120]={0}; //vetor/array unidimensional de 0 à 11, 12 posições

  //Linha 1

//CIRCULO
double zangulos =0;
 for(int nao =0; nao < 361; nao++) //SERIA 360 PARA GL_POLYGON, mas como só funciona line strip, E ELE NÃO FECHA, VC FORÇA MAIS UM
  {
    zangulos = nao*3.14159265358979323846/180;
    glVertex2f(128+ 50*cos(zangulos), 128+ 50*sin(zangulos) );

  }
//FIM DO CIRCULO

    for(j =0; j < 361; j+= angDiv) //SERIA 360 PARA GL_POLYGON, mas como só funciona line strip, E ELE NÃO FECHA, VC FORÇA MAIS UM
  {
    angulos = j*3.14159265358979323846/180;
    glVertex2f(128+ 50*cos(angulos), 128+ 50*sin(angulos) );

    
    x_poligono [(int)ponto] = 128+ 50*cos(angulos); //TEMOS O X E O Y (AQUI O X)
    y_poligono [(int)ponto] = 128+ 50*sin(angulos); //AQUI TEMOS O Y
    ponto++;
    //Armazeno os pontos em 2 vetores, x e y.
  }

    
        //yReta = xReta*2;
        //minha ajuda: https://www.projetos.unijui.edu.br/matematica/principal/apostilas/cmaismais/frame07.htm
        yReta = 158;

        double m_pol; //coeficiente angular "m'" ou "a", (tangente), da reta do poligono
        double b_pol; //coeficiente linear b da reta do poligono
  
  int k = 0;
  for (k = 0; k<lados; k++){

     //Do poligono, vamos calcular, formar cada uma das retas e comparar em seu dominio
     //transforamando os dados que já temos:
     if((y_poligono [k+1] - y_poligono [k]) == 0){
      m_pol = 0;
     }

     if((x_poligono [k+1] - x_poligono [k]) == 0){
        m_pol = 0;
     }

     else {

     
        m_pol = (y_poligono [k+1] - y_poligono [k])/(x_poligono [k+1] - x_poligono [k]); //coeficiente angular "m'" ou "a", (tangente), da reta.
    }

        b_pol = y_poligono [k] - (m_pol*x_poligono [k]); //isola "b" pra achar
    

         //Na equação, se tem o mesmo x e o mesmo y para que ela seja resolvida!
         //Mas aqui, preciso de declarar diferentes pro computador
         //Na matemática, só aparece uma vez, como iguais.
         
         
         f_de_x_polig = m_pol*xReta + b_pol;
         // 0  = m_pol*xReta + b - f_de_x_polig
         // b_pol = m_pol*xReta - f_de_x_polig (->que é -1*y)
         // Iguale atribua a cada letra lá embaixo
         //0 = xReta*2 - 1*yReta.
    
    /* Não usei:
    double vetorABx = x_poligono [k+1] - x_poligono [k]; //Descobrindo vetor AB de cada reta para a sua equacao parametrica
    double vetorABy = y_poligono [k+1] - y_poligono [k];
    */

    
    dominioXi = x_poligono [k]; //inicio do dominio: inclui x
    dominioXf = x_poligono [k+1]; //x do dominio final. Final do dominio. Inclui xf

    //https://www.projetos.unijui.edu.br/matematica/principal/apostilas/cmaismais/frame07.htm
    /*ESSA É A ORGANIZAÇÃO*/
    //ax+by=c RETAS DO POLIGONO ENTRARAO AQUI
    //dx+ey=f //nossa reta unica, que o traça
    a= m_pol;
        b=-1; //quando passa f(y) para a direita, fica -1f(y)
        c= b_pol;
        d= 0; //DADO POR MIM - RETA QUE CRIEI
        e= 1; //DADO POR MIM - RETA QUE CRIEI
        f = 158; //DADO POR MIM - RETA QUE CRIEI

        y=(f*a-d*c)/(a*e-d*b);
        x=(c-b*y)/a ;
        //x=10.200256563; //teste - ok

        
          //PARECE QUE ELE COMEÇA DO PONTO MAIS A ESQ. DO TRIÂNGULO, para a direita!
         //if (x >= dominioXi && x<= dominioXf){

          
          
          if (x>= 0){
          intercessao [indice] = x; 
          indice ++;
          }
          else {
          intercessao [indice] = -(x); //converter pra mais 
          indice ++;
          }
          
          
          
         //}
          
        
        

        
        
        
        
        


        
        
  }

  glEnd();
  glFlush();

  //DESENHANDO A RETA:
  glBegin(GL_LINES); //Inicializa linhas - uma linha a cada dois comandos de glVertex2i
  //glVertex2i(40,200);  glVertex2i(200,10); //Ponto Inicial e dps o ponto final da nossa reta

  glVertex2i(0,158);  glVertex2i(200,158); //Ponto Inicial e dps o ponto final da nossa reta
  glVertex2i(103,0);  glVertex2i(103,158); //RETA MOSTRANDO PRIMEIRA INTERSECAO x = 103
  glVertex2i(128,0);  glVertex2i(128,158); //RETA MOSTRANDO Segunda INTERSECAO x = 126
  

  glVertex2i(178,0);  glVertex2i(178,158); //instersecao 3, fora do dom

glEnd();
  glFlush();

  //double hj [2] = {6, 8}; teste de sprintf
  
  sprintf(vetor_de_char_ou_string, "%.3f e %.3f e %.3f x=%f  XP=%.3f XP=%.3f XP=%.3f XP03=%.3f", intercessao [0], intercessao [1], intercessao [2], x, x_poligono [0], x_poligono [1], x_poligono [2],x_poligono [3] ); //Apesar de ser uma print, ELA É UMA CONVERSORA! USO SÓ PRA CONVERTER
        //ONDE SERA ARMAZENADO, "OQUE SERA CONVERTIDO %D ou %f", REFERENCIA DO %D ou %f)
        char *string = vetor_de_char_ou_string;

  //string = "3"; //teste, indicou que ate aqui funciona

  
  glRasterPos2f(0, 200); //define a posição na tela

  while(*string){
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
      }

      glEnd();
  glFlush(); //---> SE VC NAO FINALIZAR NO FIM DE TUDO, ELE NAO DESENHA.
  //SE NAO FINALIZAR NO COMECO DESSE, TB NAO.

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

    
  
  
  

