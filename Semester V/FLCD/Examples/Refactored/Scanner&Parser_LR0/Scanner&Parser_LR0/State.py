from enum import Enum
from Item import RuleItem
from Grammar import Grammar


class StateType(Enum):
    ACCEPT = 1
    REDUCE = 2
    SHIFT = 3
    REDUCE_REDUCE_CONFLICT = 4
    SHIFT_REDUCE_CONFLICT = 5


def testCond(items: dict[RuleItem], condition) -> bool:
    return all(condition(it) for it in items.keys())


class State:
    def __init__(self, items: dict[RuleItem]):
        self.items = items
        if not items:
            self.stateType = StateType.SHIFT_REDUCE_CONFLICT
            return

        firstItem = next(iter(items))

        # Determine state type based on conditions
        if len(items) == 1 and len(firstItem.rhs) == firstItem.dotPos:
            if firstItem.lhs == Grammar.enrichedGrammarStartingSymbol:
                self.stateType = StateType.ACCEPT
            else:
                self.stateType = StateType.REDUCE
        elif testCond(items, lambda it: len(it.rhs) > it.dotPos):
            self.stateType = StateType.SHIFT
        elif len(items) > 1 and testCond(items, lambda it: len(it.rhs) == it.dotPos):
            self.stateType = StateType.REDUCE_REDUCE_CONFLICT

    def getSymbolsSucceedingTheDot(self) -> list[str]:
        return [it.rhs[it.dotPos] for it in self.items.keys() if 0 <= it.dotPos < len(it.rhs)]

    def __str__(self):
        items_str = ', '.join(str(item) for item in self.items) if self.items else '[]'
        return f'{self.stateType} items: {items_str}'
