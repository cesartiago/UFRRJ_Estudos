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
  double dominioXi;
  double dominioXf;

  double a,b,c,d,e,f;
  double x,y;

  double f_de_x_polig = 0;
  double xReta;
  double yReta;

  //Linha 1


    for(j =0; j < 361; j+= angDiv) //SERIA 360 PARA GL_POLYGON, mas como só funciona line strip, E ELE NÃO FECHA, VC FORÇA MAIS UM
  {
    angulos = j*3.14159265358979323846/180;
    glVertex2f(128+ 50*cos(angulos), 128+ 50*sin(angulos) );

    ponto ++;
    x_poligono [(int)ponto] = 128+ 50*cos(angulos); //TEMOS O X E O Y (AQUI O X)
    y_poligono [(int)ponto] = 128+ 50*sin(angulos); //AQUI TEMOS O Y

    //Armazeno os pontos em 2 vetores, x e y.
  }

 
            
        yReta = xReta*2;
        //minha ajuda: https://www.projetos.unijui.edu.br/matematica/principal/apostilas/cmaismais/frame07.htm
    

  for (int k = 0; k<lados; k++){

     //Do poligono, vamos calcular, transforamando os dados que já temos:
        double m_pol = (y_poligono [k+1] - y_poligono [k])/(x_poligono [k+1] - x_poligono [k]); //coeficiente angular "m'" ou "a", (tangente), da reta.
        double b_pol = y_poligono [k] - (m_pol*x_poligono [k]); //isola "b" pra achar


         //Na euqação, se tem o mesmo x e o mesmo y para que ela seja resolvida!
         //Mas aqui, preciso de declarar diferentes pro computador
         //Na matemática, só aparece uma vez, como iguais.
         
         
         f_de_x_polig = m_pol*xReta + b_pol;
         // 0  = m_pol*xReta + b - f_de_x_polig
         // b_pol = m_pol*xReta - f_de_x_polig (->que é -1*y)
         // Iguale atribua a cada letra lá embaixo
         //0 = xReta*2 - 1*yReta.
    
    double vetorABx = x_poligono [k+1] - x_poligono [k]; //Descobrindo vetor AB de cada reta para a sua equacao parametrica
    double vetorABy = y_poligono [k+1] - y_poligono [k];

    
    dominioXi = x_poligono [k]; //inicio do dominio: inclui x
    dominioXf = x_poligono [k+1]; //x do dominio final. Final do dominio. Inclui xf

    a= m_pol;
        b=-1; //quando passa f(y) para a direita, fica -1f(y)
        c= b_pol;
        d= 2; //DADO POR MIM - RETA QUE CRIEI
        e= -1; //DADO POR MIM - RETA QUE CRIEI
        f = 0; //DADO POR MIM - RETA QUE CRIEI

        y=(f*a-d*c)/(a*e-d*b);
        x=(c-b*y)/a ;

        
  }

        



glEnd();
  glFlush();

  //DESENHANDO A RETA:
  glBegin(GL_LINES); //Inicializa linhas - uma linha a cada dois comandos de glVertex2i
  glVertex2i(40,200);  glVertex2i(200,10); //Ponto Inicial e dps o ponto final da nossa reta
  
glEnd();
  glFlush();


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

    
  
  
  

