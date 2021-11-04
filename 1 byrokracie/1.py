with open("input.txt","r",encoding="utf-8") as f:
    inpt = f.read()

#parse data to ulohy [n,[a,b],[a,b]..]
radky = inpt.split("\n")
pocet_zadani = int(radky[0])
radek = 1
ulohy = []
for i in range(pocet_zadani):
    zadani_specs = radky[radek].split(" ")
    P = int(zadani_specs[1])
    n = int(zadani_specs[2])
    uloha = [n]
    for j in range(radek+1,radek+1+P):
        nums = radky[j].split(" ")
        a = int(nums[0])
        b = int(nums[1])
        uloha.append([a,b])
    
    ulohy.append(uloha)
    radek += P+1

#get smlouvy order
vysledky = []
for x in range(len(ulohy)):
    uloha = ulohy[x]
    l1 = [uloha[0]]
    l2 = []

    if (len(uloha) == 1): vysledky.append([uloha[0]])

    i = 1
    while i < len(uloha):
        finding = l1[-1]
        line = uloha[i]
        a = line[0]
        b = line[1]
     
        #narazil na podminku
        if a == finding and b not in l2:
            if (b in l1):
                vysledky.append([])
                break
            else:
                l1.append(b)
                i = 1
                continue

        i += 1
        #dojel do konce
        if (i >= len(uloha)):
            print("uloha %s" % x,l1,l2)
            l2.append(finding)
            l1.pop()
            i = 1
            if l1 == []:
                vysledky.append(l2)
                break

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