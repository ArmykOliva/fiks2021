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
    posledni_cesticka = (None,None)
    while len(krizovatky) > 0:
        #setup vars
        nejmin = 99999999
        target = None
        cesta_target = None

        secondary_nejmin = 99999999
        target_secondary = None
        secondary_cesta_target = None

        #pokud slepa ulicka: musi se vytvorit cesta navic, cesta povede do krizovatky s nejvic cestama, ktera jeste nebyla zvolena
        if (momm not in krizovatky):
            for key in krizovatky:
                krizovatka = krizovatky[key]
                length = len(krizovatka)
                if (length < nejmin and posledni_cesticka not in krizovatka):
                    target = key
                    nejmin = length

                if (length < secondary_nejmin):
                    target_secondary = key
                    secondary_nejmin = length

            #select the right target
            if (target == None):
                target = target_secondary
            
            vytvorit_cesty.append((momm,target))
            print("vytvorit",(momm,target))
            momm = target
        else:
            #najit cestu a target pozici
            for cesta in krizovatky[momm]:
                key = cesta[0] if cesta[0] != momm else cesta[1]
                length = len(krizovatky[key])
                if (length < nejmin and length > 1):
                    target = key
                    cesta_target = cesta
                    nejmin = length

                if (length < secondary_nejmin):
                    #if (target_secondary == startovni_pozice and secondary_nejmin == 1) or (target_secondary != startovni_pozice):
                    if (cesta != posledni_cesticka):
                        target_secondary = key
                        secondary_cesta_target = cesta
                        secondary_nejmin = length
                    
            #select the right target
            if (target == None):
                target = target_secondary
                cesta_target = secondary_cesta_target

            #pokud opravdu nenaslo nic, jit pres posledni cesticku
            if (target == None):
                if (len(krizovatky) == 2):
                    cesta_target = posledni_cesticka
                    target = posledni_cesticka[0] if posledni_cesticka[0] != momm else posledni_cesticka[1]
                    

            #remove target
            if (target != None):
                krizovatky[momm].remove(cesta_target)
                if (len(krizovatky[momm]) == 0): krizovatky.pop(momm)
                krizovatky[target].remove(cesta_target)
                if (len(krizovatky[target]) == 0): krizovatky.pop(target)
            momm = target

        if (startovni_pozice in krizovatky and len(krizovatky[startovni_pozice]) == 1): posledni_cesticka = krizovatky[startovni_pozice][0]
            

    #nakonec se vratit do startu
    #if (momm != startovni_pozice):
    #    vytvorit_cesty.append((momm,startovni_pozice))
        
    radek += 1 

    #napsat vysledek
    with open("output.txt","a",encoding="utf-8",newline='\n') as f:
        if (len(vytvorit_cesty) == 0): f.write("Ano.\n")
        else:
            f.write("Ne.\n%s\n" % len(vytvorit_cesty))
            for cesta in vytvorit_cesty:
                ss = "{} {}\n".format(cesta[0],cesta[1])
                f.write(ss)

    