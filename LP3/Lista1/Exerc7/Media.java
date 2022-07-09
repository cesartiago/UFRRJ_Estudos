package com.mycompany.testemedia;
import javax.swing.JOptionPane; //Utiliza a classe JOptioPane que se encontra na biblioteca do Java, no pacote javax.swing


/**
 *
 * @author Th
 */
public class TesteMedia {

    public static void main (String[] args) { //Aqui fica nossa main //"String[] args" serve tipo pra iniciar o programa pelo terminal parece...
        Media Maria = new Media (6.23,4.12);        
        Media Marco = new Media (6.27,5.40);
        
        JOptionPane.showMessageDialog (null, "Media de Maria =" + Maria.calcularMedia());
        JOptionPane.showMessageDialog (null, "Media de Marco =" + Marco.calcularMedia());
        
        
    }
}
