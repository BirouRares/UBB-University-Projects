from dataclasses import dataclass
from typing import Optional
from State import StateType


@dataclass
class Row:
    stateType: StateType
    goTo: Optional[dict[str, int]] = None
    reductionIndex: Optional[int] = None

    def __str__(self):
        if self.stateType == StateType.REDUCE:
            return f"REDUCE {self.reductionIndex}"
        elif self.stateType == StateType.ACCEPT:
            return "ACCEPT"
        elif self.stateType == StateType.SHIFT:
            return f"SHIFT {self.goTo}"
        else:
            return f"No state: goTo={self.goTo}, reductionIndex={self.reductionIndex}"
