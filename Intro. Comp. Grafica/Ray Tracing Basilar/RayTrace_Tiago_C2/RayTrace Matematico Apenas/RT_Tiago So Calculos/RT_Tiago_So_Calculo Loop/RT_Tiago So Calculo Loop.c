#include <stdio.h>
#include <math.h>
//  ========== autor/criado por: Tiago césar ==========
//  ========== evitar por letras maiusculas ==========


double divisorEq;


int main(){
    
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
                printf("Delta=%f e x1=%f \n", faca_raiz [i],  x1[i]);
                printf("-----------\n");
                printf("y1=%f \n", y1[i]);
                printf("-----------  \n");
                printf("z1=%f \n", z1[i]);
                printf("FIM");
                }
                if (z1[i] > z2[i]){
                    printf("Delta=%f e x2=%f \n", faca_raiz [i],  x2[i]);
                    printf("-----------\n");
                    printf("y2=%f \n", y2[i]);
                    printf("-----------  \n");
                    printf("z2=%f \n", z2[i]);
                    printf("FIM");
                }
            }
            else {printf("Nao ha interceccao - ");}
        }
        else {printf("Nao ha interceccao - ");}
    
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
                            printf("Delta=%f e x1=%f \n", faca_raiz [i],  x1[i]);
                            printf("-----------\n");
                            printf("y1=%f \n", y1[i]);
                            printf("-----------  \n");
                            printf("z1=%f \n", z1[i]);
                            printf("FIM");
                            }
                            if (z1[i] > z2[i]){
                                printf("Delta=%f e x2=%f \n", faca_raiz [i],  x2[i]);
                                printf("-----------\n");
                                printf("y2=%f \n", y2[i]);
                                printf("-----------  \n");
                                printf("z2=%f \n", z2[i]);
                                printf("FIM");
                            }
                        }

                        else {printf("Nao ha interceccao - ");}
                    }
                    //FIM DO IF DIVISOR

                    else {printf("Nao ha interceccao - ");}
                    

                   
                } //FIM DO FOR (int j)

        }
        
    return 0;
}