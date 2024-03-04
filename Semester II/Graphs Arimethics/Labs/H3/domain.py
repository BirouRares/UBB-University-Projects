


class GraphException(Exception):
    def __init__(self, msg):
        self._msg = msg

    def __str__(self):
        return str(self._msg)


class Graph:

    def __init__(self):
        self._vertices = []
        self._edges = 0

    def initialize_edges(self, number_of_edges): #this function initializes the number of edges
        self._edges = number_of_edges

    def initialize_vertices(self, number_of_vertices):#this function initializes the number of vertices

        if(len(self._vertices)) != 0:#if the list of vertices is not empty, it clears it
            self._vertices.clear()
        for index in range(0, number_of_vertices):#it adds the vertices to the list
            self._vertices.append(index)




    def add_vertex(self, new_vertex):# this function adds a new vertex to the list of vertices
        if new_vertex not in self._vertices:# if the vertex is not in the list, it adds it
            self._vertices.append(new_vertex)
        else:# if the vertex is in the list, it raises an exception
            raise GraphException('The given vertex already exists!!!')

    def remove_vertex(self, vertex):# this function removes a vertex from the list of vertices
        if self.check_existence_of_vertex(vertex):# if the vertex is in the list, it removes it
            self._vertices.remove(vertex)
        else:# if the vertex is not in the list, it raises an exception
            raise GraphException('The given vertex does not exist!!!')

    @property
    def edges(self):# this function returns the number of edges
        return self._edges

    @edges.setter
    def edges(self, new_value):# this function sets the number of edges
        self._edges = new_value

    @property
    def vertices(self):# this function returns the list of vertices
        return self._vertices

    def parse_vertices(self):# this function parses the list of vertices
        for vertex in self._vertices:
            yield vertex

    def check_existence_of_vertex(self, check_vertex):# this function checks if a vertex is in the list of vertices
        vertices = self.parse_vertices()
        for vertex in vertices:
            if vertex == check_vertex:
                return True
        return False

    def __len__(self):# this function returns the length of the list of vertices
        return len(self._vertices)

    def get_nr_of_vertices(self):# this function returns the length of the list of vertices
        return len(self._vertices)

    def find_vertex(self, vertex):# this function checks if a vertex is in the list of vertices
        if vertex in self._vertices:
            return True
        return False

