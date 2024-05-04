import java.util.Scanner;

public class QuestaoDemo3
{
   public static void main(String[] args)
   {
      QuestaoBasica questao1 = new QuestaoBasica();
      questao1.setPergunta("Qual linguagem de programacao se aprende em LP3?");
      questao1.setResposta("Java");      

      MultiplaEscolha questao2 = new MultiplaEscolha();
      questao2.setPergunta("Em que pais nasceu o inventor de Java?");
      questao2.adicionarAlternativa("Australia", false);
      questao2.adicionarAlternativa("Canada", true);
      questao2.adicionarAlternativa("Denmark", false);
      questao2.adicionarAlternativa("United States", false);

      apresentarQuestao(questao1);
      apresentarQuestao(questao2);
   }

   /**
      Presents a question to the user and checks the response.
      @param questao the question
   */
   public static void apresentarQuestao(QuestaoBasica questao)
   {
      questao.perguntar();
      System.out.print("Sua resposta: ");
      Scanner in = new Scanner(System.in);
      String response = in.nextLine();
      System.out.println(questao.verificarResposta(response));
   }
}

