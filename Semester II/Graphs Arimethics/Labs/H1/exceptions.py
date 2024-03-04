class EdgeError(Exception): # Exception class for the graph

    def __init__(self, message=""): # constructor
        super().__init__(message) # call the constructor of the parent class
class VertexError(Exception): # Exception class for the graph

    def __init__(self, message=""): # constructor
        super().__init__(message) # call the constructor of the parent class

