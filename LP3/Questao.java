public class Questao {
   private String pergunta;
   private String resposta;

   public Questao() {
      pergunta = "";
      resposta = "";
   }

   public void setPergunta(String perguntaQuestao) {
      pergunta = perguntaQuestao;
   }

   public void setResposta(String respostaCorreta) {
      resposta = respostaCorreta;
   }

   public boolean verificarResposta(String resposta) {
      return this.resposta.equals(resposta);
   }

   public void perguntar() {
      System.out.println(pergunta);
   }
}

