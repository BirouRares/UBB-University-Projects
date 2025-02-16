from State import State


class CanonicalCollection:
    def __init__(self):
        self.nodes: list[State] = []
        self.connectionMap: dict[tuple[int, str], int] = {}

    def addNode(self, node: State):
        self.nodes.append(node)

    def linkNodes(self, firstNodeIdx: int, symbol: str, secondNodeIdx: int):
        self.connectionMap[(firstNodeIdx, symbol)] = secondNodeIdx
