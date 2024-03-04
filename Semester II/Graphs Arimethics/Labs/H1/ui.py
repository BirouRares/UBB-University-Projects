from graph import *

class UI:
    def __init__(self, type_of_graph):
        self.type_of_graph = type_of_graph
        self.graph = None

    def empty_graph(self):
        try:
            self.graph = self.type_of_graph()
            print("Done!")
        except Exception as e:
            print(e)
            print("\n")

    def n_graph(self):
        n = input("How many vertices do you need: ")
        try:
            self.graph = self.type_of_graph(int(n))
            print("Done!")
        except Exception as e:
            print(e)
            print("\n")

    def m_graph(self):
        n = input("How many vertices do you need: ")
        m = input("How many edges do you need: ")
        try:
            self.graph = self.type_of_graph(int(n), int(m))
            print("Done!")
        except Exception as e:
            print(e)
            print("\n")

    def add_vertex(self):
        n = input("Type the vertex you wish to add: ")
        try:
            self.graph.add_vertex(int(n))
        except Exception as e:
            print(e)
            print("\n")

    def add_edge(self):
        v1 = input("Type the first vertex of the edge: ")
        v2 = input("Type the second vertex of the edge: ")
        c = input("Type the cost of the edge: ")
        try:
            self.graph.add_edge(int(v1), int(v2), int(c))
        except Exception as e:
            print(e)
            print("\n")

    def rem_vertex(self):
        n = input("Type the vertex you wish to remove: ")
        try:
            self.graph.remove_vertex(int(n))
        except Exception as e:
            print(e)
            print("\n")

    def rem_edge(self):
        v1 = input("Type the first vertex of the edge: ")
        v2 = input("Type the second vertex of the edge: ")
        try:
            self.graph.remove_edge(int(v1), int(v2))
        except Exception as e:
            print(e)
            print("\n")

    def change_edge(self):
        v1 = input("Type the first vertex of the edge: ")
        v2 = input("Type the second vertex of the edge: ")
        c = input("Type the cost of the edge: ")
        try:
            self.graph.set_edge_cost(int(v1), int(v2), int(c))
        except Exception as e:
            print(e)
            print("\n")

    def print_edge(self):
        v1 = input("Type the first vertex of the edge: ")
        v2 = input("Type the second vertex of the edge: ")
        try:
            print("The cost of the given edge is {0}.".format(self.graph.get_edge_cost(int(v1), int(v2))))
        except Exception as e:
            print(e)
            print("\n")

    def in_degree(self):
        n = input("Type the vertex for which you wish to find the in degree: ")
        try:
            print(self.graph.in_degree(int(n)))
        except Exception as e:
            print(e)
            print("\n")

    def out_degree(self):
        n = input("Type the vertex for which you wish to find the out degree: ")
        try:
            print(self.graph.out_degree(int(n)))
        except Exception as e:
            print(e)
            print("\n")

    def cnt_vertices(self):
        try:
            print("There are a total of {0} vertices.".format(self.graph.count_vertices()))
        except Exception as e:
            print(e)
            print("\n")

    def cnt_edges(self):
        try:

            print("There are a total of {0} edges.".format(self.graph.count_edges()))
        except Exception as e:
            print(e)
            print("\n")

    def is_vertex(self):
        n = input("Type the vertex you wish to check: ")
        try:
            if self.graph.is_vertex(int(n)):
                print("The given vertex belongs to the graph.")
            else:
                print("The given vertex does not belong to the graph.")
        except Exception as e:
            print(e)
            print("\n")

    def is_edge(self):
        v1 = input("Type the first vertex of the edge: ")
        v2 = input("Type the second vertex of the edge: ")
        try:
            if self.graph.is_edge(int(v1), int(v2)):
                print("The edge does exist.")
            else:
                print("The edge doesn't exist.")
        except Exception as e:
            print(e)
            print("\n")

    def print_vertex_list(self):
        try:
            for node in self.graph.vertices_iterator():
                print(node, end=" ")
            print()
        except Exception as e:
            print(e)
            print("\n")

    def print_neighbour_list(self):
        n = input("Type the vertex you wish to find neighbours for: ")
        try:
            anyone = False
            for node in self.graph.neighbours_iterator(int(n)):
                print(node, end=" ")
                anyone = True
            if not anyone:
                print("Vertex {0} has no neighbours.".format(n))
            else:
                print()
        except Exception as e:
            print(e)
            print("\n")

    def print_transpose_list(self):
        n = input("Type the vertex you wish to find inbound neighbours for: ")
        try:
            anyone = False
            for node in self.graph.transpose_iterator(int(n)):
                print(node, end=" ")
                anyone = True
            if not anyone:
                print("Vertex {0} has no inbound neighbours.".format(n))
            else:
                print()
        except Exception as e:
            print(e)
            print("\n")

    def print_edges(self):
        try:
            anyone = False
            for triple in self.graph.edges_iterator():
                print("Vertices {0} --> {1} and cost {2}.".format(triple[0], triple[1], triple[2]))
                anyone = True
            print("\n")
            if not anyone:
                print("No edges in the graph.")
                print("\n")
        except Exception as e:
            print(e)
            print("\n")

    def read_file(self):
        path = input("Type the file from which you wish to read: ")
        try:
            self.graph = read_file(path)
        except Exception as e:
            print(e)
            print("\n")

    def write_file(self):
        path = input("Type the file you wish to write to: ")
        try:
            write_file(path, self.graph)
        except Exception as e:
            print(e)
            print("\n")
    def copy_graph(self):
        pass
        """
        try:
            self.graph2 = self.graph.copy()
            print("Graph copied.\n")
        except Exception as e:
            print(e)
            print("\n")"""

    def start(self):
        commands = {"1": self.m_graph,
                    "2": self.add_vertex,
                    "3": self.add_edge,
                    "4": self.rem_vertex,
                    "5": self.rem_edge,
                    "6": self.change_edge,
                    "7": self.print_edge,
                    "8": self.in_degree,
                    "9": self.out_degree,
                    "10": self.cnt_vertices,
                    "11": self.cnt_edges,
                    "12": self.is_vertex,
                    "13": self.is_edge,
                    "14": self.print_vertex_list,
                    "15": self.print_neighbour_list,
                    "16": self.print_transpose_list,
                    "17": self.print_edges,
                    "18": self.read_file,
                    "19": self.write_file,
                    "20": self.empty_graph}
        while True:
            print("0. Exit")
            print("1. Generate a graph with n vertices and m random edges")
            print("2. Add a vertex")
            print("3. Add an edge")
            print("4. Remove a vertex")
            print("5. Remove an edge")
            print("6. Change the cost of an edge")
            print("7. Print the cost of an edge")
            print("8. Print the in degree of a vertex")
            print("9. Print the out degree of a vertex")
            print("10. Print the number of vertices")
            print("11. Print the number of edges")
            print("12. Check whether a vertex belongs to the graph")
            print("13. Check whether an edge belongs to the graph")
            print("14. Print the list of vertices")
            print("15. Print the list of outbound neighbours of a vertex")
            print("16. Print the list of inbound neighbours of a vertex")
            print("17. Print the list of edges")
            print("18. Reads the graph from a file")
            print("19. Writes(  ---COPY--- ) the graph to a file")
            print("20. Create an empty graph and start\n")


            opt = input("Your choice:  ")
            if opt in commands:
                commands[opt]()
            elif opt == "0":
                break
            else:
                print("Invalid choice.\n")


UI(Graph).start()