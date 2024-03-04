from ProgramExceptions import myException
import math


class DirectedGraph(object):

    def __init__(self, vertices):

        self.__dictIn = {}

        self.__dictOut = {}

        self.__dictCosts = {}

        for i in range(vertices):
            self.__dictOut[i] = []
            self.__dictIn[i] = []

    def parseKeys(self):
        """returns a copy of all the vertex keys"""
        return list(self.__dictOut.keys())

    def parseIterableOut(self, x):
        """returns a copy of all out neighbours of x"""
        try:
            return list(self.__dictOut[x])
        except KeyError:
            raise myException("No such vertex")

    def parseIterableIn(self, x):
        """return a copy of all in neighbours of x"""
        try:
            return list(self.__dictIn[x])
        except KeyError:
            raise myException("No such vertex")

    def isEdge(self, start, end):
        """Returns True if there is an edge from x to y, False otherwise"""
        try:
            return end in self.__dictOut[start]
        except KeyError:
            raise myException("No such pair of vertices in the graph.")

    def addEdge(self, start, end, cost):
        """adds an edge (start,end) that has that cost to the graph
           precondition: the edge mustn't already exist and the vertices need to be valid"""
        exception = ""
        if self.isEdge(start, end):
            exception += "Already an edge;"
        if len(exception):
            raise myException(exception)
        self.__dictOut[start].append(end)
        self.__dictIn[end].append(start)
        self.__dictCosts[(start, end)] = cost

    def addVertex(self, x):
        """adds the vertex x to the graph, as an isolated vertex
            precondition: x mustn't already be a vertex in the graph"""
        if x in self.parseKeys():
            raise myException("Already existing vertex")
        self.__dictOut[x] = []
        self.__dictIn[x] = []

    def retrieveCost(self, start, end):
        if self.isEdge(start, end):
            return self.__dictCosts[(start, end)]

    def removeVertex(self, x):
        """removes the vertex x from the graph
           precondition: x needs to exist in the graph as a vertex"""
        if x not in self.parseKeys():
            raise myException("Vertex doesn't exist")
        for y in self.__dictOut[x]:
            self.__dictIn[y].remove(x)
            del self.__dictCosts[(x, y)]
        del self.__dictOut[x]
        for y in self.__dictIn[x]:
            self.__dictOut[y].remove(x)
            del self.__dictCosts[(y, x)]
        del self.__dictIn[x]

    def removeEdge(self, x, y):
        """removes the edge (x,y) from the graph
            precondition: (x,y) needs to be a valid edge in the graph """
        if not self.isEdge(x, y):
            raise myException("This edge doesn't exist")
        del self.__dictCosts[(x, y)]
        self.__dictOut[x].remove(y)
        self.__dictIn[y].remove(x)

    def getNumberOfVertices(self):
        """return an integer containing the number of vertices in the graph"""
        return len(self.parseKeys())

    def getOutDegree(self, x):
        """return an integer representing the out degree of the vertex x
           precondition: x needs to be a valid vertex in the graph
                         in case it isn't, the error is handled and the user is informed"""
        try:
            return len(self.__dictOut[x])
        except KeyError:
            raise myException("No such vertex")

    def getInDegree(self, x):
        """return an integer representing the in degree of the vertex x
           precondition: x needs to be a valid vertex in the graph """
        try:
            return len(self.__dictIn[x])

        except KeyError:
            raise myException("No such vertex")

    def modifyEdgeCost(self, start, end, c):
        """modifies the cost of an edge
        precondition: (x,y) needs to be a valid edge in the graph"""
        if (start, end) in self.__dictCosts:
            self.__dictCosts[(start, end)] = c
        else:
            raise myException("No such edge")

    """
    x: The current vertex being processed.
    sorted: A list that will store the sorted vertices in the topological order.
    fullyProcessed: A set that keeps track of vertices that have been fully processed
    inProcess: A set that keeps track of vertices that are currently being processed in the current DFS traversal.
    """
    def __topologicalSortWithDFS(self, x, sorted, fullyProcessed, inProcess):
        inProcess.add(x)
        # iterates over the inbound neighbors of the current vertex x
        for inboundNeighbour in self.parseIterableIn(x):
            # checks if the inbound neighbor is already being processed in the current DFS traversal.
            if inboundNeighbour in inProcess: # if it is, then the graph contains a cycle
                return False
            else:
                # is used to check if the recursive call to __topologicalSortWithDFS
                if inboundNeighbour not in fullyProcessed: # returns False, then the graph contains a cycle
                    ok = self.__topologicalSortWithDFS(inboundNeighbour, sorted, fullyProcessed, inProcess)
                    if not ok: # if it does, then the graph contains a cycle
                        print(sorted)
                        return False
        inProcess.remove(x)
        sorted.append(x)
        fullyProcessed.add(x)
        return True
    """
    sorted, which will store the sorted vertices in the topological order.
    fullyProcessed and inProcess. These sets are used to keep track of vertices that have been fully processed 
    and vertices that are currently being processed, respectively.
    The code enters a loop that iterates over the vertices obtained from the parseKeys method
    """
    def DAG(self):
        sorted = [] # will store the sorted vertices in the topological order
        fullyProcessed = set() # will keep track of vertices that have been fully processed
        inProcess = set() # will keep track of vertices that are currently being processed
        for vertex in self.parseKeys(): # iterates over the vertices obtained from the parseKeys method
            if vertex not in fullyProcessed: # if the current vertex is not in the fullyProcessed set
                ok = self.__topologicalSortWithDFS(vertex, sorted, fullyProcessed, inProcess) # then it calls the __topologicalSortWithDFS method
                if not ok:
                    return []
        return sorted[:]

    def highestCostPath(self, sorted, source, destination): # sorted is the topological order
        distances = [-math.inf] * len(sorted) # stores the highest cost path from the source to the current vertex
        prev = [-1] * len(sorted) # stores the previous vertex in the highest cost path from the source to the current vertex
        distances[source] = 0 # the distance from the source to itself is 0
        for vertex in sorted: # iterates over the vertices in the topological order
            if vertex == destination: # if the current vertex is the destination vertex, then it breaks the loop
                break
            for outboundNeighbours in self.parseIterableOut(vertex): # iterates over the outbound neighbours of the current vertex
                if distances[outboundNeighbours] < distances[vertex] + self.retrieveCost(vertex, outboundNeighbours):
                    # if the distance from the source to the outbound neighbour is smaller than the distance from the source to the current vertex plus the cost of the edge between the current vertex and the outbound neighbour
                    distances[outboundNeighbours] = distances[vertex] + self.retrieveCost(vertex, outboundNeighbours)
                    # then the distance from the source to the outbound neighbour is updated
                    prev[outboundNeighbours] = vertex
                    # the previous vertex in the highest cost path from the source to the outbound neighbour is updated
        return distances[destination], prev[:]