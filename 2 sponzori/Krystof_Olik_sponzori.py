#Kryštof Olík 2021
#python 3.8.3 and greater
import sys
sys.setrecursionlimit(5000) #aby mohla rekurzivní funkce běžet hlouběji

## parsing
with open("input.txt","r",encoding="utf-8") as f:
    input = f.read().splitlines()
    input = [input.split(" ") for input in input]

#dostat základní proměnné
N = int(input[0][0]) #zvire count int=O(n)
Z = int(input[0][1]) #sponzor count int=O(n)

#parse zvirata to dict {zvire_id:zvire_name,zvire_id:zvire_name}
zvirata = {}
for i in range(1,N+1):
    zvire = input[i]
    zvirata[zvire[0]] = zvire[1]

#parse sponzor to dict {sponzor:[zvire,zvire,zvire],sponzor:[zvire]...}
sponzori = {}
for i in range(N+1,N+Z+1):
    sponzor = input[i]
    if (sponzor[0] not in sponzori): sponzori[sponzor[0]] = []
    for zvire_id in sponzor[2:]: 
        zvire = zvirata[zvire_id]
        sponzori[sponzor[0]].append(zvire)

#globální proměnné pro algoritmus
vysledek = {} #vysledek = {zvire:sponzor,zvire:sponzor...}
recursion_done = set() #zaznamenání jací sponzoři už byli v rekurzi

#sponzor = jmeno sponzora, in_recursion = zda je v rekurzi
def algo(sponzor, in_recursion = False):
    global vysledek
    global recursion_done

    zvirata = sponzori[sponzor] #všechna možná zvířata na sponzorování

    #iteruje přes zvířata, pokud najde zvíře, které není ve výsledcích, přidá ho do vysledek a return True
    for zvire in zvirata:
        if (zvire not in vysledek):
            vysledek[zvire] = sponzor
            return True

    #pokud není možné přiřadit zvíře, pokusit se vrátit k jiným sponzorům, kteří už tato zvířata sponzorují, a pokusit se pro ně najít jiné nezabrané zvíře
    for zvire in zvirata:
        hledany_sponzor = vysledek[zvire]
        if (hledany_sponzor == sponzor or hledany_sponzor in recursion_done): continue #pokud se tento sponzor už hledal, neiterovat přes něj
        recursion_done.add(hledany_sponzor)

        #rekurzivně se vrátit na hledaného sponzora, pokud se změna povedla return True pokud ne return False
        worked = algo(hledany_sponzor,True)
        if (worked):
            vysledek[zvire] = sponzor
            return True

    return False

#iterovat každého 
vystup = "Ne"
for sponzor in sponzori:
    recursion_done = set()
    algo(sponzor)
    if (len(vysledek) == len(zvirata)):
        vystup = "Ano"
        break

#parse to výstup
for zvire in sorted(vysledek):
    vystup += "\n{} {}".format(zvire,vysledek[zvire])

with open("output.txt","w",encoding="utf-8") as f:
    f.write(vystup)