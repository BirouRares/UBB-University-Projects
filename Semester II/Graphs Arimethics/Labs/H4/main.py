from DirectedGraph import DirectedGraph
from ProgramExceptions import myException
import math


class Console():

    def __init__(self, fileName):

        self.__fileName = fileName
        self.__commands = {"1": self.__loadFromFile, "2": self.__performDAG, "3": self.__highestCostPath}

    def __loadFromFile(self): # this is the function that loads the graph from the file
        try:
            with open(self.__fileName, "r") as file:
                firstLine = file.readline()
                firstLine = firstLine.strip().split()
                vertices, edges = int(firstLine[0]), int(firstLine[1])
                self.__graph = DirectedGraph(vertices)
                for times in range(edges):
                    line = file.readline()
                    line = line.strip().split()
                    start, end, cost = int(line[0]), int(line[1]), int(line[2])
                    self.__graph.addEdge(start, end, cost)
            print("Graph loaded.")
        except IOError:
            raise myException("File Reading Error")

    def __performDAG(self):  # this is the function that computes the topological sorting
        sortedDAG = self.__graph.DAG()
        if sortedDAG != []: # if the graph is DAG
            print(sortedDAG) # print the topological sorting
            self.__sortedDAG = sortedDAG # save the topological sorting
            print("Done computing topological sorting with dfs.")
        else:
            print("Graph is not DAG")

    def __highestCostPath(self): # this is the function that computes the highest cost path
        print("Start:")
        source = int(input())
        print("End:")
        destination = int(input())
        cost, prev = self.__graph.highestCostPath(self.__sortedDAG, source, destination) # compute the highest cost path
        if cost == -math.inf: # if there is no path
            print("No possible path")
            return
        path = [destination]
        while source != destination: # reconstruct the path
            destination = prev[destination] # go to the previous vertex
            path.append(destination) # add the vertex to the path
        print("Cost:")
        print(cost)
        print("Path:")
        path.reverse()
        print(path)

    def run(self):
        while True:
            print(">>")
            cmd = input()
            if cmd == "end":
                return
            elif cmd in self.__commands:
                try:
                    self.__commands[cmd]()
                except myException as e:
                    print(e)
            else:
                print("Wrong cmd")


c = Console("graph.txt")
c.run()
