import random
#Criando um conjunto de pontos aleatórios entre 1 e 13
pontos = []
for i in range(20):
    x = random.randint(1,13)
    y = random.randint(1,13)

    # Gerando um número aleatório entre 0 e 1 para determinar a classificação do ponto
    classificao = random.choice (["bolininha", "triangulo"])
    pontos.append ((x,y,classificao))

'''
# Modificando as coordenadas do primeiro ponto
pontos[0] = (10, 5, "quadrado")
pontos = [
    (2, 8, "bolininha"),
    (5, 3, "triangulo"),
    (10, 12, "bolininha"),
    (7, 6, "triangulo"),
    (1, 11, "bolininha"),
    (9, 4, "triangulo"),
    (12, 1, "bolininha"),
    (4, 9, "triangulo"),
    (8, 7, "bolininha"),
    (3, 10, "triangulo")
]    
'''


#Imprimindo os pontos gerados
print ("Seus pontos gerados:")

for ponto in pontos:
    print (ponto)

def y1(x):
    return x

def y2(x):
    return (2/3)*x +1 

def y3(x):
    return 0.5*x +5

#Verificando se o ponto está a baixo, acima ou na reta
def classificar_pontos (y,x,funcao) :
    if y<funcao(x):
        return "bolinha" #O ponto está ABAIXO da reta = BOLINHA
    
    elif y > funcao (x):
        return "triangulo" # o ponto está ACIMA da reta = TRIÂNGULO
    
    else:
        return "bolinha" #O ponto está na EQUAÇÃO DA RETA
    

#Testando a classificação dos pontos em cada uma das 3 retas
#Iterando sobre os pontos e classificando-os
for ponto in pontos:
    x_desempacota, y_desempacota, classificao_desempacota = ponto
    classificao_reta1 = classificar_pontos (y_desempacota, x_desempacota, y1)
    classificao_reta2 = classificar_pontos (y_desempacota, x_desempacota, y1)
    classificao_reta3 = classificar_pontos (y_desempacota, x_desempacota, y1)
    print (f"Ponto ({x_desempacota},{y_desempacota}): Classificação : {classificao_reta1} (Reta 1) {classificao_reta2} (Reta 2) {classificao_reta3} (Reta 3)")

