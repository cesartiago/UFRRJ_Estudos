Class Main Aluno:
import java.util.ArrayList;
import java.util.Map.Entry;
import java.util.Scanner;
import java.util.HashMap;

public class Aluno {

public static void main(String[] args){
    HashMap<Integer, ArrayList<String>> alunos = new HashMap
<Integer, ArrayList<String>>();

    Scanner in = new Scanner(System.in);
    int mat;

    System.out.println("---------------------------------------------
--------------------------------------");
    System.out.println("Formato de matricula desejavel: ano entrada
em xxxx + 7 numeros, Exemplo: 20140043804");
    System.out.println("Formato de disciplina desejavel: sigla do
departamento em xx + codigo, Exemplo: IC403");
    System.out.println("Digitar -1 na matricula sai do programa e
mostra os alunos cadastrados!");
    System.out.println("---------------------------------------------
--------------------------------------");

while(true){
        System.out.printf("Digite a matricula: ");
        mat = in.nextInt();
        if(mat == -1)
        break;
        System.out.printf("Digite o codigo da disciplina: ");
        String codigo = in.next();
        ArrayList<String> disciplina = alunos.get(mat);
        if(disciplina == null) {
        disciplina = new ArrayList<>();
        alunos.put(mat, disciplina);
        }
        disciplina.add(codigo);
        }
        for(Entry<Integer, ArrayList<String>> entry : alunos.entrySet())
        {
        System.out.println(entry.getKey() + ": " +
        entry.getValue());
        }
        in.close();
    }
}
