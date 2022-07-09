package com.mycompany.teste1;

public class Media {
    double Av1;
    double Av2;
    
    public Media (){
           }    
    public Media (double p1, double p2) {
    this.Av1 = p1;
    this.Av2 = p2;
    }
    public double calcularMedia (){
        return (Av1+Av2)/2;
    }
}
