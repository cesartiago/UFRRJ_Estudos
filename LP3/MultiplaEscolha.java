import java.util.ArrayList;

public class MultiplaEscolha extends Questao {
   private ArrayList<String> alternativas;

   public MultiplaEscolha() {
      alternativas = new ArrayList<String>();
   }

   public void adicionarAlternativa(String alternativa, boolean verdadeira) {
      alternativas.add(alternativa);
      if (verdadeira) {
         String alternativaCorreta = "" + alternativas.size();
         this.setResposta(alternativaCorreta);
      }
   }
   
   public void perguntar() {
      super.perguntar();
      for (int i = 0; i < alternativas.size(); i++) {
         int numAlternativa = i + 1;
         System.out.println(numAlternativa + ": " + alternativas.get(i));     
      }
   }
}

