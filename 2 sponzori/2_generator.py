import random
N = int(input("animals "))
Z = int(input("Sponsors "))

alphabet = "abcdefghijklmnopqrstuvwxyz123456789,./;'[]"
v = "{} {}".format(N,Z)

for i in range(N):
    v += "\n{} {}".format(i,i)
    
for i in range(Z):
    animals = random.randint(1,5)
    v += "\n{} {}".format(i, animals)
    for x in range(animals):
        v += " %s" % random.randint(0,N-1)

with open("input.txt","w",encoding="utf-8") as f:
    f.write(v)