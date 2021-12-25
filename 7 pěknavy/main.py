import sys
from time import time
from Levenshtein import distance

def getbin(s):
    binary=""
    iters = [s[i:i+1] for i in range(len(s))]
    for x in iters:
        srong = bin(int.from_bytes(x, byteorder=sys.byteorder))[2:]
        while len(srong) != 8:
            srong = "0" + srong
        binary += srong 
    return binary

def translate(s,n): 
    translation = ""
    baze = {"00":"A","01":"C","10":"G","11":"T"}
    i = 0 
    while i < len(s)-1:
        srong = s[i:i+2]
        translation += baze[srong]
        i += 2
    return translation[:n]

def find_space(b):
    iters = [b[i:i+1] for i in range(len(b))]
    i = 0
    for it in iters:
        i += 1
        if it == b" ":
            return i
    return 0

def levenshtein(s1, s2,maximum):
    if (abs(len(s1)-len(s2)) > maximum): return False

    return distance(s1,s2) <= maximum


def editDistDP(str1, str2):
    m = len(str1)
    n = len(str2)
    # Create a table to store results of subproblems
    dp = [[0 for x in range(n + 1)] for x in range(m + 1)]
  
    # Fill d[][] in bottom up manner
    for i in range(m + 1):
        for j in range(n + 1):
  
            # If first string is empty, only option is to
            # insert all characters of second string
            if i == 0:
                dp[i][j] = j    # Min. operations = j
  
            # If second string is empty, only option is to
            # remove all characters of second string
            elif j == 0:
                dp[i][j] = i    # Min. operations = i
  
            # If last characters are same, ignore last char
            # and recur for remaining string
            elif str1[i-1] == str2[j-1]:
                dp[i][j] = dp[i-1][j-1]
  
            # If last character are different, consider all
            # possibilities and find minimum
            else:
                dp[i][j] = 1 + min(dp[i][j-1],        # Insert
                                   dp[i-1][j],        # Remove
                                   dp[i-1][j-1])    # Replace
  
    return dp[m][n]

"""
import random
s1 = ""
s2 = ""
for i in range(0,2000):
    s1 += str(random.randint(0,9))
    s2 += str(random.randint(0,9))

tim = time()
print(distance(s1,s2),time()-tim)"""
    
tim = time()
#open file
with open("input1.txt","rb") as f:
    input = f.read().split(b"\n")

#parse
ulohy = [] 
T = int(input[0])
line_num = 1
for i in range(T):
    gg = input[line_num].decode("utf-8")
    gg = gg.split(" ")
    N = int(gg[0])
    K = int(gg[1])
    penkavy = [K]
    for j in range(N):
        line_num += 1
        Li = int(input[line_num][0:find_space(input[line_num])])
        byts = getbin(input[line_num][find_space(input[line_num]):])
        while len(translate(byts,Li)) < Li:
            line_num += 1
            byts += getbin(b"\n") + getbin(input[line_num])

        penkavy.append(translate(byts,Li))
    line_num += 1
    #print(penkavy)
    ulohy.append(penkavy)

print("parsing trval: ",time()-tim)

#remove file
with open("output.txt","w",encoding="utf-8",newline="\n") as f:
    f.write("")

#penkavy algorithm distance dp https://www.geeksforgeeks.org/edit-distance-dp-5/
for ulohanum,uloha in enumerate(ulohy):
    tim = time()
    vysledky = set()
    pary = set()
    notpary = set()
    K = uloha[0]
    for i,dna in enumerate(uloha[1:]):
        for j,dna2 in enumerate(uloha[1:]):
            if (i != j):
                if ((i,j) in pary or levenshtein(dna,dna2,K)):
                    pary.add((i,j))
                    for l,dna3 in enumerate(uloha[1:]):
                        if (i > l): continue
                        if (l != j and l != i):
                            leven1 = (j,l) in pary or levenshtein(dna2,dna3,K)
                            leven2 = (i,l) in notpary or not levenshtein(dna,dna3,K)
                            if (leven1 and leven2):
                                vysledek = (i,j,l)
                                print(vysledek)
                                vysledky.add(vysledek)
                                if ((j,l) not in pary): pary.add((j,l))
                                if ((i,l) not in notpary): notpary.add((i,l))
            
    print("uloha",ulohanum+1,"trvala",time()-tim)

    #save vysledky
    with open("output.txt","a",encoding="utf-8",newline="\n") as f:
        f.write(str(len(vysledky))+"\n")
        for vysledek in vysledky:
            f.write("{} {} {}\n".format(vysledek[0],vysledek[1],vysledek[2]))

