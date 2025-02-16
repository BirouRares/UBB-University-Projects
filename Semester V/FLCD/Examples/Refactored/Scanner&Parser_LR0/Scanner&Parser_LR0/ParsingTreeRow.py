from dataclasses import dataclass
from typing import Optional


@dataclass
class ParsingTreeRow:
    index: int
    info: str
    parent: Optional[int] = -1
    rightSibling: Optional[int] = -1

    def __str__(self):
        return (
            f"Index: {self.index}, Info: {self.info}, "
            f"Parent: {self.parent}, Right Sibling: {self.rightSibling}"
        )

    def has_sibling(self) -> bool:
        return self.rightSibling != -1

    def is_root(self) -> bool:
        return self.parent == -1
