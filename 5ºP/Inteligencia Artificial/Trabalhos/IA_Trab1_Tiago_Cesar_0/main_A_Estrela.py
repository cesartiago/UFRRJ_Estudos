# Aluno: Tiago César            Disciplina: Inteligência Artificial
# Início: (05/05/2023)    Fim: (19/05/2023)

import random
import Mapa_matematico as MapMat
import desenho_labirinto as des # Tem que chamar como o nome, ou apelido. Se não, não chama o OUTRO ARQUIVO LÁ NÃO
import main_A_Estrela
from Robo import * #Pra classe precisa disso. Se ñ tem q escrever diferente parece...

linha_inicial = 2
coluna_inicial = 1

inicio = Robo(linha_inicial, coluna_inicial, 0, None, None, (0,0)) #Aqui ele ainda não foi desenhado. So criado

# Nosso "mapa" 12x12 = é uma lista de listas -> matriz 12x12. #!!! 11 É A ULTIMA COLUNA
mapa1 = MapMat.Mapa_matematico() #Cria novo objeto/instância
mapa1.desenhar_labirinto() #DESENHA O LABIRINTO VAZIO COM PAREDE NAS BORDAS (COM BLOCOS BRANCOS SEPARADOS E AZUIS NAS BORDAS)

for i in range(random.randint(25, 45)):
    mapa1.adicionar_obstaculo(random.randint(1, 10),random.randint(2, 10)) #DESENHAR OBSTÁCULOS AZUIS NO MEIO


#y,x INVENTER NO GRAFICO: (X= COLUNA Y+ LINHA)
mapa1.mover_robo(coluna_inicial, linha_inicial, inicio) #Desenha o robô VERDE pela primeira vez no mapa
#O ROBO NUNCA ESTARÁ NAS BORDAS

por_meta_na_coluna = random.randint(2, 10)
por_meta_na_linha = random.randint(2, 10)
mapa1.adicionar_meta(por_meta_na_coluna,por_meta_na_linha ) #DESENHAR META LARANJA/AMARELA
#A META NUNCA ESTARÁ NAS BORDAS

#Para A estrela (A Star)
caminho = mapa1.encontrar_caminho(inicio, (por_meta_na_linha, por_meta_na_coluna))

#pritando MAPA FINAL:
mapa1.print_matriz ()
print (inicio.posX, inicio.posY)

nao_rodar_grafico = 0 #Pra não forçar ele desenhar sem ter achado caminho
Passos_dados = 0

tempo = 0
indice_do_par = 0  # por algum MOTIVO - TEM QUE SER -1

def chamar_atualizar_posicao_robo():

    inicio.atualizar_posicao_robo_a_star(mapa1,indice_do_par, caminho)
    main_A_Estrela.indice_do_par += 1

if caminho:
    print("Caminho encontrado:")

    for i, (linha, coluna) in enumerate(caminho):
        print(f"Passo {i}: linha {linha}, coluna {coluna}")
        mapa1.imprimir_movimento((linha, coluna))

        Passos_dados = i+1
        print("\n")


else:
    print("Não foi possível encontrar um caminho até a meta.")
    nao_rodar_grafico = 1


print ("caminho -->", caminho)


if nao_rodar_grafico !=1:
    tempo = 0
    for i in range(Passos_dados):  # Executa 10 vezes
        tempo += 650

        des.janela.after(tempo, chamar_atualizar_posicao_robo )  # TEM QUE TER UMA FUNÇÃO PRA SE CHAMAR!
        print ("VALOR DE I", i)
        #print("VALOR DE INDICE no for", indice_do_par)


""" Inicie o loop de eventos da interface gráfica
# !!! "TUDO" PRECISA DE ESTAR ANTES DO LOOP!!!
#<<<^^^--------------------------------------^^^>>>
"""
#mapa.adicionar_obstaculo(2, 2)


des.janela.mainloop() #Assim como em Intr. Cp. Gráf. = precisa de ser um loop.

