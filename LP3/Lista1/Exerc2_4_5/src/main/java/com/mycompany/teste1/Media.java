package com.mycompany.teste1;

public class Media {
    double Av1;
    double Av2;
    
    public Media (){ //Construtor padrão, vai dar os valores padrão nesse caso, zero (0.0)
           }    
    public Media (double p1, double p2) { //Não pode ter return pois é um construtor. E não pode nem escrever void aqui!
    this.Av1 = p1;
    this.Av2 = p2;
    }
    public double calcularMedia (){ //Isso pe um MÉTODO, e tem return não vazio
        return (Av1+Av2)/2;
    }
}
