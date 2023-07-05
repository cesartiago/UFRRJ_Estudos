# Aluno: Tiago César  |  UFRRJ-SI  |  Inteligência Artificial  |  Dialoguei muito com 2 IAs nesse trabalho. Puxando da internet a maioria dos preços e notas.
# *Comentários com fins de estudo, revisão etc. Não se assuste, tenho esse costume de fazer bem explicadinho, principalmente para o futuro.

import random
import matplotlib.pyplot as plt #Para desenhar o gráfico

# Definir os componentes para cada categoria
    # Usando um "dicionário" (coleção não ordenada de pares chave-valor. (Diferenças: uma "lista" tem ordem)). CPU, GPU, RAM, Arm. são chaves no dicionário.
    # O "valor" de cada "chave" é associado a uma lista de dicionários.
componentes = {
    "CPU": [
        {"nome": "AMD Ryzen 5 3600", "preco": 1500, "nota_benchmark": 83.1},   # 1º item da lista (Para chamar: componentes["CPU"][0] -- Dicionário geral, dicionário CPU 'zero')
        {"nome": "Intel Core i5-11400F", "preco": 1200, "nota_benchmark": 70.4}, # 2º item da lista (componentes["CPU"][1] -- Dicionário do dicionário 'um')
        {"nome": "AMD Ryzen 5 5600G", "preco": 2000, "nota_benchmark": 87.9},
        {"nome": "Intel Core i5-11600KF", "preco": 1800, "nota_benchmark": 88.7},
    ],
    "GPU": [
        {"nome": "NVIDIA GeForce GTX 1660 Super", "preco": 2500, "nota_benchmark": 71.4},
        {"nome": "AMD Radeon RX 5600 XT", "preco": 3000, "nota_benchmark": 83.5},
        {"nome": "NVIDIA GeForce RTX 3060", "preco": 4000, "nota_benchmark": 79.6},
        {"nome": "AMD Radeon RX 6600 XT", "preco": 4500, "nota_benchmark": 107.0},
    ],
    "RAM": [
        {"nome": "16 GB RAM", "preco": 600, "nota_benchmark": 40},
        {"nome": "32 GB RAM", "preco": 1200, "nota_benchmark": 80},
        {"nome": "64 GB RAM", "preco": 2500, "nota_benchmark": 100},
    ],
    "Armazenamento": [
        {"nome": "1 TB HDD", "preco": 300, "nota_benchmark": 60},
        {"nome": "500 GB SSD", "preco": 400, "nota_benchmark": 50},
        {"nome": "1 TB SSD", "preco": 600, "nota_benchmark": 80},
    ],
}

# Definição dos pesos e capacidade da mochila
pesos = [componente["preco"] for categoria in componentes.values() for componente in categoria] # cria uma lista chamada "pesos" que armazena os preços de todos os componentes
capacidade_mochila = 7000
# componente["preco"] é o "valor" associado a chave "preco". O Py vê todas as chaves com esse nome, mesmo que dentro de uma lista dentro de uma "chave +externa"...
# O 1º for itera sobre os valores (listas), e o segundo sobre cada "componente" dessa lista.


# Função de fitness (avaliação de um indivíduo)
def fitness(individuo): #Um indivíduo é uma lista de índices que representam a escolha de componentes para cada categoria (CPU, GPU, RAM, Armazenamento).
    # Calcule "total_peso" do indivíduo somando os preços dos seus componentes selecionados:
    total_peso = sum(componentes[categoria][individuo[i]]["preco"] for (i, categoria) in enumerate(componentes.keys()))
    # Função "sum": recebe um iterável e retorna a soma dos elementos desse iterável.
    # " componentes[categoria][individuo[i]]["preco"] ": representa o preço do componente selecionado para cada categoria
    # for i, categoria in enumerate(componentes.keys()), percorremos as categorias e seus respectivos índices. A "vírgula" pode ser usada sem parêntes...
    # No final, se atribui cada índice à variável i e cada valor da chave à variável categoria mesmo. #Percorre as categorias de componentes (CPU, GPU, RAM, Armazenamento) usando enumerate(componentes.keys())


    #>>> OU SEJA: Some o preço para cada (i, categoria) nas chaves de componente.
    # Semelhante com o abaixo:

    if total_peso > capacidade_mochila:
        return 0
    total_nota = sum(componentes[categoria][individuo[i]]["nota_benchmark"] for i, categoria in enumerate(componentes.keys()))
    return total_nota
    # Retorna a nota total daquele indivíduo (soma das notas).

# Função de crossover (combinação de dois indivíduos para criar descendentes)
def crossover(individuo1, individuo2):
    ponto_corte = random.randint(1, len(individuo1) - 1)
    #O símbolo ":" é utilizado para fazer a indexação de uma lista ou fatiar uma sequência.
    filho1 = individuo1[:ponto_corte] + individuo2[ponto_corte:] #aqui o ":" é utilizado para criar as duas fatias (complementares).
    filho2 = individuo2[:ponto_corte] + individuo1[ponto_corte:]
    return filho1, filho2

# Função de mutação (alteração aleatória em um indivíduo)
def mutacao(individuo, taxa_mutacao):
    for i in range(len(individuo)):
        if random.random() < taxa_mutacao: #Para cada gene, é gerado um número aleatório entre 0 e 1 usando random.random()
            individuo[i] = random.randint(0, len(componentes[list(componentes.keys())[i]]) - 1) #o gene é alterado atribuindo um novo valor aleatório.
            # para retornar o tamanho (comprimento) da lista de componentes pertencentes à categoria em questão. Isso nos dá a quantidade total de opções disponíveis para aquele gene específico.
            #individuo[i] representa o índice do componente escolhido na categoria correspondente à posição i no indivíduo (ele é uma lista).
    return individuo




# Função de seleção (seleção de indivíduos para reprodução com base no seu valor de aptidão (fitness))
def selecao(populacao):
    fitness_total = sum(fitness(individuo) for individuo in populacao) # calcula a soma do valor total de aptidão da população
    probabilidades = [fitness(individuo) / fitness_total for individuo in populacao] # calcula e armazena nessa lista, as probabilidades de seleção para cada indivíduo na população

    pai = random.choices(populacao, probabilidades)[0] # é escolhido aleatoriamente de MANEIRA PONDERADA (proporcional ao seu valor de aptidão, OQ CALCULAMOS ACIM) um indivíduo da população.
    return pai


# Variável para armazenar as médias do fitness de cada geração
media_fitness_geracoes = []

# Algoritmo genético
def algoritmo_genetico(tamanho_populacao, taxa_mutacao, numero_geracoes):
    populacao = []
    for _ in range(tamanho_populacao): # "_" é o iterador convencional, lembra.

        #Uma list comprehension (uma expressão seguida por uma cláusula "for") para criar um novo indivíduo da população:
        individuo = [random.randint(0, len(componentes[categoria]) - 1) for categoria in componentes.keys()]
        #random.randint(0, len(componentes[categoria]) - 1) é utilizado para selecionar um índice aleatório para cada categoria de componente.
        #for categoria in componentes.keys() é a cláusula "for" que itera sobre as chaves do dicionário "componentes".A cada iteração, a variável "categoria" assume o valor de uma chave do dicionário.
        populacao.append(individuo)

    for geracao in range(numero_geracoes):
        nova_populacao = []
        for _ in range(tamanho_populacao):
            # Utilizando a "roleta viciada", selecionamos dois pais da população atual, usando a função "selecao" (é roleta, mais ponderada pelo fitness)
            pai1 = selecao(populacao)
            pai2 = selecao(populacao)

            filho1, filho2 = crossover(pai1, pai2)
            filho1 = mutacao(filho1, taxa_mutacao)
            filho2 = mutacao(filho2, taxa_mutacao)
            nova_populacao.append(filho1)
            nova_populacao.append(filho2)

        populacao = nova_populacao

        # Cálculo da média do fitness da população atual
        media_fitness = sum(fitness(individuo) for individuo in populacao) / len(populacao)

        # Armazenar a média do fitness na lista
        media_fitness_geracoes.append(media_fitness)

    melhor_individuo = max(populacao, key=fitness) #key=fitness indica que o critério de comparação para determinar o melhor indivíduo é o valor retornado pela função fitness.
    melhor_combinacao = [componentes[categoria][melhor_individuo[i]]["nome"] for (i, categoria) in enumerate(componentes.keys())] #Para cada categoria da melhor combinção, é acessado o componente correspondente ao índice melhor_individuo[i], obtendo o seu nome que é adicionado à lista melhor_combinacao.
    melhor_custo = sum(componentes[categoria][melhor_individuo[i]]["preco"] for (i, categoria) in enumerate(componentes.keys())) #Essa linha e a próxima segue a mesma lógica da de cima.
    melhor_nota = sum(componentes[categoria][melhor_individuo[i]]["nota_benchmark"] for (i, categoria) in enumerate(componentes.keys()))

    return melhor_combinacao, melhor_custo, melhor_nota

# Função para desenhar o gráfico da média do fitness por geração
def plot_fitness_media(media_fitness_geracoes):
    geracoes = range(1, len(media_fitness_geracoes) + 1)
    plt.plot(geracoes, media_fitness_geracoes)
    plt.xlabel('Geração')
    plt.ylabel('Fitness Médio (Nota média)')
    plt.title('Média do Fitness por Geração')
    plt.show()


# Execução do algoritmo genético
def main_Comentada():
    tamanho_populacao = 10
    taxa_mutacao = 0.1
    numero_geracoes = 10

    melhor_combinacao, melhor_custo, melhor_nota = algoritmo_genetico(tamanho_populacao, taxa_mutacao, numero_geracoes)

    print("\nMelhor combinação:", melhor_combinacao)
    print("   Custo total:", melhor_custo)
    print("   Nota total:", melhor_nota)

    plot_fitness_media(media_fitness_geracoes)

    print("- Valores da média do fitness por geração: -")
    for geracao, media_fitness in enumerate(media_fitness_geracoes, start=1):
        print(f"  Geração {geracao}: {media_fitness}")

main_Comentada()
