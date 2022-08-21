#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

//ATENCAO
//FUNCAO PRA CONVERSAO DE INT EM TEXTO CHAR* (PRA PRINTAR NA TELA)
//COMO NÃO ACHOU A FUNCAO ITOA, TIVE QUE JOGAR ELA AQUI
char *  itoa ( int value, char * str )
{
    char temp;
    int i =0;
    while (value > 0) {
        int digito = value % 10;

        str[i] = digito + '0';
        value /= 10;
        i++;

    }
   i = 0;
   int j = strlen(str) - 1;

   while (i < j) {
      temp = str[i];
      str[i] = str[j];
      str[j] = temp;
      i++;
      j--;
   }
    return str;
}
//FIM DA ITOA (CONVERSAO)


//CRIADO POR: TIAGO CESAR
//Fazendo só a parte matemática da comparação com os dados que já consigo retirar do polígono.

double guardax [4];
double guarday [4];


double x_poligono [4];
double y_poligono [4];
double x2_poligono [4];
double y2_poligono [4];
double f_de_x_polig [4];


//Y é F(X) dessa reta que inventamos
        //Pra já comparar direto (seria bom ver uma forma de já só calcular a igualdade direto) tipo igualando as euqações do sitema msm - mesmo, ou  estilo: double xReta = x_poligono; sempre
double xReta [4];
double yReta [4];

double m_pol [4];
double b_pol [4];
//
double a,b,c,d,e,f;
double x,y;


void init(void);
void display(void);


int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (256, 256); 
  glutInitWindowPosition (100, 100); 
  glutCreateWindow ("Desenhando intercessao");
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

   
  //RETA (A,B) -3x+y = -11 //PARECE Q ASSIM, "VETOR [0] =" VC SO PODE FAZER SÓ PODE FAZER DENTRO DA FUNCAO MAIN
x_poligono [0] = 50; //dados que pegamos la do poligono
y_poligono [0] = 100; //dado pego la do poligono
glVertex2f(x_poligono [0] , y_poligono [0]  );

x2_poligono [0] = 50; //dados que pegamos lá do poligono
y2_poligono [0] = 150; //dado pego la do poligono
glVertex2f(x2_poligono [0] , y2_poligono [0]  );

//RETA (A,B) -3x+y = -11
x_poligono [1] = 50; //dados que pegamos la do poligono
y_poligono [1] = 150; //dado pego la do poligono
glVertex2f(x_poligono [1] , y_poligono [1]  ); //optei por escrever um pro um pra vizualizar melhor

x2_poligono [1] = 100; //dados que pegamos lá do poligono
y2_poligono [1] = 150; //dado pego la do poligono
glVertex2f(x2_poligono [1] , y2_poligono [1]  );

//RETA (A,B) -3x+y = -11
x_poligono [2] = 100; //dados que pegamos la do poligono
y_poligono [2] = 150; //dado pego la do poligono
glVertex2f(x_poligono [2] , y_poligono [2]  );

x2_poligono [2] = 100; //dados que pegamos lá do poligono
y2_poligono [2] = 100; //dado pego la do poligono
glVertex2f(x2_poligono [2] , y2_poligono [2]  );

//RETA (A,B) -3x+y = -11
x_poligono [3] = 50; //dados que pegamos la do poligono
y_poligono [3] = 100; //dado pego la do poligono
glVertex2f(x_poligono [3] , y_poligono [3]  );

x2_poligono [3] = 100; //dados que pegamos lá do poligono
y2_poligono [3] = 100; //dado pego la do poligono
glVertex2f(x2_poligono [3] , y2_poligono [3]  );
glEnd();
  glFlush();

  

//Desenhando reta
glBegin(GL_LINE_STRIP);
glVertex2f(70 , 80); glVertex2f(70 , 180);
glEnd();
  glFlush();

f_de_x_polig [0] = 0;
f_de_x_polig [1] = 0;
f_de_x_polig [2] = 0;
        

        for (int loc = 0; loc<4; loc++){

        
        //Do poligono, vamos calcular, transforamando os dados que já temos:
        m_pol [loc]= (y2_poligono[loc] - y_poligono[loc])/(x2_poligono[loc] - x_poligono[loc]); //coeficiente angular "m'" ou "a", (tangente), da reta.
        b_pol [loc] = y_poligono[loc] - (m_pol[loc]*x_poligono[loc]); //isola "b" pra achar


         //Na euqação, se tem o mesmo x e o mesmo y para que ela seja resolvida!
         //Mas aqui, preciso de declarar diferentes pro computador
         //Na matemática, só aparece uma vez, como iguais.
         
         yReta [loc] = xReta [loc]*2;
         f_de_x_polig [loc] = m_pol [loc]*xReta [loc] + b_pol [loc];
         // 0  = m_pol*xReta + b - f_de_x_polig
         // b_pol = m_pol*xReta - f_de_x_polig (->que é -1*y)
         // Iguale atribua a cada letra lá embaixo
        
        //0 = xReta*2 - 1*yReta.
            
        
        //minha ajuda: https://www.projetos.unijui.edu.br/matematica/principal/apostilas/cmaismais/frame07.htm
    

        
        
        //ax+by=c
        //dx+ey=f
        a= -m_pol [loc];
        
        
        b= 1; //quando passa f(y) para a direita, fica -1f(y)
        c= b_pol [loc];
        //RETA (A,B) -3x+y = -11
        d= 1; //DADO POR MIM - RETA QUE CRIEI
        e= 0; //DADO POR MIM - RETA QUE CRIEI
        f = 70; //DADO POR MIM - RETA QUE CRIEI

        y=(f*a-d*c)/(a*e-d*b);
        x=(c-b*y)/a ;

        double tst = -x;
        double tsty = -y;
        if (e == 0){
                if (isnan(x) || isnan(tst)){ x = f;}
        }
        guardax [loc]= x;
        guarday [loc]= y;
      }
     


        
  glRasterPos2f(0, 220); //define a posição na tela
        
        
        char vetor_de_char_ou_string[6]={0}; //vetor/array unidimensional de 0 à 5, 6 posições
        itoa (10, vetor_de_char_ou_string); //pega o parametro 1, e joga no param. 2, que é uma string/vetor char.
        //char *string = "10 %d texto";
        char *string = vetor_de_char_ou_string;
        double meu_x_de_intercessao= 10.3;
        
        // Não funcionaram as conversões: itoa(valor,string,10;  //sprintf(string, "%d", valor);  
        
        //Para nao fazer um teste do tipo Se x e y isnan()print.
        //eu decidi jogar as posicoes do vetor q eu sei q armazena as interecssoes, pois dao valores, e nao 'nan".
        sprintf(vetor_de_char_ou_string, "x2:%f y2:%f e x4:%f y4:%f ", guardax [1], guarday [1], guardax [3], guarday [3]); //Apesar de ser uma print, ELA É UMA CONVERSORA! USO SÓ PRA CONVERTER
        //ONDE SERA ARMAZENADO, "OQUE SERA CONVERTIDO %D ou %f", REFERENCIA DO %D ou %f)
      
      while(*string){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
      }


  glEnd();
  glFlush();
  
  
  
}
