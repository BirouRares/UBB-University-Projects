class State:

    def __init__(self, items, index):
        self.items = items # list of items
        self.index = index # index of the state

    def add(self, item):
        self.items.append(item)

    def __repr__(self):
        result = 'S' + str(self.index) + '( '
        result += str(self.items)
        result += ' )'
        return result

    def __str__(self):
        return self.__repr__()
