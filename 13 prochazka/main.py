#input
from tracemalloc import start


with open("input.txt","r",encoding="utf-8") as f:
    input = f.read().splitlines()
    input = [input.split(" ") for input in input]
with open("output.txt","w",encoding="utf-8") as f:
    f.write("")

t = int(input[0][0])
radek = 1
for zadani in range(t):
    krizovatky = {}
    krizovatky_length = input[radek][0]
    for i in range(int(input[radek][1])):
        radek += 1

        kr1 = int(input[radek][0])
        kr2 = int(input[radek][1])
        if (kr1 not in krizovatky): krizovatky[kr1] = []
        if (kr2 not in krizovatky): krizovatky[kr2] = []

        if (kr1 != kr2):
            krizovatky[kr1].append((kr1,kr2))
            krizovatky[kr2].append((kr1,kr2))

   # print(krizovatky)
    startovni_pozice = 0
    nejmin = 99999999
    for key in krizovatky.keys():
        if (len(krizovatky[key]) < nejmin):
            nejmin = len(krizovatky[key])
            startovni_pozice = key
            
            
    momm = startovni_pozice # momentalni pozice 
    vytvorit_cesty = [] #cesty, ktery se musi vytvorit navic
    navstivene_krizovatky = set()
    while len(krizovatky) > 0:
        #pokud slepa ulicka: musi se vytvorit cesta navic, cesta povede do krizovatky s nejvic cestama, ktera jeste nebyla zvolena
        if (momm not in krizovatky):
            nejmin = 9999999999
            target = None
            for key in krizovatky.keys():
                if (len(krizovatky[key]) < nejmin and key not in navstivene_krizovatky):
                    nejmin = len(krizovatky[key])
                    target = key
            nejmin = 99999999
            if (target == None):
                for key in krizovatky.keys():
                    if (len(krizovatky[key]) < nejmin):
                        nejmin = len(krizovatky[key])
                        target = key
            vytvorit_cesty.append((momm,target))
            if (momm not in navstivene_krizovatky): navstivene_krizovatky.add(momm)
            if (target not in navstivene_krizovatky): navstivene_krizovatky.add(target)
            momm = target
        else:
            #najit cestu a target pozici
            targetr = krizovatky[momm][0]
            if (targetr[0] != momm): target = targetr[0]
            else: target = targetr[1]
           # print(target)

            #remove target
            krizovatky[momm].pop(0)
            if (len(krizovatky[momm]) == 0): krizovatky.pop(momm)
            krizovatky[target].remove(targetr)
            if (len(krizovatky[target]) == 0): krizovatky.pop(target)
            if (momm not in navstivene_krizovatky): navstivene_krizovatky.add(momm)
            if (target not in navstivene_krizovatky): navstivene_krizovatky.add(target)
            momm = target
        #print(krizovatky)

    #nakonec se vratit do startu
    if (momm != startovni_pozice):
        vytvorit_cesty.append((momm,startovni_pozice))
        
    radek += 1 

    #napsat vysledek
    with open("output.txt","a",encoding="utf-8",newline='\n') as f:
        if (len(vytvorit_cesty) == 0): f.write("Ano.\n")
        else:
            f.write("Ne.\n%s\n" % len(vytvorit_cesty))
            for cesta in vytvorit_cesty:
                ss = "{} {}\n".format(cesta[0],cesta[1])
                f.write(ss)

    