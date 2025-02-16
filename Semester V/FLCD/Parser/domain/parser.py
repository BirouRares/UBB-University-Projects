from domain.item import Item
from domain.state import State
from domain.table import Table, addSpaces
import copy

AUGMENTED_PRODUCTION_LHS = 'S`'
REDUCE = 'reduce'
ACCEPT = 'acc'
SHIFT = 'shift'

class Parser:
    def __init__(self, grammar):
        self.grammar = grammar
        self._initializeGrammar()
        self.items = []
        self._initializeItems()
        self.canonicalCollection = []
        self.table = Table(self.grammar.N + self.grammar.E)

    def _initializeGrammar(self):
        """ Add the augmented production S` -> S to the grammar."""
        self.grammar.P = {AUGMENTED_PRODUCTION_LHS: [(self.grammar.S, -1)], **self.grammar.P}

    def _initializeItems(self):
        """ Generate initial LR(0) items by placing the dot at the start of each production."""
        for lhs, productions in self.grammar.P.items():
            for rhs in productions:
                self.items.append(Item(lhs, rhs[0], self.grammar.N + self.grammar.E))

    def _closure(self, itemList):
        """ Compute the closure of a given set of items."""
        closureItems = itemList.copy()
        while True:
            newItems = closureItems.copy()
            for item in newItems:
                if item.isDotAtTheEnd():
                    continue
                symbolAfterDot = item.getSymbolAfterDot()
                if symbolAfterDot in self.grammar.N:
                    for potentialItem in self.items:
                        if potentialItem.lhs == symbolAfterDot and potentialItem not in closureItems:
                            closureItems.append(potentialItem)
            if closureItems == newItems:
                break
        return State(closureItems, len(self.canonicalCollection))

    def _goto(self, state, symbol):
        """ Compute the GOTO function for a state and a given symbol."""
        items = [
            copy.deepcopy(item).moveDot()
            for item in state.items if not item.isDotAtTheEnd() and item.getSymbolAfterDot() == symbol
        ]
        if items:
            gotoState = self._closure(items)
            self.table.addSymbolToState(state, symbol, gotoState)
            return gotoState
        return []

    def _isStateInCollection(self, state):
        """ Check if a state already exists in the canonical collection."""
        return any(existingState.items == state.items for existingState in self.canonicalCollection)

    def computeCanonicalCollection(self):
        """ Compute the canonical collection of LR(0) items."""
        self.canonicalCollection.append(self._closure([self.items[0]]))
        while True:
            newCollection = self.canonicalCollection.copy()
            for state in newCollection:
                for symbol in self.grammar.N + self.grammar.E:
                    gotoState = self._goto(state, symbol)
                    if gotoState and not self._isStateInCollection(gotoState):
                        self.canonicalCollection.append(gotoState)
            if newCollection == self.canonicalCollection:
                break

    def computeTableActions(self):
        """ Populate the LR(0) parsing table with actions and GOTO entries."""
        for state in self.canonicalCollection:
            for item in state.items:
                if item.lhs == AUGMENTED_PRODUCTION_LHS and item.isDotAtTheEnd():
                    self.table.addActionToState(state, ACCEPT)
                elif item.isDotAtTheEnd():
                    reduceValue = next(
                        (rhs[1] for rhs in self.grammar.P[item.lhs] if item.rhs == rhs[0]),
                        -1
                    )
                    if self.table.isActionToStateDefined(state):
                        existingAction = self.table.actionsForStates[state]
                        if existingAction.startswith(SHIFT):
                            raise RuntimeError(f"SHIFT/REDUCE conflict in state {state.index}")
                        elif existingAction.startswith(REDUCE):
                            raise RuntimeError(f"REDUCE/REDUCE conflict in state {state.index}")
                    self.table.addActionToState(state, f"{REDUCE}{reduceValue}")
                else:
                    if self.table.isActionToStateDefined(state):
                        existingAction = self.table.actionsForStates[state]
                        if existingAction.startswith(REDUCE):
                            raise RuntimeError(f"SHIFT/REDUCE conflict in state {state.index}")
                    self.table.addActionToState(state, SHIFT)

    def buildInputStack(self, sequence):
        """ Convert the input sequence into a stack of valid symbols."""
        inputStack, index = [], 0
        while index < len(sequence):
            nextSymbol = sequence[index:]
            while nextSymbol not in self.grammar.E + self.grammar.N:
                nextSymbol = nextSymbol[:-1]
            inputStack.append(nextSymbol)
            index += len(nextSymbol)
        return inputStack

    def parseSequence(self, sequence):
        """ Parse the input sequence and output the sequence of productions used."""
        workingStack, inputStack, outputStack = [0], self.buildInputStack(sequence), []
        while True:
            print(
                f"{workingStack}{addSpaces(40 - len(str(workingStack)))} | "
                f"{inputStack}{addSpaces(40 - len(str(inputStack)))} | "
                f"{outputStack}"
            )

            topOfInputStack = inputStack.pop(0) if inputStack else None
            currentState = self.getStateHavingIndex(workingStack[-1])
            currentAction = self.table.actionsForStates[currentState]

            if currentAction == SHIFT and topOfInputStack is not None:
                workingStack.extend([topOfInputStack, self.table.stateToStateMap[currentState][topOfInputStack]])
            elif REDUCE in currentAction:
                if topOfInputStack is not None:
                    inputStack.insert(0, topOfInputStack)
                reduceTo, reduceFrom = self.grammar.getProductionAsPair(int(currentAction[len(REDUCE):]))
                outputStack.insert(0, currentAction[len(REDUCE):])
                for _ in reduceFrom[::-1]:
                    workingStack.pop()
                workingStack.append(reduceTo)
                workingStack.append(self.table.stateToStateMap[currentState][reduceTo])
            elif currentAction == ACCEPT and topOfInputStack is None:
                break
            else:
                raise RuntimeError("The sequence is not accepted")
        print(f"\nFinal output: {outputStack}")

    def getStateHavingIndex(self, index):
        """ Retrieve a state by its index."""
        return next((state for state in self.canonicalCollection if state.index == index), None)

    def printCanonicalCollection(self):
        """ Print all states in the canonical collection."""
        print("\n".join(map(repr, self.canonicalCollection)))

    def printLr0Table(self):
        """ Print the LR(0) parsing table."""
        print(self.table)
