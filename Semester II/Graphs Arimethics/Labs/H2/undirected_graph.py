from copy import deepcopy

from exceptions import VertexError, NonexistentVertexError, EdgeError, NonexistentEdgeError


class UndirectedGraph:
    def __init__(self, vertices, edges):
        self.__vertices = []
        self.__edges = []
        self.__costs = {}
        self.__neighbours = {}

        for vertex in vertices:
            self.add_vertex(vertex)

        for edge in edges:
            self.add_edge(edge[0], edge[1], edge[2])

    """
    GETTERS
    """
    @property
    def edges(self):
        return self.__edges

    @property
    def costs(self):
        return self.__costs

    def get_number_of_vertices(self):
        return len(self.__vertices)

    def get_number_of_edges(self):
        return len(self.__edges)

    """
    ITERATORS
    """

    def parse_vertices(self):
        return [vertex for vertex in self.__vertices]

    def parse_edges(self):
        return [edge for edge in self.__edges]

    def parse_neighbours(self, x):
        return [neighbour for neighbour in self.__neighbours[x]]


    def add_vertex(self, x):
        if x in self.parse_vertices():
            raise VertexError
        self.__vertices.append(x)
        self.__neighbours[x] = []

    def add_vertex_valid(self, x):
        self.__vertices.append(x)
        self.__neighbours[x] = []

    def remove_vertex(self, x):
        if x not in self.parse_vertices():
            raise NonexistentVertexError

        for edge in self.parse_edges():
            if edge[0] == x or edge[1] == x:
                self.remove_edge(edge[0], edge[1])
        del self.__neighbours[x]
        self.__vertices.remove(x)

    def add_edge(self, x, y, c):
        if x not in self.parse_vertices():
            raise NonexistentVertexError
        if y not in self.parse_vertices():
            raise NonexistentVertexError

        if y < x:
            x, y = y, x
        if (x, y) in self.parse_edges():
            raise EdgeError

        self.__edges.append((x, y))
        self.__neighbours[x].append(y)
        self.__neighbours[y].append(x)
        self.__costs[(x, y)] = c

    def add_edge_valid(self, x, y, c):
        if y < x:
            x, y = y, x
        self.__edges.append((x, y))
        self.__neighbours[x].append(y)
        self.__neighbours[y].append(x)
        self.__costs[(x, y)] = c

    def remove_edge(self, x, y):
        if x not in self.parse_vertices():
            raise NonexistentVertexError
        if y not in self.parse_vertices():
            raise NonexistentVertexError

        if y < x:
            x, y = y, x
        if (x, y) not in self.parse_edges():
            raise NonexistentEdgeError

        self.__edges.remove((x, y))
        del self.__costs[(x, y)]
        self.__neighbours[x].remove(y)
        self.__neighbours[y].remove(x)

    def update_edge(self, x, y, new_cost):
        if x not in self.parse_vertices():
            raise NonexistentVertexError
        if y not in self.parse_vertices():
            raise NonexistentVertexError

        if y < x:
            x, y = y, x
        if (x, y) not in self.parse_edges():
            raise NonexistentEdgeError

        self.__costs[(x, y)] = new_cost

    def is_edge(self, x, y):
        if x not in self.parse_vertices():
            raise NonexistentVertexError
        if y not in self.parse_vertices():
            raise NonexistentVertexError

        if y in self.__neighbours[x] and x in self.__neighbours[y]:
            return True
        return False

    def degree(self, x):
        if x not in self.parse_vertices():
            raise NonexistentVertexError

        return len(self.__neighbours[x])

    def copy(self):
        """
        Returns a deepcopy of the graph.
        Runtime: O(1)
        :return: UndirectedGraph object
        """
        return deepcopy(self)