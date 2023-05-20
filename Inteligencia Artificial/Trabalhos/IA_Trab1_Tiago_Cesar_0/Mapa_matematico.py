# Aluno: Tiago César            Disciplina: Inteligência Artificial
# Início: (05/05/2023)    Fim: (19/05/2023)

import desenho_labirinto as des # Tem que chamar como o nome, ou apelido. Se não, não chama o OUTRO ARQUIVO LÁ NÃO
from Robo import * #Pra classe precisa disso. Se ñ tem q escrever diferente parece...
import heapq #Fornece funções para manipulação de filas de prioridade (também conhecidas como heaps) queue
import math

TAMANHO = 12
class Mapa_matematico:
    def __init__(self, tamanho=TAMANHO): #self": CONVENÇÃO que representa a própria instância do objeto.
        """Construtor da classe Mapa: "só 'tamanho' REALMENTE IMPORTA. Até aqui só estamos criando uma 12x12. "self" ñ é 1 variável q pode ser alterada p usuário da classe"""

        self.tamanho = tamanho
        self.mapa = [[0] * tamanho for _ in range(tamanho)] #Preencherá com zeros oq se criará: uma matriz "tamanho" por "tamanho".
                                    #loop "na faixa (de 12 elementos)" para iterar "tamanho_mapa" vezes (12x). Só p/ fins de aprendizado. Poderia ser só: mapa = [[0] * tamanho_mapa] * tamanho_mapa
        self.meta_local_coluna = None
        self.meta_local_linha = None
    def get_celula_mapa(self, linha, coluna):
        return self.mapa[linha][coluna] #!!! AQUI QUE INVERTE! <<<<<<<<<<<<<< MEU DEUS CARA! - Defini invertido em
    #POIS COLUNA 1, 2, 3 É O valor q corta a abscissa x.


    """
    ----------- COMEÇA MÉTODOS DO: A estrela (STAR) -------------
    """
    def calcular_custo_h(self, linha, coluna, meta):
        return abs(linha - meta[0]) + abs(coluna - meta[1])

    #A Estrela
    def encontrar_caminho(self, inicio, meta):
        fila_aberta = []
        heapq.heappush(fila_aberta, (0,inicio))  # objeto inicio deve ter a implementaçãodo método __lt__ (LESS THAN) para permitir a comparação entre instâncias da class
        # A função heapq.heappush é usada para adicionar elementos em uma fila de prioridade, onde o menor elemento tem prioridade...
        # ^ significa q inicio terá prioridade máxima na fila ("0") e será considerado o MENOR elemento em relação aos outros elementos presentes.
        nos_visitados = set()

        while fila_aberta:
            _, no_atual = heapq.heappop(
                fila_aberta)  #:  Dsempilhar (remover e retornar) o elemento de maior prioridade (no caso de um heap máximo) ou menor prioridade (no caso de um heap mínimo) do heap.
            # O caractere _ é utilizado para descartar o primeiro elemento da tupla retornada pela função heapq.heappop. Queremos só no_atual
            nos_visitados.add((no_atual.linha, no_atual.coluna))

            if (no_atual.linha, no_atual.coluna) == meta:
                caminho = []
                while no_atual:
                    caminho.append((no_atual.linha, no_atual.coluna))
                    no_atual = no_atual.pai
                caminho.reverse()
                return caminho

            vizinhos = self.obter_vizinhos(no_atual, meta)

            for vizinho in vizinhos:
                if (vizinho.linha, vizinho.coluna) not in nos_visitados:
                    heapq.heappush(fila_aberta, (vizinho.custo_total(), vizinho))  # Aqui usamos o __lt__ pra critério de desempate
                    """
                    Qnd vc chama heapq.heappush(fila_aberta, (vizinho.custo_total(), vizinho)), o módulo heapq compara as tuplas usando o operador < internamente. Para q a comparação seja possível, o método __lt__ precisa ser implementado na classe do objeto vizinho.

                    > Ao comparar as tuplas (vizinho.custo_total(), vizinho) durante a inserção, o módulo heapq utiliza o método __lt__ definido na classe do objeto vizinho
                    p/ determinar a ordem dos elementos caso os custos totais sejam iguais (empate). Isso permite uma comparação adequada e a ordenação correta dos objetos na fila de prioridade.
                    """

                    nos_visitados.add((vizinho.linha, vizinho.coluna))

        return None

    #A Estrela

    def obter_vizinhos(self, no, meta):
        vizinhos = []
        linha, coluna = no.linha, no.coluna
        direcoes = [(0, 1), (0, -1), (1, 0), (-1, 0), (1, 1), (-1, -1), (1, -1), (-1, 1)]

        for dx, dy in direcoes:
            nova_linha, nova_coluna = linha + dx, coluna + dy

            if (
                0 <= nova_linha < self.tamanho and
                0 <= nova_coluna < self.tamanho and
                self.mapa[nova_linha][nova_coluna] != 1
            ):
                custo_g = no.custo_g
                if dx == 0 and dy == 0:  # Ficar parado
                    custo_g += 1000
                elif abs(dx) == abs(dy):  # Movimento na diagonal
                    custo_g += math.sqrt(2) * 1  # Girar 45º tem custo 1
                else:  # Movimento na horizontal ou vertical
                    custo_g += 1  # Girar 45º tem custo 1

                custo_h = self.calcular_custo_h(nova_linha, nova_coluna, meta)
                vizinho = Robo(nova_linha, nova_coluna, custo_g, custo_h, no, (dx, dy))
                vizinhos.append(vizinho)

                # Criar vizinho adicional para a direção oposta
                oposto_dx, oposto_dy = -dx, -dy
                vizinho_oposto = Robo(nova_linha, nova_coluna, (oposto_dx, oposto_dy), custo_g, custo_h, no)
                vizinhos.append(vizinho_oposto)

        return vizinhos


    #A Estrela
    def imprimir_movimento(self, coordenadas):
        for linha in range(self.tamanho):
            for coluna in range(self.tamanho):
                if (linha, coluna) == coordenadas:
                    print("|", end=" ")  # Imprime o robô na posição atual
                elif self.mapa[linha][coluna] == 0:
                    print(".", end=" ")
                elif self.mapa[linha][coluna] == 1:
                    print("*", end=" ")
                elif self.mapa[linha][coluna] == 2:
                    print("@", end=" ")
            print()


    """
    ----------- FIM DOS MÉTODOS DO: A estrela (STAR) -------------
    """



    def adicionar_obstaculo(self, linha, coluna):
        self.mapa[coluna][linha] = 1 #!!! AQUI QUE INVERTE! <<<<<<<<<<<<<< MEU DEUS CARA!
        # POIS COLUNA 1, 2, 3 É O valor q corta a abscissa x.
        des.matriz_para_pontos(linha, coluna, 'BLUE')

    def adicionar_parede(self, linha, coluna):
        self.mapa[coluna][linha] = 11 #!!! AQUI QUE INVERTE! <<<<<<<<<<<<<< MEU DEUS CARA!
        # POIS COLUNA 1, 2, 3 É O valor q corta a abscissa x.
        des.matriz_para_pontos(linha, coluna, 'PINK')

    def adicionar_meta(self, linha, coluna):
        self.mapa[coluna][linha] = 2 #!!! AQUI QUE INVERTE! <<<<<<<<<<<<<< MEU DEUS CARA!
        # POIS COLUNA 1, 2, 3 É O valor q corta a abscissa x.
        des.matriz_para_pontos(linha, coluna, 'ORANGE') #FICA MEIO BEM AMARELO ESSE LARANJA
        self.meta_local_linha = linha
        self.meta_local_coluna = coluna

    def mover_robo(self, linha, coluna, robo):
        self.robo = robo

        robo.verificar_colisao_sensor(self,coluna,linha)

        self.mapa[coluna][linha] = 3 #!!! AQUI QUE INVERTE! <<<<<<<<<<<<<< MEU DEUS CARA!
        # POIS COLUNA 1, 2, 3 É O valor q corta a abscissa x.

        robo.posX = linha
        robo.posY = coluna
        des.matriz_para_pontos(linha, coluna, 'GREEN')

    def remover_robo(self, linha, coluna): #Deixar bloco branco

        #COMECEI USAR PARA TRAÇAR P CAMINHO
        self.mapa[coluna][linha] = 0 #!!! AQUI QUE INVERTE! <<<<<<<<<<<<<< MEU DEUS CARA!
        # POIS COLUNA 1, 2, 3 É O valor q corta a abscissa x.
        des.matriz_para_pontos(linha, coluna, '#808080') #AQUI É WHITE TO SO EM TESTE - ACABA SENDO RASTRO

        print("_________sssssssssssssssssss testandpo recpcao de param.", linha)

    def desenhar_labirinto (self): #Desenha matriz

        # Chame a função para desenhar o labirinto ANTES DE INICIAR O LOOP de eventos da interface gráfica "janela.mainloop()".
        des.desenhar_labirinto()

        for j in range(12):  # DESENHAR OBSTÁCULOS AZUIS NAS BORDAS
            #self.adicionar_obstaculo(0, j)
            #self.adicionar_obstaculo(j, 0)
            #self.adicionar_obstaculo(11, j)
            #self.adicionar_obstaculo(j, 11)
            self.adicionar_parede(0, j)
            self.adicionar_parede(j, 0)
            self.adicionar_parede(11, j)
            self.adicionar_parede(j, 11)


    def print_matriz (self):
        for linha_mapa in self.mapa:
            print(linha_mapa)
