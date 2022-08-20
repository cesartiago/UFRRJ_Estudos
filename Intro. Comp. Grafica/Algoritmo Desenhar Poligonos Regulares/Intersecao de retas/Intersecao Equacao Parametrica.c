#include <stdio.h>
#include <math.h>
//CRIADO POR: TIAGO CESAR

/*
float x1, x2, yi, y2;
float x3, x4, y3, y4;

t = 1.5; t2 = 1.5;
x1 = 0; yi = 0; x2 = 256; y2= 256;
x3 = 0; y3 = 0; x4 = 256; y4= 256;
*/



float t = 1;
float t2 = 2;
float t3 = -10;
float t4 = -10;

int main(){
    
    printf("Ola mundo.");


   
//Linha 1: com pontos x1,yi e x2,y2
    float x = (1-t)*0 + t*256;
    float y = (1-t)*0 + t*256;

//Linha 2: com pontos x3,y3 and x4,y4
    float xb = (1-t2)*0 + t2*256;
    float yb = (1-t2)*256 + t2*0;

//L3:
    float xc = t3;
    float yc = t3;

//L4:
    float xd = t4;
    float yd = -t4;
    
    
    for (int p = -10; p < 10; p++) { //O segundo bloco do for, é a condição de execução. Eu posso chamar de "enquanto", mesmo não sendo while.
    //O segundo bloco do for não é sobre a condiição final. É um se/enquanto. Mas indiretamente, fala dela.

         t3 = p;
         t4 = p;

    float xc = t3; //tem que chamar a função aqui pra mudar sempre seus valores. Pois não sobe até acabar o loop.
    float yc = t3;

    float xd = t4;
    float yd = -t4;

         //printf("%f", xd); Teste pra ver se tá mudando xd
         
         
         if (xd == xc && yd == yc)
         {
            printf("A interseção é em x= %f e y = %f COM O PARÂMETRO t = %f" , xd, yd, p);
         }
        
         
    }
    
   
    return 0;
}
