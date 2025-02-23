import queue
from random import randrange

from exceptions import InvalidEdges
from undirected_graph import UndirectedGraph


def generate_random_graph(n, m, file_path): # n = number of vertices, m = number of edges
    # this function generates a random graph with n vertices and m edges
    if m > n ** 2 / 2:
        raise InvalidEdges

    vertices = []
    for i in range(n):
        vertices.append(str(i))

    edges = []
    while len(edges) < m:
        x = str(randrange(n))
        y = str(randrange(n))
        if x < y:
            x, y = y, x
        cost = randrange(-1000, 1000)

        ok = 1
        for edge in edges:
            if edge[0] == x and edge[1] == y:
                ok *= -1

        if ok == 1:
            edges.append((x, y, cost))

    G = UndirectedGraph(vertices, edges)

    with open(file_path, "w") as f:
        f.write(str(G.get_number_of_vertices()) + " ")
        f.write(str(G.get_number_of_edges()) + "\n")

        for edge in G.parse_edges():
            f.write(f"{edge[0]} {edge[1]} {G.costs[(edge[0], edge[1])]}\n")


def read_graph(file_path):
    """
    Function that reads a graph from a text file with the path file_path.
    :param file_path: the path of the file from which the graph will be read
    :return: DirectedGraph object
    """
    vertices = []
    edges = []

    G = UndirectedGraph(vertices, edges)

    with open(file_path) as f:
        line = f.readline()
        line = line.strip(" \n")
        n = int(line.split(" ")[0])

        for i in range(n):
            G.add_vertex_valid(str(i))

        for line in f.readlines():
            line = line.strip(" \n")
            x = line.split(" ")[0]
            y = line.split(" ")[1]
            c = int(line.split(" ")[2])

            G.add_edge_valid(x, y, c)
    return G


def print_graph(G, option): # function that prints the undirectedgraph object G
    if not option:
        print(str(G.get_number_of_vertices()) + " " + str(G.get_number_of_edges()))

        for edge in G.parse_edges():
            print(f"{edge[0]} {edge[1]} {G.costs[(edge[0], edge[1])]}")
    else:
        with open("graph_modif.txt", "w") as f:
            f.write(str(G.get_number_of_vertices()) + " ")
            f.write(str(G.get_number_of_edges()) + "\n")

            for edge in G.parse_edges():
                f.write(f"{edge[0]} {edge[1]} {G.costs[(edge[0], edge[1])]}\n")


def bfs(G, s, visited): # function that executes a BFS traversal of the undirected graph G
    vertices = []
    edges = []
    q = queue.Queue()

    q.put(s)
    visited[s] = True
    vertices.append(s)
    while not q.empty():
        first = q.get()
        for neighbour in G.parse_neighbours(first):
            if not neighbour in visited.keys():
                visited[neighbour] = True
                q.put(neighbour)

                if G.is_edge(neighbour, neighbour):
                    edges.append((neighbour, neighbour, G.costs[(neighbour, neighbour)]))
                for vertex in vertices:
                    if vertex < neighbour:
                        x, y = vertex, neighbour
                    else:
                        y, x = vertex, neighbour
                    if G.is_edge(x, y) and ((x, y, G.costs[(x, y)]) not in edges):
                        edges.append((x, y, G.costs[(x, y)]))
                vertices.append(neighbour)
    return UndirectedGraph(vertices, edges)


def bfs_connected_components(G): # function that returns a list of the connected components of an undirected graph as UndirectedGraph objects
    visited = {}# dictionary that stores the visited vertices
    connected_components = []# list that stores the connected components of the graph

    for vertex in G.parse_vertices():# for each vertex in the graph
        if not vertex in visited.keys(): # if the vertex is not visited
            connected_component = bfs(G, vertex, visited)# execute a BFS traversal of the graph starting from the vertex
            connected_components.append(connected_component)# add the connected component to the list of connected components

    return connected_components # function that returns a list of the connected components of an undirected graph as UndirectedGraph objects