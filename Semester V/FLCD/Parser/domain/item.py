class Item:

    def __init__(self, lhs: str, rhs: str, symbols):
        self.lhs = lhs
        self.rhs = rhs
        self.dotPosition = 0
        self.symbols = symbols

    def moveDot(self):
        self.dotPosition += len(self.getSymbolAfterDot())

    def getSymbolAfterDot(self):
        nextPossibleSymbol = self.rhs[self.dotPosition:] # the rhs list after the dot
        while nextPossibleSymbol not in self.symbols:
            nextPossibleSymbol = nextPossibleSymbol[:-1]
        return nextPossibleSymbol

    def isDotAtTheEnd(self):
        return len(self.rhs) == self.dotPosition

    def setSymbols(self, symbolList):
        self.symbols = symbolList

    def __eq__(self, x):
        return self.lhs == x.lhs and self.rhs == x.rhs and self.dotPosition == x.dotPosition

    def __repr__(self):
        representation = self.lhs + ' -> '
        for pos in range(0, self.dotPosition):
            representation += self.rhs[pos]
        representation += '.'
        for pos in range(self.dotPosition, len(self.rhs)):
            representation += self.rhs[pos]
        return representation

    def __str__(self):
        return self.__repr__()
