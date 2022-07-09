package com.mycompany.testeproduto;

/**
 *
 * @author tiago
 */

public class Produto {
    String nome; //Atributo0
    //String, com "S" MAIÚSCULO SEMPRE AQUI EM JAVA!
    
      
    Produto (String nomeDado){ //TEM QUE TIPAR O DATO "String" nomeDado, entre os parênteses DO CONSTRUTOR TAMBÉM!
        this.nome = nomeDado; //É O ÚNICO CONSTRUTOR. NO DIAGRAMA, os construtores sçao os que no final a direita não tem "void", "String", tem nada!
    }
    
    /*public String Produto (String nome) {
    
    }
    */
    
    //TODOS OS NOSSOS MÉTODOS NÓS TEMOS QUE POR O TIPO DE RETORNO NA DECLARAÇÃO INICAL DELE: VOID, String etc!
    
    public String getNome () { /*E TEM QUE INFORMAR O TIPO DO RETURN EM MÉTODOS, LÁ EM CIMA, NA ESCRITA DO MÉTODO, DPS DE "PUBLIC"...
         POIS PODEM TER RETORNO! POR "VOID" SE NÃO TIVER! NUNCA POR VOID, INT ETC EM CONSTRUTOR! */
                
               
        return nome;
    }
    
    public void setNome (String novoNome) {
        this.nome = novoNome; //Que é o argumento acima escrito, entre parênteses
        
    }
}
