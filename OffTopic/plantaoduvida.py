list = []

algoritmos = []
praticas = []
desempenho = []
fluxogramas = []
enunciados = []
linguagem = []

testes = int(input())
while True:
    try:
        list.append(input().split())
    except EOFError:
        for x in range(len(list)):
            for y in range(len(list[x][y])):
                nome = list[x][0]
                if (y==0): continue
                if (y==1): algoritmos.append(nome)
                elif (y==2): praticas.append(nome)
                elif (y==3): desempenho.append(nome)
                elif (y==4): fluxogramas.append(nome)
                elif (y==5): enunciados.append(nome)
                elif (y==6): linguagem.append(nome)        
                
        print("------------------------------")
        print("ALGORITMOS")
        print(algoritmos)
        print("------------------------------")
        print("------------------------------")
        print("BOAS PRATICAS")
        print(praticas)
        print("------------------------------")
        print("------------------------------")
        print("DESEMPENHO")
        print(desempenho)
        print("------------------------------")
        print("------------------------------")
        print("FLUXOGRAMAS")
        print(fluxogramas)
        print("------------------------------")
        print("------------------------------")
        print("INTERPRETACAO DE ENUNCIADOS")
        print(enunciados)
        print("------------------------------")
        print("------------------------------")
        print("SINTAXE DE LINGUAGEM")
        print(linguagem)
        print("------------------------------")
        break