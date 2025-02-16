# TODO: lr(0)
# TODO: lr(0)
from Grammar import Grammar
from Item import Item
from Row import Row
from State import State, StateType
from Table import Table
from CannonicalCollection import CanonicalCollection
from ParsingTreeRow import ParsingTreeRow
from State import StateType
import itertools
import copy


class Parser:
    def __init__(self, grammar: Grammar):
        self.grammar: Grammar = grammar
        self.augmentedGrammar: Grammar = grammar.getEnrichedGrammar()
        self.orderedProductions = grammar.listOrderedProductions()

    def closure(self, item: Item) -> State:
        previousClosure = dict()
        currentClosure = {item.clone(): None}
        while True:
            previousClosure = copy.deepcopy(currentClosure)
            extendedClosure = copy.deepcopy(currentClosure)
            for currentItem in currentClosure.keys():
                nonTerminal = self.findDotFollowingNonTerminal(currentItem)
                if nonTerminal is None:
                    continue
                for production in self.grammar.getProductionsFor(nonTerminal):
                    newItem = Item(nonTerminal, list(itertools.chain(*production[1])), 0)
                    extendedClosure[newItem] = None
            currentClosure = extendedClosure
            if str(list(previousClosure.keys())[-1]) == str(list(currentClosure.keys())[-1]):
                break
        return State(currentClosure)

    def findDotFollowingNonTerminal(self, item: Item):
        if not (0 <= item.markerPos < len(item.right)):
            return None
        symbol = item.right[item.markerPos]
        if symbol not in self.grammar.N:
            return None
        return symbol

    def goTo(self, state: State, symbol: str) -> State:
        resultSet = dict()
        for currentItem in state.items:
            nextSymbol = None
            if 0 <= currentItem.markerPos < len(currentItem.right):
                nextSymbol = currentItem.right[currentItem.markerPos]
            if nextSymbol == symbol:
                newItem = Item(currentItem.left, currentItem.right, currentItem.markerPos + 1)
                for closureItem in self.closure(newItem).items:
                    resultSet[closureItem] = None
        return State(resultSet)

    def canonicalCollection(self) -> CanonicalCollection:
        collection = CanonicalCollection()
        collection.addState(
            self.closure(
                Item(
                    self.augmentedGrammar.S,
                    self.augmentedGrammar.getProductionsFor(self.augmentedGrammar.S)[0][1][0],
                    0
                )
            )
        )
        index = 0
        while index < len(collection.states):
            for symbol in collection.states[index].getSymbolsSucceedingTheDot():
                nextState = self.goTo(collection.states[index], symbol)

                existingStateIndex = -1
                for i, state in enumerate(collection.states):
                    if str(state) == str(nextState):
                        existingStateIndex = i
                        break

                if existingStateIndex == -1:
                    collection.addState(nextState)
                    existingStateIndex = len(collection.states) - 1
                collection.connectStates(index, symbol, existingStateIndex)
            index += 1
        return collection

    def parse(self, tokens: list[str]) -> list[ParsingTreeRow]:
        workStack: list[tuple[str, int]] = []
        inputStack: list[str] = tokens
        productionStack: list[int] = []
        parseTable = self.getParsingTable()
        workStack.append(("$", 0))

        parseTree: list[ParsingTreeRow] = []
        treeStack: list[tuple[str, int]] = []

        currentIndex = 0
        while len(inputStack) > 0 or len(workStack) > 0:
            if workStack[-1][1] >= len(parseTable.rows) or parseTable.rows[workStack[-1][1]] is None:
                raise Exception(f'Invalid state {workStack[-1][1]} in the working stack')
            action = parseTable.rows[workStack[-1][1]]
            if action.State == State.SHIFT:
                if len(inputStack) == 0 or inputStack[0] is None:
                    raise Exception('Action is shift but nothing is left in the input stack')
                token = inputStack[0]
                transition = action.transition
                if token not in transition or transition[token] is None:
                    raise Exception(f'Invalid symbol {token} for transition of state {workStack[-1][1]}')
                value = transition[token]
                workStack.append((token, value))
                inputStack.pop(0)
                treeStack.append((token, currentIndex))
                currentIndex += 1
            elif action.State == State.ACCEPT:
                lastNode = treeStack.pop()
                parseTree.append(ParsingTreeRow(lastNode[1], lastNode[0][0], -1, -1))
                if len(inputStack) > 0:
                    raise Exception("Input stack is not empty but reached ACCEPT state")
                return parseTree
            elif action.State == State.REDUCE:
                targetProduction = self.orderedProductions[action.reductionIndex]
                parentIndex = currentIndex
                currentIndex += 1
                lastSibling = -1
                for _ in range(len(targetProduction[1])):
                    workStack.pop()
                    lastNode = treeStack.pop()
                    parseTree.append(ParsingTreeRow(lastNode[1], lastNode[0][0], parentIndex, lastSibling))
                    lastSibling = lastNode[1]
                treeStack.append((targetProduction[0], parentIndex))
                previousState = workStack[-1]
                workStack.append(
                    (targetProduction[0], parseTable.rows[previousState[1]].transition[targetProduction[0][0]])
                )
                productionStack = [action.reductionIndex] + productionStack
            else:
                raise Exception(str(action.State))
        raise Exception('Unexpected parsing termination')

    def getParsingTable(self) -> Table:
        canonicalStates = self.canonicalCollection()
        table = Table()
        for key in canonicalStates.connectionMap.keys():
            state = canonicalStates.states[key[0]]
            if key[0] not in table.rows:
                table.rows[key[0]] = Row(state.category, {}, None)
            table.rows[key[0]].transition[key[1]] = canonicalStates.connectionMap[key]
        for i, state in enumerate(canonicalStates.states):
            if state.category == State.REDUCE:
                index = None
                try:
                    index = self.orderedProductions.index(
                        ([list(state.items.keys())[0].left], list(state.items.keys())[0].right))
                except ValueError:
                    pass
                table.rows[i] = Row(state.category, None, index)
            if state.category == State.ACCEPT:
                table.rows[i] = Row(state.category, None, None)

        return table



class SyntaxAnalyzer:
    def __init__(self, grammar: Table):
        self.grammar: Grammar = grammar
        self.augmentedGrammar: Grammar = grammar.getEnrichedGrammar()
        self.orderedProductions = grammar.listOrderedProductions()

    def closure(self, item: Item) -> State:
        previousClosure = dict()
        currentClosure = {item.clone(): None}
        while True:
            previousClosure = copy.deepcopy(currentClosure)
            extendedClosure = copy.deepcopy(currentClosure)
            for currentItem in currentClosure.keys():
                nonTerminal = self.findDotFollowingNonTerminal(currentItem)
                if nonTerminal is None:
                    continue
                for production in self.grammar.getProductionsFor(nonTerminal):
                    newItem = Item(nonTerminal, list(itertools.chain(*production[1])), 0)
                    extendedClosure[newItem] = None
            currentClosure = extendedClosure
            if str(list(previousClosure.keys())[-1]) == str(list(currentClosure.keys())[-1]):
                break
        return State(currentClosure)

    def findDotFollowingNonTerminal(self, item: Item):
        if not (0 <= item.markerPos < len(item.right)):
            return None
        symbol = item.right[item.markerPos]
        if symbol not in self.grammar.N:
            return None
        return symbol

    def goTo(self, state: State, symbol: str) -> State:
        resultSet = dict()
        for currentItem in state.items:
            nextSymbol = None
            if 0 <= currentItem.markerPos < len(currentItem.right):
                nextSymbol = currentItem.right[currentItem.markerPos]
            if nextSymbol == symbol:
                newItem = Item(currentItem.left, currentItem.right, currentItem.markerPos + 1)
                for closureItem in self.closure(newItem).items:
                    resultSet[closureItem] = None
        return State(resultSet)

    def canonicalCollection(self) -> CanonicalCollection:
        collection = CanonicalCollection()
        collection.addState(
            self.closure(
                Item(
                    self.augmentedGrammar.S,
                    self.augmentedGrammar.getProductionsFor(self.augmentedGrammar.S)[0][1][0],
                    0
                )
            )
        )
        index = 0
        while index < len(collection.states):
            for symbol in collection.states[index].getSymbolsSucceedingTheDot():
                nextState = self.goTo(collection.states[index], symbol)

                existingStateIndex = -1
                for i, state in enumerate(collection.states):
                    if str(state) == str(nextState):
                        existingStateIndex = i
                        break

                if existingStateIndex == -1:
                    collection.addState(nextState)
                    existingStateIndex = len(collection.states) - 1
                collection.connectStates(index, symbol, existingStateIndex)
            index += 1
        return collection

    def parse(self, tokens: list[str]) -> list[ParsingTreeRow]:
        workStack: list[tuple[str, int]] = []
        inputStack: list[str] = tokens
        productionStack: list[int] = []
        parseTable = self.getParsingTable()
        workStack.append(("$", 0))

        parseTree: list[ParsingTreeRow] = []
        treeStack: list[tuple[str, int]] = []

        currentIndex = 0
        while len(inputStack) > 0 or len(workStack) > 0:
            if workStack[-1][1] >= len(parseTable.rows) or parseTable.rows[workStack[-1][1]] is None:
                raise Exception(f'Invalid state {workStack[-1][1]} in the working stack')
            action = parseTable.rows[workStack[-1][1]]
            if action.State == State.SHIFT:
                if len(inputStack) == 0 or inputStack[0] is None:
                    raise Exception('Action is shift but nothing is left in the input stack')
                token = inputStack[0]
                transition = action.transition
                if token not in transition or transition[token] is None:
                    raise Exception(f'Invalid symbol {token} for transition of state {workStack[-1][1]}')
                value = transition[token]
                workStack.append((token, value))
                inputStack.pop(0)
                treeStack.append((token, currentIndex))
                currentIndex += 1
            elif action.State == State.ACCEPT:
                lastNode = treeStack.pop()
                parseTree.append(ParsingTreeRow(lastNode[1], lastNode[0][0], -1, -1))
                if len(inputStack) > 0:
                    raise Exception("Input stack is not empty but reached ACCEPT state")
                return parseTree
            elif action.State == State.REDUCE:
                targetProduction = self.orderedProductions[action.reductionIndex]
                parentIndex = currentIndex
                currentIndex += 1
                lastSibling = -1
                for _ in range(len(targetProduction[1])):
                    workStack.pop()
                    lastNode = treeStack.pop()
                    parseTree.append(ParsingTreeRow(lastNode[1], lastNode[0][0], parentIndex, lastSibling))
                    lastSibling = lastNode[1]
                treeStack.append((targetProduction[0], parentIndex))
                previousState = workStack[-1]
                workStack.append(
                    (targetProduction[0], parseTable.rows[previousState[1]].transition[targetProduction[0][0]])
                )
                productionStack = [action.reductionIndex] + productionStack
            else:
                raise Exception(str(action.State))
        raise Exception('Unexpected parsing termination')

    def getParsingTable(self) -> Table:
        canonicalStates = self.canonicalCollection()
        table = Table()
        for key in canonicalStates.connectionMap.keys():
            state = canonicalStates.states[key[0]]
            if key[0] not in table.rows:
                table.rows[key[0]] = Row(state.category, {}, None)
            table.rows[key[0]].transition[key[1]] = canonicalStates.connectionMap[key]
        for i, state in enumerate(canonicalStates.states):
            if state.category == State.REDUCE:
                index = None
                try:
                    index = self.orderedProductions.index(
                        ([list(state.items.keys())[0].left], list(state.items.keys())[0].right))
                except ValueError:
                    pass
                table.rows[i] = Row(state.category, None, index)
            if state.category == State.ACCEPT:
                table.rows[i] = Row(state.category, None, None)

        return table
