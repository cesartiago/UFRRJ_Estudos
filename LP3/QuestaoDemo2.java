import java.util.Scanner;

public class QuestaoDemo2 {
   public static void main(String[] args) {
      MultiplaEscolha questao1 = new MultiplaEscolha();
      questao1.setPergunta("Qual o nome original da linguagem Java?");
      questao1.adicionarAlternativa("*7", false);
      questao1.adicionarAlternativa("Duke", false);
      questao1.adicionarAlternativa("Oak", true);
      questao1.adicionarAlternativa("Gosling", false);
      questao1.adicionarAlternativa("Java1", false);


      MultiplaEscolha questa02 = new MultiplaEscolha();
      questa02.setPergunta("Em que pais nasceu o inventor do Java?");
      questa02.adicionarAlternativa("Australia", false);
      questa02.adicionarAlternativa("Canada", true);
      questa02.adicionarAlternativa("Denmark", false);
      questa02.adicionarAlternativa("United States", false);

      apresentarQuestao(questao1);
      apresentarQuestao(questa02);
   }

   public static void apresentarQuestao(MultiplaEscolha q) {
      q.perguntar();
      System.out.print("Sua resposta: ");
      Scanner in = new Scanner(System.in);
      String resposta = in.nextLine();
      System.out.println(q.verificarResposta(resposta));
   }
}

