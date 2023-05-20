# Aluno: Tiago César            Disciplina: Inteligência Artificial
# Início: (05/05/2023)    Fim: (19/05/2023)

import tkinter as tk # Importa a biblioteca tkinter e a renomeia como tk (biblioteca para criar interfaces gráficas simples em Py)

# Definindo dimensões do labirinto e os pontos de início e saída
largura_tela = 600 # = Da janela/tela, do canvas, do labirinto,
altura_tela = 600


# Definindo as dimensões da grade
num_linhas = 12
num_colunas = 12

# Calculando o tamanho de cada célula
tamanho_celula = largura_tela // num_colunas # (600/12 = 50)




janela = tk.Tk() # método Tk() = Pra inicializar a janela gráfica (É a base para add outros elementos gráficos. Como em Int. Cp. Gráf.)

# "canvas" sera um objeto da classe "Canvas". "Canvas" = área de desenho retangular. Dentro da janela.
canvas = tk.Canvas(janela, width=largura_tela, height=altura_tela)
canvas.pack()  # Empacota o canvas para exibir na janela.

# Definindo função para desenhar o labirinto
def desenhar_labirinto(): # "def" = assim se defini função em python.

    # Desenhando o labirinto:
    #Antigo canvas.create_rectangle(0, 0, largura_tela, altura_tela, fill="white")  # Seu fundo branco

    # Desenhando os quadrados em cada célula da grade (COM LINHAS PRETAS CONTORNANDO-OS) #!!! 11 É A ULTIMA COLUNA. 0 a primeira.
    for linha in range(num_linhas): #Vamos "esticar" o tamanho de um píxel: Primeiro, descubra o ponto inicial de cada cél., só multiplicar o índice pelo tamanho - teremos os múltimos do tamanho (0, 50, 100...)
        for coluna in range(num_colunas):
            x = linha * tamanho_celula #Achando a distância em relação a divisão em 12 partes (do 0 ao 11!!!) = (0*50, 1*50, 2*50...)
            y = coluna * tamanho_celula #Dessa forma, sempre será o ponto inicial, o vértice superior esquerdo do quadrado!...
            desenhar_quadrado(x, y, tamanho_celula, "WHITE") # Consigo chamar uma função antes de definí-la.

    # Gráfico cresce de baixo pra cima. Da esquerda pra direita


# Funç. para desenhar quadrado em uma célula da grade
def desenhar_quadrado(x, y, tamanho_celula, cor): #":" DOIS PONTOS + INDENTAÇÃO -> E NÃO "{ }"
    #AS  LINHAS PRETAS JÁ VEM NO QUADRADO

    # Ponto inicial
    canvas.create_rectangle(
        x, #...A partir do ponto inicial...
        y,
        x + tamanho_celula, #...Some o tamanho da célula.
        y + tamanho_celula,
        fill= cor,
        outline = "black"  # Ñ precisa, é implícito já
    )

    # Nosso "mapa" 12x12 = é uma lista de listas -> matriz 12x12. #!!! 11 É A ULTIMA COLUNA

# Traduzindo os índices da matriz/mapa, para o seu ponto inicial (x,y)
def matriz_para_pontos (linha,coluna,cor):

            x = linha * tamanho_celula  # Achando a distância em relação a divisão em 12 partes (do 0 ao 11!!!) = (0*50, 1*50, 2*50...)
            y = coluna * tamanho_celula  # Dessa forma, sempre será o ponto inicial, o vértice superior esquerdo do quadrado!...
            desenhar_quadrado(x, y, tamanho_celula, cor)  # Consigo chamar uma função antes de definí-la.


