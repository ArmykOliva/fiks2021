with open("input.txt","r",encoding="utf-8") as f:
    inpt = f.read()

#parse data to ulohy {"n":n,a:[b,b,b],a:[b,b]}
radky = inpt.split("\n")
pocet_zadani = int(radky[0])
radek = 1
ulohy = []
for i in range(pocet_zadani):
    zadani_specs = radky[radek].split(" ")
    P = int(zadani_specs[1])
    n = int(zadani_specs[2])
    uloha = {}
    uloha["n"] = n
    for j in range(radek+1,radek+1+P):
        nums = radky[j].split(" ")
        a = int(nums[0])
        b = int(nums[1])
        if (a not in uloha): uloha[a] = []
        uloha[a].append(b)
    
    ulohy.append(uloha)
    radek += P+1

#get smlouvy order
vysledky = []
for x in range(len(ulohy)):
    uloha = ulohy[x]
    l1 = [uloha["n"]]
    l2 = []

    while l1 != []:
        a = l1[-1]
        if (a in uloha):
            bs = uloha[a]
            add = True
            bad_uloha = False
            for b in bs:
                if (b not in l2):
                    if (b not in l1):
                         l1.append(b)
                    else:
                        bad_uloha = True
                    add = False
                    break

            if (add):
                l2.append(a)
                l1.pop()

            if (bad_uloha):
                l1 = []
                l2 = []
                break

        else:
            l2.append(a)
            l1.pop()
        print(l1,l2)

    vysledky.append(l2)

#parse vysledky
vystup = ""
for vysledek in vysledky:
    if (vysledek != []):
        cisla = " ".join([str(elem) for elem in vysledek])
        vystup += "pujde to " + cisla + "\n"
    else:
        vystup += "ajajaj\n"

with open("output.txt","w",encoding="utf-8") as f:
    f.write(vystup)
    
print(vystup)