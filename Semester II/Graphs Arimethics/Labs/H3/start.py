from domain import Graph
from service import DirectedGraph
from ui import Console
from validation import Validation
from read_file import read_graph_from_file
from write_file import write_graph_to_file

graph = Graph()
service = DirectedGraph(graph)
validation = Validation(graph, service)
console = Console(service, graph, validation)
console.start()
