package com.mycompany.testeproduto;
import javax.swing.JOptionPane; //Utiliza a classe JOptioPane que se encontra na biblioteca do Java, no pacote javax.swing


/**
 *
 * @author Th
 */
public class TesteProduto {

    public static void main (String[] args) { //Aqui fica nossa main //"String[] args" serve tipo pra iniciar o programa pelo terminal parece...
                
              
        Produto Bugatti = new Produto ("Bugatti"); //Precisa de aspas para ser String!
        JOptionPane.showMessageDialog (null, "Carro Frânces ->" + Bugatti.nome);
    }
}
