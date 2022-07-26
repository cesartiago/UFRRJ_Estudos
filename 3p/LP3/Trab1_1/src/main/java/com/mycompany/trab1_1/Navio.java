
package com.mycompany.trab1_1;

/**
 *
 * @author tiago
 */
public class Navio {
    String nome;
    String anodeconstrução;
    
    Navio (String novonome, String novoanodeconstrução) //Construtor não tem "public" nem retorno "void" etc. Só o no "Classe" msm
    {
        nome = novonome; //PRECISA DO this. EM CONSTRUTORES?
        anodeconstrução = novoanodeconstrução; //PRECISA DO this. EM CONSTRUTORES?
    }
    
    public String getNome (){
        return nome; //PRECISA DO this. EM CONSTRUTORES em MÉTODOS?
    }
    
    public void setNome (String novoNome){ //Se fosse (... nome), ai tería que usar o this.nome abaixo, p/ separar a variável local "nome", da variável de instância "nome"
        nome = novoNome; //Se fosse "nome" entre parênteses, como variável local, ai eu ia precisar do "this".nome aqui. Como não é, não precisa!
    }
    
    @Override
    public String toString (){
    //"Texto inteiro entre aspas" + sinaldemais + "texto aspas"
    System.out.println("Nome do navio = " + nome + " -> Ano de Construção = " + anodeconstrução);
    return "Nome do navio = " + nome + " -> Ano de Construção = " + anodeconstrução; /*Eu necessito de escrever um retorno de string, mesmo que
    o enunciado não tenha pedido. Pois toString já vem como String, e não pode ser alterado para void.
    */    
    }
    
}
