# Aluno: Tiago César            Disciplina: Inteligência Artificial
# Início: (05/05/2023)    Fim: (19/05/2023)

class Robo:
    def __init__(self,  opcao1, opcao2, opcao3, opcao4, opcao5 = None, opcao6 = None):
        self.direcao_angulo_atual = opcao1
        self.posX = opcao2
        self.posY = opcao3
        self.movimento = opcao4
        self.modo_de_busca = 0
        self.melhor_movimento = [0, 0]  # [y,x] -> (linha,coluna): (y,x)
        self.movimentos_selecionados = [[] for _ in range(2)]  # Cria uma lista com duas listas vazias (duas linhas)

        self.lista_Abertos  = []
        self.lista_Fechados  = []
        self.pais = [[None] * 12 for _ in range(12)]  # Matriz para armazenar os nós pais
        # Variável do tipo Tuple[int, int]
        self.no_atual: Tuple[int, int] = ()
        self.no_inicial: Tuple[int, int] = ()

        self.linha = opcao1
        self.coluna = opcao2
        self.custo_g = opcao3
        self.custo_h = opcao4
        self.pai = opcao5
        self.direcao = opcao6

        # Para altera a posição do robô A ESTRELA NO FINAL
        self.linha_A = None
        self.coluna_A = None

    def custo_total(self):
        return self.custo_g + self.custo_h

    def __lt__(self, outro): #Esse método é chamado implicitamente quando você usa o operador < para comparar dois objetos da classe.
        """
         __lt__ é usado para o critério de desempate quando dois elementos têm o mesmo custo total
        """
        return self.custo_total() < outro.custo_total()

    """
    NÃO USE ESSES OUTROS MÉTODOS DE VC PASSOU VALORES PENSANDO EM A ESTRELA (PYTHON Ñ PERMITE 2 CONSTRUTORES, FIZ UMA JOGADA)
    """


    def encontrar_caminho_gulosa (self, mapa):

        self.mapa = mapa

        self.movimentos_selecionados[0].append(self.posY)  # !!!LISTA (Ñ VETOR). [INDÍCE DA TUPLA: PRIMEIRA = 0 SEGUNDA = 1) # "y" linha.  Pois é formado por (linha,coluna): (y,x)
        self.movimentos_selecionados[1].append(self.posX)




        # "j" é a altura. "i" a linha
        #lembrando que aqui, "J" cresce pra BAIXO, COMO A JANELA.
        #MATRIZ VIZINHOS: 3X3

        vizinhos = [[None] * 3 for _ in range(3)]  # cria matriz 3x3 com valores None
        i = self.posX #Realmente x (coluna se fosse matriz)
        j = self.posY #Realmente y (linha se fosse matriz)
        print (mapa.get_celula_mapa(j, i))
        print( "Self positions: >>>", self.posX, self.posY)

        self.custo_ate_obstaculo_e_giro_ = 1888


        #DICIONÁRIO
        direcoes = {
            "Cima-Esquerda": {"angulo": 135, "i": -1, "j": -1},
            "Esquerda": {"angulo": 180, "i": -1, "j": 0},
            "Baixo-Esquerda": {"angulo": 225, "i": -1, "j": 1},
            "Cima": {"angulo": 90, "i": 0, "j": -1},
            "Atual": {"angulo": 0, "i": 0, "j": 0},
            "Baixo": {"angulo": 270, "i": 0, "j": 1},
            "Cima-Direita": {"angulo": 45, "i": 1, "j": -1},
            "Direita": {"angulo": 0, "i": 1, "j": 0},
            "Baixo-Direita": {"angulo": 315, "i": 1, "j": 1}
        }
        ordem_direcoes = ["Cima-Esquerda", "Esquerda", "Baixo-Esquerda", "Cima", "Atual",
                          "Baixo", "Cima-Direita", "Direita", "Baixo-Direita"]
        indice_direcao = 0

        # Inicialização de variáveis

        menor_custo_total = float("inf")

        # Direção atual do agente
        direcao_atual = 270

        # Matriz para armazenar os custos totais de cada célula
        custo_finais = [[0 for _ in range(len(vizinhos[0]))] for _ in range(len(vizinhos))]
        custo_giros = [[0 for _ in range(len(vizinhos[0]))] for _ in range(len(vizinhos))]
        # Inicialize a matriz de vizinhos_distancia_manhattan
        vizinhos_distancia_manhattan = [[None] * 3 for _ in range(3)]

        #VASCULHANDO VIZINHOS
        #NÃO PRECISA DE LIMITAR POIS O ROBO E A META NAO PODEM IR PRAS BORDAS. DEFINI JÁ.
        for k in range(-1,2):  # o 1º valor representa o número inicial da sequência e o segundo valor representa o número final da sequência (não incluso). Exemplo, range(3, 6) gerará a sequência [3, 4, 5].
            for l in range(-1, 2):

                self.custo_ate_obstaculo_e_giro_ = 0
                vizinhos[k + 1][l + 1] = mapa.get_celula_mapa(j+k,i+l)  # tem q inverter j e l aqui. Pois é x e y do cartesiano seus valores. E ñ Lin. X Col.
                # ^VASCULHANDO VIZINHOS

                # PASSANDO VALOR (i+k, j+l) pro dicionário
                direcao = ordem_direcoes[
                    indice_direcao]  # elemento 0,1 etc da lista. Retorna uma "palavra" que é a "CHAVE" do dicionário

                direcoes[direcao]["i"] = i + k
                direcoes[direcao]["j"] = j + l

                # CALCULANDO HEURÍSTICA - Cada distância de Manhattan:

                vizinhos_distancia_manhattan[k + 1][l + 1] = abs(i + l - mapa.meta_local_linha) + abs(j+k - mapa.meta_local_coluna)
                # inverte i e j, pois correspondem a [i é linha = y] [j é coluna = x]

                """
                vizinhos_distancia_manhattan [k + 1][l + 1] = abs ( (i+k - mapa.meta_local_linha) + (j+l - mapa.meta_local_coluna) )
                #É UMA VARIÂNCIA DO MANHATTAN QUE FIZ NA REAL. COM O MÓDULO NO FINAL DE TODA A CONTA SÓ, NAO DENTRO DELA.
                """

                indice_direcao = (indice_direcao + 1) % len(ordem_direcoes)
                # Quando o índice atinge o comprimento da lista, o operador módulo reinicia a contagem do índice do início da lista.

                if k == 0 and l == 0:
                    # Célula do meio, adiciona um custo adicional - CUSTO DE FICAR PARADO
                    self.custo_ate_obstaculo_e_giro_ += 1000


                direcao_vizinho = direcoes[ordem_direcoes[(l + 1) * 3 + (k + 1)]]

                # Verifica se a célula vizinha contém o valor 1 = SE É UM OBSTÁCULO
                if vizinhos[k + 1][l+1] == 1:
                    self.custo_ate_obstaculo_e_giro_ += 1000

                # Verifica se a célula vizinha contém o valor 11 = É UMA PAREDE
                if vizinhos[k + 1][l + 1] == 11:
                    self.custo_ate_obstaculo_e_giro_ += 111111

                # Cálculo do custo de giro
                diferenca_angulo = (direcao_vizinho["angulo"] - direcao_atual) % 360
                if diferenca_angulo > 180:
                    diferenca_angulo = 360 - diferenca_angulo

                custo_girar_ou_n = diferenca_angulo // 45

                if k == 0 and l == 0:  # Se for o do meio...
                    custo_girar_ou_n = 0 #Custo de giro igual a zero (podia fazer uma exclusão de (0,0) desse Cálculo do custo de giro mas ñ rodava ñ sei pq e tá acabando o prazo. Deixei assim msm

                self.custo_ate_obstaculo_e_giro_ += custo_girar_ou_n

                custo_giros[k + 1][l + 1] = custo_girar_ou_n
                custo_finais[k + 1][l + 1] = self.custo_ate_obstaculo_e_giro_ + vizinhos_distancia_manhattan[k + 1][l + 1]

                if custo_finais[k + 1][l + 1] < menor_custo_total and all( (j+k, i+l) != (x, y) for x, y in zip(self.movimentos_selecionados[0], self.movimentos_selecionados[1]) ):
                    menor_custo_total = custo_finais[k + 1][l + 1]
                    #melhor_movimento = (k, l, direcao_vizinho, i, j)
                    self.melhor_movimento[0] = j+k # "y" linha.  Pois é formado por (linha,coluna): (y,x)
                    self.melhor_movimento[1] = i+l # "x" coluna.   Pois é formado por (linha,coluna): (y,x)




        for key in direcoes:
            print(f"{key}: {direcoes[key]}")


        print("\n Vizinhos:")
        for linha in vizinhos:
            print(linha)

        print("\n Mapa com heurísticas correspondentes:")
        for linha in vizinhos_distancia_manhattan:
            print(linha)

        print("Custo de cada giro:")
        for linha in custo_giros:
            print(linha)

        print(" \n melhor_movimento =", self.melhor_movimento, "               Linha, coluna, (y,x)")
        print("custo_final:")
        for linha in custo_finais:
            print(linha)

        print("\n Menor custo:", menor_custo_total)

        self.movimentos_selecionados[0].append(self.melhor_movimento[0])  # !!!LISTA (Ñ VETOR). [INDÍCE DA TUPLA: PRIMEIRA = 0 SEGUNDA = 1) # "y" linha.  Pois é formado por (linha,coluna): (y,x)
        self.movimentos_selecionados[1].append(self.melhor_movimento[1])
        # ^ "x" coluna.   Pois é formado por (linha,coluna): (y,x)
        print("GUARDEI O VALOR SELECIONADO = ", self.movimentos_selecionados[0])  # !!!LISTA (Ñ VETOR). [INDÍCE DA TUPLA: PRIMEIRA = 0 SEGUNDA = 1)
        print("GUARDEI O VALOR SELECIONADO = ", self.movimentos_selecionados[1],
              "\n")  # !!!LISTA (Ñ VETOR). [INDÍCE DA TUPLA: PRIMEIRA = 0 SEGUNDA = 1).
        # Ex. de lista: lista2 = [1, 2, 3]  # Lista com valores iniciais

        return self.melhor_movimento

    """
    xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    """


    def atualizar_posicao_robo_gulosa(self, mapa):
        self.mapa = mapa

        #des.matriz_para_pontos(self.posX, self.posY, 'RED')  # Aqui desenhamos o robo
        posXAntiga = self.posX
        posYAntiga = self.posY

        # Altera a posição do robô
        self.posY = self.melhor_movimento[0]
        self.posX = self.melhor_movimento[1]




        #Guardar melhores posições numa lista para iterar depois.

        # LIMPA O DESENHO ANTIGO (ONDE TAVA O ROBO)
        mapa.remover_robo(posXAntiga, posYAntiga)
        # Atualiza o desenho do robô na tela
        mapa.mover_robo(self.posX, self.posY, self)  # Pq robo está no mapa matemático. Se não, eu botaria em robo mesmo.

    def atualizar_posicao_robo_a_star(self, mapa,indice_do_par, caminho):
        self.mapa = mapa
        self.indice_do_par = indice_do_par
        self.caminho = caminho
        #des.matriz_para_pontos(self.caminho[indice_do_par][0], self.caminho[indice_do_par][1], 'RED')  # Aqui desenhamos o robo

        print("Q NÉGOCIO DIFICIL... X E Y", indice_do_par)

        #des.matriz_para_pontos(self.caminho[0][1], self.caminho[0][0], 'RED')  # Aqui desenhamos o robo
        posXAntiga = 2
        posYAntiga = 1
        print ("___________" , posXAntiga)

        # Altera a posição do robô
        self.posY = self.caminho[indice_do_par][1]
        self.posX = self.caminho[indice_do_par][0]


        # LIMPA O DESENHO ANTIGO (ONDE TAVA O ROBO)
        #mapa.remover_robo(posXAntiga,posYAntiga ) #INVERTIDO <<<
        # Atualiza o desenho do robô na tela -> DESENHA ELE VERDE
        mapa.mover_robo(self.posY, self.posX,self)  # Pq robo está no mapa matemático. Se não, eu botaria em robo mesmo.

    def por_decisao_no_grafico(self, mapa,indice_do_par,caminho):
        self.mapa = mapa
        self.indice_do_par = indice_do_par
        self.caminho = caminho

        print("VALOR DE INDICE AAAAAAAAAAAAAAAA", indice_do_par)
        self.linha_A = caminho[0][0]  # Par 0, elemento 0. Pares = (elemento 0, elemento 1)
        self.coluna_A = caminho[0][1]  # Par 0, elemento 1. Pares = (elemento 0, elemento 1)

    # SENSOR PARA VERIFICAR COLISÃO (NO CASO, TO DEIXANDO PASSAR PRA SEGUIR SO A LOGICA DO CUSTO")
    def verificar_colisao_sensor(self, mapa, coluna,linha):
        if mapa.get_celula_mapa(coluna,linha) == 1:
            print("COLISÃO: O robô bateu em um obstáculo!")
