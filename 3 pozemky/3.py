with open("input.txt","r",encoding="utf-8") as f:
    input = f.read().splitlines()
    input = [input.split(" ") for input in input]
T = int(input[0][0])
r = 1
vysledek = []
for i in range(T):
    N = int(input[r][0])
    num = 0
    for j in range(r+1,N+r+1):
        plus = int(input[j][1]) * int(input[j][2])
        num += plus
        r += 1
    vysledek.append(num)
    r+= 1
with open("output.txt","w",encoding="utf-8") as f:
    for v in vysledek:
        f.write(str(v) + "\n")