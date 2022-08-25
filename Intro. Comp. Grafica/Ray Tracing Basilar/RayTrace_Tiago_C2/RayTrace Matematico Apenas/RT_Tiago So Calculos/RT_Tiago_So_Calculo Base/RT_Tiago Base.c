#include <stdio.h>
#include <math.h>
//  ========== autor/criado por: Tiago césar ==========
//  ========== evitar por letras maiusculas ==========

float* number = 5;
double divisorEq;


int main(){
    
    double a [100], b[100], c[100], d[100], x1[100], y1[100], faca_raiz [100], x2[100], y2[100], z1[100], z2[100];
    double dfaca_raiz;
    a[0]=1;
    b[0]=16;
    c[0]=0;
    d[0]=138;
    //y=ax+b
    //z=cx+d

    divisorEq = ((a[0]*a[0]) + (c[0]*c[0])+1);
    //condição para existir interseção
     if ( divisorEq != 0){

     
     

//dentro de um loop
    //Nosso delta:
    faca_raiz [0] = 256*(a[0]*a[0])*d[0]  -(a[0]*a[0]) *(d[0]*d[0])   -28672*(a[0]*a[0]) +32768*a[0] +32768*a[0]*c[0]  +2*a[0]*b[0]*c[0]*d[0]  -256*a[0]*b[0]  -256*a[0]*b[0]*c[0]  -256*a[0]*c[0]*d[0] +256*b[0] +256*b[0]*(c[0]*c[0])  +32768*c[0]  +256*d[0] -(b[0]*b[0])- (b[0]*b[0])*(c[0]*c[0]) -28672*(c[0]*c[0])  -256*c[0]*d[0] -(d[0]*d[0])- 28672;
        
    dfaca_raiz = faca_raiz [0];
    //^converter para ser aceito como parâmetro de sqrt()

     //x(n)
    
        if (faca_raiz [0]  >= 0){
            //Se delta for negativo, não há interseção real

        
        x1[0]= (-a[0]*b[0] -c[0]*d[0] +128*a[0] +128*c[0] +128 +sqrt (faca_raiz [0]))/divisorEq;
        x2[0]= (-a[0]*b[0] -c[0]*d[0] +128*a[0] +128*c[0] +128 -sqrt (faca_raiz [0]))/divisorEq;

        y1[0]=a[0]*x1[0]+b[0];
        z1[0]=c[0]*x1[0]+d[0];

        y2[0]=a[0]*x2[0]+b[0];
        z2[0]=c[0]*x2[0]+d[0];
        

        //COMPARE E DESENHE O MENOR Z

        
        
        //y[0]=;

        printf("Delta=%f e x1=%f x2=%f  \n", faca_raiz [0],  x1[0], x2[0]);
        printf("-----------\n");
        printf("y1=%f y2=%f  \n", y1[0], y2[0]);
        printf("-----------  \n");
        printf("z1=%f z2=%f  \n", z1[0], z2[0]);
        printf("FIM");
        }
        else {printf("Não há intercessão");}
    }
     else {printf("Não há intercessão");}
   
    return 0;
}