#konstanty
NEMAME = "Takove prekladatele nemame."
MAME = "To nas bude stat xxx,-."
POCET = "Pocet prekladu: xxx."

global mozne_jazyky
global nejlepsi_cena
global nejlepsi_cesta
global preklad

#strom rekurze najit nejlepsi cestu
def algo(prekladaci,ogcesta,cesta_set,cena):
    global nejlepsi_cena
    global nejlepsi_cesta
    print(ogcesta)
    for prekladac in prekladaci:
        for jazyk in prekladac[1:]:
            if (jazyk not in cesta_set):
                cesta = list(ogcesta)
                cesta.append(jazyk)
                gcesta_set = set(cesta_set)
                gcesta_set.add(jazyk)
                cena_prekladem = cena + int(prekladac[0])
                if (nejlepsi_cena == -1 or cena_prekladem < nejlepsi_cena):
                    if (cesta[-1] == preklad[1]):
                        nejlepsi_cesta = cesta
                        nejlepsi_cena = cena_prekladem
                    else:
                        algo(mozne_jazyky[jazyk],cesta,gcesta_set,cena_prekladem)

#input
with open("input1.txt","r",encoding="utf-8") as f:
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
    preklad = input[radek + 2 + n + p]

    #mozne jazyky parse do {cj:[[5,cj,aj],[7,cj,kl]],aj:[....]
    prekladaci = input[radek+n+2:radek+n+p+2]
    prekladaci.sort(key = lambda prekladaci: int(prekladaci[1]))
    for jazyk in mozne_jazyky:
        for prekladac in prekladaci:
            if jazyk in prekladac:
                mozne_jazyky[jazyk].append(prekladac[1:])
    print(mozne_jazyky)

    #reverse
    reverse = False
    if (len(mozne_jazyky[preklad[0]]) > len(mozne_jazyky[preklad[1]])): 
        preklad.reverse()
        reverse = True

    #parsing end
    radek += 3 + n + p

    ## algoritmus
    nejlepsi_cena = -1
    nejlepsi_cesta = []
    cesta = [preklad[0]]
    cesta_set = set()
    cesta_set.add(preklad[0])
    algo(mozne_jazyky[cesta[-1]],cesta,cesta_set,0)
    if (reverse): nejlepsi_cesta.reverse()
    print("Nejlepsi cesta: ",nejlepsi_cesta,nejlepsi_cena)
    print("")

    #konec
    if (ti != 0): konecny_text = "\n"
    else: konecny_text = ""
    if (len(nejlepsi_cesta) != 0):
        konecny_text += MAME.replace("xxx",str(nejlepsi_cena))
        konecny_text += "\n" + POCET.replace("xxx",str(len(nejlepsi_cesta)-1))
        for preklad in nejlepsi_cesta:
            konecny_text += "\n" + preklad
    else:
        konecny_text += NEMAME
    
    with open("output.txt","a",encoding="utf-8",newline='\n') as f:
        f.write(konecny_text)
    