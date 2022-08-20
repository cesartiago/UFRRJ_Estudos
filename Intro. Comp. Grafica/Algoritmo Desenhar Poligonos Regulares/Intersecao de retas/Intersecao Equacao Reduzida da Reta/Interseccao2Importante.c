#include <stdio.h>
#include <math.h>
//CRIADO POR: TIAGO CESAR
//Fazendo só a parte matemática da comparação com os dados que já consigo retirar do polígono.

/*
float x1, x2, yi, y2;
float x3, x4, y3, y4;

t = 1.5; t2 = 1.5;
x1 = 0; yi = 0; x2 = 256; y2= 256;
x3 = 0; y3 = 0; x4 = 256; y4= 256;
*/


double x_poligono = 5; //dados que pegamos lá
double y_poligono = 4; //dado pego la

double x2_poligono = 6; //dados que pegamos lá
double y2_poligono = 7; //dado pego la
double f_de_x_polig = 0;
//Y é F(X) dessa reta que inventamos
        //Pra já comparar direto (seria bom ver uma forma de já só calcular a igualdade direto) tipo igualando as euqações do sitema msm - mesmo, ou  estilo: double xReta = x_poligono; sempre
double xReta;
double yReta;



int main(){
        
        
        //Do poligono, vamos calcular, transforamando os dados que já temos:
        double m_pol = (y2_poligono - y_poligono)/(x2_poligono - x_poligono); //coeficiente angular "m'" ou "a", (tangente), da reta.
        double b = y_poligono - (m_pol*x_poligono); //isola "b" pra achar

        

        
    printf("Ola mundo.");

      for (int p = -10; p < 10; p++) { //O segundo bloco do for, é a condição de execução. Eu posso chamar de "enquanto", mesmo não sendo while.
    //O segundo bloco do for não é sobre a condiição final. É um se/enquanto. Mas indiretamente, fala dela.

         xReta = p;
         
         yReta = xReta +1;
         f_de_x_polig = m_pol*xReta + b;

            
         if (f_de_x_polig == yReta)
         {
            printf("A interseção é em x= %f e y = %f " , xReta, yReta);
         }
        
         
    }
    
   
    return 0;
}