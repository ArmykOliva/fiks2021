N = 1000
Z = 1000
c = 0

def algo():
    global c

    for i in range(N):
        c += 1

    for i in range(N):
        c += 1
        algo()

for i in range(Z):
    c += 1
    algo()

print(c)