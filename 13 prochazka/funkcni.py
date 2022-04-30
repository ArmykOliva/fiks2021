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
        if (kr1 not in krizovatky): krizovatky[kr1] = {"leng":0}
        if (kr2 not in krizovatky): krizovatky[kr2] = {"leng":0}

        if (kr1 != kr2):
            krizovatky[kr1]["leng"] += 1
            krizovatky[kr2]["leng"] += 1
            if (kr2 not in krizovatky[kr1]): krizovatky[kr1][kr2] = 0
            if (kr1 not in krizovatky[kr2]): krizovatky[kr2][kr1] = 0
            krizovatky[kr1][kr2] += 1
            krizovatky[kr2][kr1] += 1

    #dat odd krizovatkam path
    vytvorit_cesty = []
    neprirazene = []
    for key in krizovatky:
        krizovatka = krizovatky[key]
        if (krizovatka["leng"] % 2 == 1):
            nasel = False
            for kkey in krizovatka:
                if (kkey != "leng"):
                    if (krizovatky[kkey]["leng"] % 2 == 1):
                        vytvorit_cesty.append((kkey,key))
                        krizovatky[key][kkey] += 1
                        krizovatky[kkey][key] += 1
                        krizovatky[key]["leng"] += 1
                        krizovatky[kkey]["leng"] += 1
                        nasel = True
                        break

            if (not nasel): neprirazene.append(key)

                    
    for i in range(len(neprirazene)):
        if (i % 2 == 0):
            vytvorit_cesty.append((neprirazene[i],neprirazene[i+1]))
    
    print("nig",vytvorit_cesty,len(vytvorit_cesty))
    radek += 1 

    #napsat vysledek
    with open("output.txt","a",encoding="utf-8",newline='\n') as f:
        if (len(vytvorit_cesty) == 0): f.write("Ano.\n")
        else:
            f.write("Ne.\n%s\n" % len(vytvorit_cesty))
            for cesta in vytvorit_cesty:
                ss = "{} {}\n".format(cesta[0],cesta[1])
                f.write(ss)

    