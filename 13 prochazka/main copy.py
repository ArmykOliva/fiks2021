#input
from tracemalloc import start
from collections import defaultdict

class Solution:
        
        # Function to find smallest set
        # of vertices from which the
        # complete graph can be visited
        def solve(self , edges):

            graph = defaultdict(list)

            # dictionary storing
            # indgree of nodes
            indeg = defaultdict(int)

            for (u,v) in edges:
                graph[u].append(v)

                # count indegree of
                # each node
                indeg[v] +=1

            ans = []
            for u in graph:
                
                # add to ans, if indegree
                # of node u is 0
                if(indeg[u] == 0):
                    ans.append(u)

            # Return Ans
            return (ans)

with open("input1.txt","r",encoding="utf-8") as f:
    input = f.read().splitlines()
    input = [input.split(" ") for input in input]
with open("output.txt","w",encoding="utf-8") as f:
    f.write("")

t = int(input[0][0])
radek = 1
for zadani in range(t):
    krizovatky = {}
    for i in range(int(input[radek][1])):
        radek += 1

        kr1 = int(input[radek][0])
        kr2 = int(input[radek][1])
        if (kr1 not in krizovatky): krizovatky[kr1] = []
        if (kr2 not in krizovatky): krizovatky[kr2] = []

        if (kr1 != kr2):
            krizovatky[kr1].append((kr1,kr2))
            krizovatky[kr2].append((kr1,kr2))

   # print(krizovatky)# Python program of the above approach
    

    
                

    obj = Solution()
    edges = [[0,1] , [2,1] , [3,2] , [4,3] ]

    vytvorit_cesty= obj.solve(edges)
    print(vytvorit_cesty)
 

    #napsat vysledek
    with open("output.txt","a",encoding="utf-8",newline='\n') as f:
        if (len(vytvorit_cesty) == 0): f.write("Ano.\n")
        else:
            f.write("Ne.\n%s\n" % len(vytvorit_cesty))
            for cesta in vytvorit_cesty:
                ss = "{} {}\n".format(cesta[0],cesta[1])
                f.write(ss)

    radek += 1