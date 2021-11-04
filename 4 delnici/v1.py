#konstanty
NEMAME = "Takove prekladatele nemame."

#strom iterace


#input
with open("input.txt","r",encoding="utf-8") as f:
    input = f.read().splitlines()
    input = [input.split(" ") for input in input]
with open("output.txt","w",encoding="utf-8") as f:
    f.write("")

t = int(input[0][0])
radek = 1
for ti in range(t):
    ## parsing
    #zjisteni vsech jazyku, ktere prekladaci umi
    n = int(input[radek][0])
    mozne_jazyky = {}
    for ni in range(n):
        mozne_jazyky[input[radek+ni+1][0]] = []
    #zjistit jaky preklad je potreba
    p = int(input[radek+n+1][0])
    preklad = tuple(input[radek + 2 + n + p])
    #mozne jazyky parse do {cj:[[5,cj,aj],[7,cj,kl]],aj:[....]
    prekladaci = input[radek+n+2:radek+n+p+2]
    prekladaci.sort(key = lambda prekladaci: int(prekladaci[1]))
    for jazyk in mozne_jazyky:
        for prekladac in prekladaci:
            if jazyk in prekladac:
                mozne_jazyky[jazyk].append(prekladac[1:])
    #parsing end
    radek += 3 + n + p
    print(mozne_jazyky)
    print(preklad)

    ## algoritmus
    #iterativne najit nejlevnejsi cestu, zkousenim ruznych cest
    master = [set(preklad[0])]
    cesta = [preklad[0]]
    nejlepsi_cesta = []
    jazyk_prekladaci = mozne_jazyky[cesta[-1]]
    cena = 0
    nejlepsi_cena = -1
    last_i = []
    i = 0
    while i < len(jazyk_prekladaci): #['4', 'Cestina', 'Spanelstina']
        last_i.insert(len(cesta)-1,i) 
        print(last_i)
        jazyk_prekladaci = mozne_jazyky[cesta[-1]]
        jazyk_prekladac = jazyk_prekladaci[i]
        cena_prekladace = int(jazyk_prekladac[0])
        if (cena + cena_prekladace < nejlepsi_cena or nejlepsi_cena == -1):
            for jazyk in jazyk_prekladac[1:]: #'Cestina'
                if (jazyk == preklad[1]):
                    cesta.append(jazyk)
                    cena += cena_prekladace
                    nejlepsi_cena = cena
                    nejlepsi_cesta = cesta
                    print("mozna cesta:",cesta,cena)

                    #kroky zpet dokud nenajdeme jazyk, u ktereho jsme jeste nezkouseli vsechny cesty
                    cesta = cesta[:-1]
                    l = 0
                    x = last_i[i-l]
                    cena -= int(mozne_jazyky[cesta[-1]][x][0])
                    print(cena+int(mozne_jazyky[cesta[-1]][x][0])," - ",int(mozne_jazyky[cesta[-1]][x][0]),"=",cena)
                    #print(cesta,x,l,cena,int(mozne_jazyky[cesta[-1]][x][0]))
                    while x >= len(mozne_jazyky[cesta[-1]])-1:
                        cesta = cesta[:-1]
                        x = last_i[i-l]
                        cena -= int(mozne_jazyky[cesta[-1]][x-1][0])
                        print(cena+int(mozne_jazyky[cesta[-1]][x-1][0])," - ",int(mozne_jazyky[cesta[-1]][x-1][0]),"=",cena)
                        l += 1
                    i = x-1
                    last_i = last_i[:-l]
                    break
                elif (jazyk != cesta[-1] and jazyk not in cesta):
                    cesta.append(jazyk)
                    cena += cena_prekladace
                    i = -1
                    break
        i += 1
    print("nejlepsi cesta: ",nejlepsi_cesta,nejlepsi_cena)
    break