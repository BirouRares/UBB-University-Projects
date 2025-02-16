import copy


class Item:
    def __init__(self, left: str, right: list, markerPos: int):
        self.left = left
        self.right = right
        self.markerPos = markerPos

    def clone(self):
        return Item(copy.deepcopy(self.left), copy.deepcopy(self.right), copy.deepcopy(self.markerPos))

    def __str__(self):
        prefix = " ".join(symbol for symbol in self.right[:self.markerPos])
        suffix = " ".join(symbol for symbol in self.right[self.markerPos:])
        return f'{self.left} -> {prefix}.{suffix}'

    def __hash__(self):
        return hash(self.__str__())

    def __eq__(self, other):
        return self.__str__() == other.__str__()
