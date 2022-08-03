package com.mycompany.testecirculo;
import javax.swing.JOptionPane;

/**
 *
 * @author th
 */
public class TesteCirculo {

    public static void main(String[] args) {
        Circulo circulo01 = new Circulo (5.0);
        JOptionPane.showMessageDialog (null, "Perímetro do Círculo =" + circulo01.calcularPerimetro()); /*MÉTODOS, ASSIM COMO FUNCÕES, TEM RETORNO E TAL
                 E TEM QUE POR O () NO FINAL!*/
        
    }
}
