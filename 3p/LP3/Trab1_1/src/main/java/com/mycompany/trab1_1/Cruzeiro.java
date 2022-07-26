package com.mycompany.trab1_1;

/**
 *
 * @author tiago
 */
public class Cruzeiro extends Navio
{
    int capacidadeMaximadePassageiros;

    Cruzeiro (String novonome, String novoanodeconstrução, int capacidadeMaximadePassageiros ){ //Construtor
        super (novonome, novoanodeconstrução); //super = Usando o método construtor da classe super (superclasse), da classe mãe
        this.capacidadeMaximadePassageiros = capacidadeMaximadePassageiros; 
    }
    
    public int getCapacidadeMaximadePassageiros (){
        return capacidadeMaximadePassageiros; //PRECISA DO this. EM CONSTRUTORES em MÉTODOS?
    }
    
    public void setCapacidadeMaximadePassageiros (int capacidade){ //Método
       capacidadeMaximadePassageiros = capacidade;
    }
        
    @Override
    public String toString (){
        
    System.out.println("Nome do cruzeiro = " + nome + " -> Nº máximo de passageiros = " + capacidadeMaximadePassageiros);
    return "Nome do cruzeiro = " + nome + " -> Nº máximo de passageiros = " + capacidadeMaximadePassageiros;
        
    }
    
     /*
    Cruzeiro (int capacidadeMaximadePassageiros)  //Construtor QUE NÃO FUNCIONOU 1(COM EXTENDS) AQUI
    {
        this.capacidadeMaximadePassageiros = capacidadeMaximadePassageiros; //Usei o this para diferenciar variável de instância da local.
    }
    */
    
    /*
    public Cruzeiro() { //Construtor que NÃO FUNCIONA 2 (COM EXTENDS) AQUI
        capacidadeMaximadePassageiros = 10; 
    }
    */
    
   
}
