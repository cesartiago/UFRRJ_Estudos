/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Camisa;

import javax.swing.JOptionPane;
import net.sourceforge.jFuzzyLogic.FIS;
import net.sourceforge.jFuzzyLogic.FunctionBlock;
import net.sourceforge.jFuzzyLogic.Gpr;
import net.sourceforge.jFuzzyLogic.plot.JFuzzyChart;
import net.sourceforge.jFuzzyLogic.rule.Variable;

/**
 * Test parsing an FCL file
 * @author1: Gizelle
 * @author2: Tiago César
 * 
 *Ideia: Cálculo da desvalorização média do preço de uma camisa usada
 *para o seguinte contexto: você é dono de um brechó, e quer fazer a avaliação
 *média da desvalorização de uma camisa (recém chagada) a partir do preço original.
 */
public class TesteCamisa {

	public static void main(String[] args) throws Exception {
		// Carrega o arquivo .FCL
		String fileName = "C:\\Users\\tiago_2\\Trabalho 3 - Fuzzy (Logica Nebulosa)\\Desvalorizacao_Camisa_Comum_Fuzzy\\src\\Camisa\\camisa.fcl";
                //^PONHA SEU CAMINHO ACIMA.
		FIS fis = FIS.load(fileName, true);
		if (fis == null) { // Erro de arquivo
			System.err.println("Arquivo inexistente: '" + fileName + "'");
			return;
		}

		// mostra o conjunto de regras
		FunctionBlock functionBlock = fis.getFunctionBlock(null);
                JFuzzyChart.get().chart(functionBlock);

		// escolhe entradas
                String nota = JOptionPane.showInputDialog("O quão gasta está a camisa de 0 à 10? (0 = quase nada, 10 = Extremamente gasta - O estado da roupa)");
		functionBlock.setVariable("estado_da_roupa", Float.parseFloat(nota));
                nota = JOptionPane.showInputDialog("Quantos anos de uso a roupa tem?");
                functionBlock.setVariable("anos_de_uso", Float.parseFloat(nota));

		// Avalia as regras 
		functionBlock.evaluate();

		// Mostra o gráfico de conclusões
		Variable tip = functionBlock.getVariable("desvalorizacao");
		JFuzzyChart.get().chart(tip, tip.getDefuzzifier(), true);
		Gpr.debug("velha[estado_da_roupa]: " + functionBlock.getVariable("estado_da_roupa").getMembership("velha"));
		Gpr.debug("seminova[estado_da_roupa]: " + functionBlock.getVariable("estado_da_roupa").getMembership("seminova"));
		Gpr.debug("nova[estado_da_roupa]: " + functionBlock.getVariable("estado_da_roupa").getMembership("nova"));
		Gpr.debug("poucos[anos_de_uso]: " + functionBlock.getVariable("anos_de_uso").getMembership("poucos"));
		Gpr.debug("alguns[anos_de_uso]: " + functionBlock.getVariable("anos_de_uso").getMembership("alguns"));
		Gpr.debug("muitos[anos_de_uso]: " + functionBlock.getVariable("anos_de_uso").getMembership("muitos"));

		// Imprime as regras no console
		System.out.println(functionBlock);
                
                //Resposta final:
                String texto = "Em porcentagem, a desvalorizacao será (em cima do preço original): " + functionBlock.getVariable("desvalorizacao").getValue();
                JOptionPane.showMessageDialog(null, texto);
                
	}
}