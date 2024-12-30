from random import random
from itertools import product, combinations

def random_graph(n, p, *, directed=False):
    nodes = range(n)
    adj_list = [[] for i in nodes]
    possible_edges = product(nodes, repeat=2) if directed else combinations(nodes, 2)
    for u, v in possible_edges:
        if random() < p:
            adj_list[u].append(v)
            if not directed:
                adj_list[v].append(u)
                
    f = open("testGraph6.txt", "w")
    
    f.write(str(n) + "\n")
    
    i = 0;
    for vertexList in adj_list:
        f.write(str(i) + " ")
        for vertex in vertexList:
            f.write(str(vertex) + " ")
        f.write("\n")
        i = i + 1;
            
    f.close()
    
    return adj_list
    
random_graph(500, 0.1)