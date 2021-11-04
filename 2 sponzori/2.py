#Kryštof Olík 2021
#python 3.8.3 and greater

## parsing
with open("input.txt","r",encoding="utf-8") as f:
    input = f.read().splitlines()
    input = [input.split(" ") for input in input]

#get first values
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
sponzori = dict(sorted(sponzori.items(), key=lambda item: len(item[1]))) #O(n log n)

#vysledek = {zvire:sponzor,zvire:sponzor...}
vysledek = {}

#the algorithm returns true if found place without having to go back
def algo(sponzor,recursion=True):
    global vysledek
    global pro_vsechny_sponzor

    zvirata = sponzori[sponzor]

    for zvire in zvirata:
        if (zvire not in vysledek):
            vysledek[zvire] = sponzor
            return True

    if (recursion):
        for zvire in zvirata:
            print("recursion",sponzor,vysledek[zvire])
            worked = algo(vysledek[zvire],False)
            if (worked):
                print("povedlo se",sponzor,vysledek[zvire])
                vysledek[zvire] = sponzor
                return True

    return False

#run it
for sponzor in sponzori:
    algo(sponzor)

    
print(len(vysledek) == len(zvirata))
print(vysledek)
print(len(vysledek))