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

//
double a,b,c,d,e,f;
double x,y;

int main(){
        
        
        //Do poligono, vamos calcular, transforamando os dados que já temos:
        double m_pol = (y2_poligono - y_poligono)/(x2_poligono - x_poligono); //coeficiente angular "m'" ou "a", (tangente), da reta.
        double b_pol = y_poligono - (m_pol*x_poligono); //isola "b" pra achar


         //Na euqação, se tem o mesmo x e o mesmo y para que ela seja resolvida!
         //Mas aqui, preciso de declarar diferentes pro computador
         //Na matemática, só aparece uma vez, como iguais.
         
         yReta = xReta*2;
         f_de_x_polig = m_pol*xReta + b_pol;
         // 0  = m_pol*xReta + b - f_de_x_polig
         // b_pol = m_pol*xReta - f_de_x_polig (->que é -1*y)
         // Iguale atribua a cada letra lá embaixo
        
        //0 = xReta*2 - 1*yReta.
            
        
        //minha ajuda: https://www.projetos.unijui.edu.br/matematica/principal/apostilas/cmaismais/frame07.htm
    
        a= m_pol;
        b=-1; //quando passa f(y) para a direita, fica -1f(y)
        c= b_pol;
        d= 2; //DADO POR MIM - RETA QUE CRIEI
        e= -1; //DADO POR MIM - RETA QUE CRIEI
        f = 0; //DADO POR MIM - RETA QUE CRIEI

        y=(f*a-d*c)/(a*e-d*b);
        x=(c-b*y)/a ;

        printf(" aaaaaaaaaaaaaaaaa Y= %f e X = %f " , y, x);
   
    return 0;
}