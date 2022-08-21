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
double x_poligono [3];
double y_poligono [3];
double x2_poligono [3];
double y2_poligono [3];
double f_de_x_polig [3];


//Y é F(X) dessa reta que inventamos
        //Pra já comparar direto (seria bom ver uma forma de já só calcular a igualdade direto) tipo igualando as euqações do sitema msm - mesmo, ou  estilo: double xReta = x_poligono; sempre
double xReta [3];
double yReta [3];

double m_pol [3];
double b_pol [3];
//
double a,b,c,d,e,f;
double x,y;

int main(){
        //RETA (A,B) -3x+y = -11 //PARECE Q ASSIM, "VETOR [0] =" VC SO PODE FAZER SÓ PODE FAZER DENTRO DA FUNCAO MAIN
x_poligono [0] = 50; //dados que pegamos la do poligono
y_poligono [0] = 100; //dado pego la do poligono

x2_poligono [0] = 50; //dados que pegamos lá do poligono
y2_poligono [0] = 150; //dado pego la do poligono

//RETA (A,B) -3x+y = -11
x_poligono [1] = 50; //dados que pegamos la do poligono
y_poligono [1] = 150; //dado pego la do poligono

x2_poligono [1] = 85; //dados que pegamos lá do poligono
y2_poligono [1] = 100; //dado pego la do poligono

//RETA (A,B) -3x+y = -11
x_poligono [2] = 50; //dados que pegamos la do poligono
y_poligono [2] = 100; //dado pego la do poligono

x2_poligono [2] = 85; //dados que pegamos lá do poligono
y2_poligono [2] = 100; //dado pego la do poligono



f_de_x_polig [0] = 0;
f_de_x_polig [1] = 0;
f_de_x_polig [2] = 0;
        

        for (int loc = 0; loc<3; loc++){

        
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
        

        printf(" Intercessão %d em Y= %f e X = %f", loc , y, x);
        }
    return 0;
}