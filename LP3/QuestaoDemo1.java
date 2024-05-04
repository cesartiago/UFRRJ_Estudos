import java.util.Scanner;

public class QuestaoDemo1 {
   public static void main(String[] args) {
      Scanner in = new Scanner(System.in);

      Questao q = new Questao();
      q.setPergunta("Qual a capital do Brasil?");
      q.setResposta("Brasilia");      

      q.perguntar();
      System.out.print("Sua resposta: ");
      String resposta = in.nextLine();
      System.out.println(q.verificarResposta(resposta));
   }
}