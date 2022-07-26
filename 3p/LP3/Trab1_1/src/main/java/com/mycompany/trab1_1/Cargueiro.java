package com.mycompany.trab1_1;

/**
 *
 * @author tiago
 */
public class Cargueiro extends Navio {
    int cargaMáximaTon;
    
    Cargueiro (String novonome, String novoanodeconstrução, int cargaMáximaTon){
    super (novonome, novoanodeconstrução);
    this.cargaMáximaTon = cargaMáximaTon;
    }
    
    @Override
    public String toString (){
        System.out.println ("Nome do cargueiro = " + nome + " -> Capacidade de carga = " + cargaMáximaTon);
        return "Nome do cargueiro = " + nome + " -> Capacidade de carga = " + cargaMáximaTon ;
    }
}
