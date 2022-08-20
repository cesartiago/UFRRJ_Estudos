#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double atof ( const char *pN );

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

void init(void);
void display(void);
int valor = 90;
//void output(int, int, float, float, float, int, char*);

/*
void DesenhaTexto(void *font, char *string) 
{
	// Exibe caractere a caractere
	while(*string)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*string++); 
}
*/

/*
void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor de fundo definida
	glClear(GL_COLOR_BUFFER_BIT);





	// Posi��o no universo onde o texto bitmap ser� colocado 
	glColor3f(0,0,1);
	//glScalef(0.1, 0.1, 0.1); // diminui o tamanho do fonte
	//glRotatef(15, 0,0,1); // rotaciona o texto
    glRasterPos2f(250,250); 
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,"OpenGl"); //Desenhar texto
	// Exibe o desenha na janela
	glutSwapBuffers();
}
*/

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (256, 256); 
  glutInitWindowPosition (100, 100); 
  glutCreateWindow ("Desenhando uma linha");
  
  //glutDisplayFunc (Desenha);
  
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
  glFlush(); //PRECISA DE TERMINAR PARA DESENHAR O TEXTO

        glRasterPos2f(0, 120); //define position on the screen
        
        
        char vetor_de_char_ou_string[6]={0}; //vetor/array unidimensional de 0 à 5, 6 posições
        itoa (10, vetor_de_char_ou_string); //pega o parametro 1, e joga no param. 2, que é uma string/vetor char.
        //char *string = "10 %d texto";
        char *string = vetor_de_char_ou_string;
        double meu_x_de_intercessao= 10.3;
        
        // Não funcionaram as conversões: itoa(valor,string,10;  //sprintf(string, "%d", valor);  
        
        sprintf(vetor_de_char_ou_string, "%f", meu_x_de_intercessao); //Apesar de ser uma print, ELA É UMA CONVERSORA! USO SÓ PRA CONVERTER
        //ONDE SERA ARMAZENADO, "OQUE SERA CONVERTIDO %D ou %f", REFERENCIA DO %D ou %f)
      
      while(*string){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
      }

/*
  void output(int x, int y, float r, float g, float b, int font, char *string)
{
  glColor3f( r, g, b );
  glRasterPos2f(x, y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}
*/

  glEnd();
  glFlush();
}
