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
        self.enrichedGrammar: Grammar = grammar.getEnrichedGrammar()
        self.orderedProductions = grammar.getOrderedProductions()

    def closure(self, item: Item) -> State:
        # Expands a given item into a state by adding all possible productions
        # for a non-terminal immediately after the dot.
        currentClosure = [item.deepCopy()]
        while True:
            oldClosure = currentClosure[:]
            for it in oldClosure:
                nonTerminal = self.getDotPrecededNonTerminal(it)
                if nonTerminal is None:
                    continue
                for production in self.grammar.getProductionsFor(nonTerminal):
                    currentItem = Item(nonTerminal, list(itertools.chain(*production[1])), 0)
                    if currentItem not in currentClosure:  # Ensure no duplicates
                        currentClosure.append(currentItem)
            if oldClosure == currentClosure:  # No new items added
                break
        return State(currentClosure)

    def getDotPrecededNonTerminal(self, item: Item):
        #Extracts the non-terminal directly after the dot in an item, if it exists
        if not (0 <= item.dotPos < len(item.rhs)):
            return None
        term = item.rhs[item.dotPos]
        if term not in self.grammar.N:
            return None
        return term

    def goTo(self, state: State, element: str) -> State:
        # Computes the state resulting from moving the dot past a specific symbol
        result = []
        for item in state.items:
            if 0 <= item.dotPos < len(item.rhs) and item.rhs[item.dotPos] == element:
                nextItem = Item(item.lhs, item.rhs, item.dotPos + 1)
                if nextItem not in result:  # Ensure no duplicates
                    result.append(nextItem)
        return self.closure(result[0]) if result else State([])

    def canonicalCollection(self) -> CanonicalCollection:
        # Constructs the set of all possible states for the grammar
        canonicalCollection = CanonicalCollection()
        canonicalCollection.addState(
            self.closure(
                Item(
                    self.enrichedGrammar.S,
                    self.enrichedGrammar.getProductionsFor(self.enrichedGrammar.S)[0][1][0],
                    0
                )
            )
        )
        i = 0
        while i < len(canonicalCollection.states):
            for symbol in canonicalCollection.states[i].getSymbolsSucceedingTheDot():
                newState = self.goTo(canonicalCollection.states[i], symbol)
                if newState.items not in [s.items for s in canonicalCollection.states]:  # Ensure state uniqueness
                    canonicalCollection.addState(newState)
                indexInStates = next(
                    (ind for ind, s in enumerate(canonicalCollection.states) if s.items == newState.items), -1
                )
                canonicalCollection.connectStates(i, symbol, indexInStates)
            i += 1
        return canonicalCollection

    #Generate the parse tree by tracking parent-child relationships during reductions
    def parse(self, word: list[str]) -> list[ParsingTreeRow]:
        workingStack: list[tuple[str, int]] = []  # Current (symbol, state)
        remainingStack: list[str] = word
        productionStack: list[int] = []  # Indices of the grammar rules applied
        parsingTable = self.getParsingTable()
        workingStack.append(("$", 0))  # Initial state with the end marker

        parsingTree: list[ParsingTreeRow] = []
        treeStack: list[tuple[str, int]] = []

        currentIndex = 0
        while len(remainingStack) > 0 or len(workingStack) > 0:
            if workingStack[-1][1] >= len(parsingTable.tableRow) or parsingTable.tableRow[workingStack[-1][1]] is None:
                raise Exception(f'Invalid state {workingStack[-1][1]} in the working stack')
            tableValue = parsingTable.tableRow[workingStack[-1][1]]

            if tableValue.stateType == StateType.SHIFT:
                # Move the next symbol from the remainingStack to the workingStack
                if len(remainingStack) == 0 or remainingStack[0] is None:
                    raise Exception('Action is shift but nothing else is left in the remaining stack')
                token = remainingStack[0]
                goto = tableValue.goTo
                if token not in goto or goto[token] is None:
                    raise Exception(f'Invalid symbol {token} for goto of state {workingStack[-1][1]}')
                value = goto[token]
                workingStack.append((token, value))
                remainingStack.pop(0)
                treeStack.append((token, currentIndex))  # Add for later construction
                currentIndex += 1
            elif tableValue.stateType == StateType.ACCEPT:  # Parsing successful
                lastElement = treeStack.pop()
                parsingTree.append(ParsingTreeRow(lastElement[1], lastElement[0][0], -1, -1))
                if len(remainingStack) > 0:
                    raise Exception("Input stack is not empty but reached ACCEPT state")
                return parsingTree
            elif tableValue.stateType == StateType.REDUCE:
                # Replace the symbols on the top of the working stack with the lhs of the production
                productionToReduceTo = self.orderedProductions[tableValue.reductionIndex]

                # Update the parent node index for the parse tree
                parentIndex = currentIndex
                currentIndex += 1
                lastIndex = -1

                for _ in range(len(productionToReduceTo[1])):  # Each RHS symbol
                    workingStack.pop()
                    lastElement = treeStack.pop()
                    parsingTree.append(ParsingTreeRow(lastElement[1], lastElement[0][0], parentIndex, lastIndex))
                    # Add it to the parse tree with the current non-terminal as the parent
                    lastIndex = lastElement[1]

                treeStack.append((productionToReduceTo[0], parentIndex))  # Add the LHS to the tree stack
                previous = workingStack[-1]
                workingStack.append(
                    (productionToReduceTo[0], parsingTable.tableRow[previous[1]].goTo[productionToReduceTo[0][0]])
                )
                # Add LHS to the working stack
                productionStack = [tableValue.reductionIndex] + productionStack  # Used production rule
            else:
                raise Exception(str(tableValue.stateType))
        raise Exception('Bad things happened')

    def getParsingTable(self) -> Table:
        canonicalCollection = self.canonicalCollection()
        # Compute the CC, representing all possible states and transitions between
        table = Table()
        for k in canonicalCollection.adjacencyList.keys():  # Shift transitions
            # Keys: (currentState, symbol) pairs.
            # Values: The state reached after processing the symbol from currentState.
            state = canonicalCollection.states[k[0]]
            if k[0] not in table.tableRow:
                table.tableRow[k[0]] = Row(state.stateType, {}, None)  # Initialize a new row
            table.tableRow[k[0]].goTo[k[1]] = canonicalCollection.adjacencyList[k]  # Add the shift transition

        for i, state in enumerate(canonicalCollection.states):  # Reduce and accept transitions
            if state.stateType == StateType.REDUCE:
                index = None
                try:
                    # Adjust the retrieval of items as state.items is now a list
                    index = self.orderedProductions.index(
                        ([state.items[0].lhs], state.items[0].rhs)
                    )
                except ValueError:
                    pass
                table.tableRow[i] = Row(state.stateType, None, index)
                # Update the table row for the current state with the REDUCE action
            if state.stateType == StateType.ACCEPT:
                table.tableRow[i] = Row(state.stateType, None, None)

        return table
