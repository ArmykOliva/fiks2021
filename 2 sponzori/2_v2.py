#Kryštof Olík 2021
#python 3.8.3 and greater

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

#sort the dictionary by the number of zvirata for better average speed
#uspořádat sponzori vzestupně dle počtu možných zvířat pro lepší průměrnou rychlost
sponzori = dict(sorted(sponzori.items(), key=lambda item: len(item[1]))) #O(n log n)

#global variables for the algorithm
vysledek = {} #vysledek = {zvire:sponzor,zvire:sponzor...}
recursion_done = set() #na zaznamenani co uz bylo v recursion

def algo(sponzor, in_recursion = False):
    global vysledek
    global recursion_done

    zvirata = sponzori[sponzor]

    #iteruje přes zvířata, pokud najde zvíře, které není ve výsledcích, přidá ho tam a return True
    for zvire in zvirata:
        if (zvire not in vysledek):
            vysledek[zvire] = sponzor
            return True

    #
    for zvire in zvirata:
        search_sponzor = vysledek[zvire]
        if (search_sponzor == sponzor or search_sponzor in recursion_done): continue
        recursion_done.add(search_sponzor) #

        print("recursion",sponzor,search_sponzor)
        worked = algo(search_sponzor,True)
        if (worked):
            print("povedlo se",sponzor,search_sponzor)
            vysledek[zvire] = sponzor
            return True
    
    return False

#run it
for sponzor in sponzori:
    recursion_done = set()
    algo(sponzor)

print(len(vysledek) == len(zvirata))
print(vysledek)
print(len(vysledek))