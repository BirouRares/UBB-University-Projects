from domain import GraphException
from generate_graph import generate_random_graph
from read_file import read_graph_from_file
from write_file import write_graph_to_file
from write_file2 import write_graph_to_file2


class Console:

    def __init__(self, service, graph, validation):
        self._graph = graph
        self._service = service
        self._validation = validation

    def read_graph(self):
        file_name = input("Type in the file name: ")
        read_graph_from_file(file_name, self._graph, self._service)
        print("The command executed with success!")

    def display_graph(self):
        file_name = input("Type in the file name: ")
        criteria = int(input("Type 1 for displaying the graph without isolated points or 2 for displaying the graph "
                         "with isolated points"))
        if criteria != 1 and criteria != 2:
            raise GraphException("Invalid input!")
        if criteria == 1:
            write_graph_to_file(file_name, self._graph, self._service)
        elif criteria == 2:
            write_graph_to_file2(file_name, self._graph, self._service)
        print("The command executed with success!")

    def generate_a_random_graph(self):
        print("Type in the number of vertices: ")
        number_of_vertices = int(input())
        print("Type in the number of edges: ")
        number_of_edges = int(input())
        generate_random_graph(self._graph, self._service, number_of_vertices, number_of_edges)
        print("The graph was generated with success!!!")

    def get_cost(self):
        first_vertex = int(input("Type in the first vertex: "))
        second_vertex = int(input("Type in the second vertex: "))
        if self._graph.check_existence_of_vertex(first_vertex) and self._graph.check_existence_of_vertex(second_vertex):
            if self._service.check_existence_edge(first_vertex, second_vertex):
                cost = self._service.get_cost_for_edge(first_vertex, second_vertex)
                print(cost)
            else:
                print("There is no edge between these two vertices!")
        else:
            print("The given vertices doesn't exist!")

    def lowest_cost_walk(self):
        first_vertex = int(input("Type in the first vertex: "))
        second_vertex = int(input("Type in the second vertex: "))
        path, distance = self._service.get_lowest_cost_path(first_vertex, second_vertex)
        print("The lowest cost walk is: " + distance.__str__())
        print("The path for the lowest cost is : ")
        print(path)


    def display_menu(self):
        print("1. Read the graph from the file")
        print("2. Write the graph into a file")
        print("3. Generate a random graph")
        print("4. Get the cost of a specified edge")
        print("5. Dijkstra algorithm for the minimum cost path in reverse")

    def start(self):

        are_we_done_yet = False
        command_dict = {'0': self.display_menu, '1': self.read_graph,
                        '2': self.display_graph, '3': self.generate_a_random_graph, '4': self.get_cost, '5' : self.lowest_cost_walk}
        while not are_we_done_yet:
            self.display_menu()
            command = input('\nWhat would you like to do? Enter command: \n')
            if command in command_dict:
                try:
                    command_dict[command]()
                except ValueError as ve:
                    print(ve)
                except GraphException as ge:
                    print(ge)
            elif command == '0':
                self.display_menu()
            elif command == 'x':
                print("Goodbye!")
                are_we_done_yet = True
            else:
                print("Invalid command")
