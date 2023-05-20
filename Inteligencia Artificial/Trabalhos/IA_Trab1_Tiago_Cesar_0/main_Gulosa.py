# Aluno: Tiago César            Disciplina: Inteligência Artificial
# Início: (05/05/2023)    Fim: (19/05/2023)

import desenho_labirinto as des # Tem que chamar como o nome, ou apelido. Se não, não chama o OUTRO ARQUIVO LÁ NÃO
import random
import Mapa_matematico as MapMat
from Robo import * #Pra classe precisa disso. Se ñ tem q escrever diferente parece...

robo1 = Robo(0,0,0,0,0) #Aqui ele ainda não foi desenhado. So criado

# Nosso "mapa" 12x12 = é uma lista de listas -> matriz 12x12. #!!! 11 É A ULTIMA COLUNA
mapa1 = MapMat.Mapa_matematico() #Cria novo objeto/instância
mapa1.desenhar_labirinto() #DESENHA O LABIRINTO VAZIO COM PAREDE NAS BORDAS (COM BLOCOS BRANCOS SEPARADOS E AZUIS NAS BORDAS)

for i in range(random.randint(35, 45)):
    mapa1.adicionar_obstaculo(random.randint(1, 10),random.randint(2, 10)) #DESENHAR OBSTÁCULOS AZUIS NO MEIO


linha_inicial = 2
coluna_inicial = 1

robo1.no_inicial = (linha_inicial,coluna_inicial)

#y,x INVENTER NO GRAFICO: (X= COLUNA Y+ LINHA)
mapa1.mover_robo(coluna_inicial, linha_inicial, robo1) #Desenha o robô VERDE pela primeira vez no mapa
#O ROBO NUNCA ESTARÁ NAS BORDAS



por_meta_na_coluna = random.randint(2, 10)
por_meta_na_linha = random.randint(2, 10)
mapa1.adicionar_meta(por_meta_na_coluna,por_meta_na_linha ) #DESENHAR META LARANJA/AMARELA
#A META NUNCA ESTARÁ NAS BORDAS


#pritando MAPA FINAL:
mapa1.print_matriz ()
print (robo1.posX, robo1.posY)


# Após a busca A* ser concluída com sucesso
# Exibir o caminho

robo1.encontrar_caminho_gulosa(mapa1)

def chamar_atualizar_posicao_robo(contador):
    robo1.atualizar_posicao_robo_gulosa(mapa1)
    robo1.encontrar_caminho_gulosa(mapa1)
    print("------> Y é ", robo1.posY, "coluna é", "=", por_meta_na_linha)

    # Verificar a condição depois de chamar a função várias vezes
    if robo1.posX != por_meta_na_coluna or robo1.posY != por_meta_na_linha:
        # Realizar ação desejada
        print("Condição NÃO alcançada")
        if contador < N:
            tempo = 500
            des.janela.after(tempo, lambda: chamar_atualizar_posicao_robo(contador + 1))



N = 100  # Número de vezes para chamar a função
#LIMITE DE MOVIMENTOS QUE BOTEI
chamar_atualizar_posicao_robo(1)  # Iniciar a primeira chamada


""" Inicie o loop de eventos da interface gráfica
# !!! "TUDO" PRECISA DE ESTAR ANTES DO LOOP!!!
#<<<^^^--------------------------------------^^^>>>
"""

des.janela.mainloop() #Assim como em Intr. Cp. Gráf. = precisa de ser um loop.

