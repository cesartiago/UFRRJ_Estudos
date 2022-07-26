package com.mycompany.trab1_1;

/**
 *
 * @author tiago
 */
public class Trab1_1 {

    public static void main(String[] args) {
        
        //Navio Navio1 = new Navio("Triplo A","2010");
        //Navio1.toString();
        
        /*
        ISSO NÃO RODA AQUI:
        Cruzeiro Cruzeiro2 = new Cruzeiro();
        Cruzeiro2.nome = "a";
        Cruzeiro2.anodeconstrução = "2022";
        */
        
        //Cruzeiro Cruzeiro1 = new Cruzeiro ("CRUZEIRO1 S.A.","1889",10);
        //Cruzeiro1.setNome("asbs"); //Setando nome, o extends permite usar um método que só tá escrito na classe mãe, não na filha
        //Cruzeiro1.toString();

        //Cargueiro Cargueiro1 = new Cargueiro ("CARGUEIRO 1 S.A", "1958", 600);
        //Cargueiro1.toString();
        
       Navio [] vetordeNavios = new Navio [10]; //Estrutura do vetor = Tipo/Classe [] nome' = new Tipo/Classe []
       
       vetordeNavios [0] = new Cargueiro ("C-Jhonny", "1995", 500); //Isso não é um vetor de CLASSES, É UM VETOR DE OBJETOS. Por isso, descrevemos as propriedades dos objetos
       vetordeNavios [1] = new Navio ("N-Kajota", "2008");
       vetordeNavios [2] = new Cruzeiro ("Cz-JLanson", "2001", 400);
       vetordeNavios [3] = new Cruzeiro ("Cz-JLanson", "1991", 830);
       vetordeNavios [4] = new Cruzeiro ("Cz-JLanson", "1990", 790);
       vetordeNavios [5] = new Navio ("N-JLanson", "1978");
       vetordeNavios [6] = new Navio ("N-JLanson", "2005");
       vetordeNavios [7] = new Navio ("N-JLanson", "2004");
       vetordeNavios [8] = new Cargueiro ("C-lil", "2002", 900);
       vetordeNavios [9] = new Cargueiro ("C-yang", "2022", 820);
       
       for (int i =0; i<10; i++){
           vetordeNavios[i].toString();
       }
    
    
    
    }
}
