import random
import copy
from src.expenses_class import Expenses

class MemoryRepository():
    def __init__(self):
        self._expenses = []

    def add(self, expense):
        self._expenses.append(expense)

    """
    def add_10(self):
        self._expenses.append(Expenses(10,500,"rent"))
        self._expenses.append(Expenses(4,300,"gas"))
        self._expenses.append(Expenses(11,200,"internet"))
        self._expenses.append(Expenses(11,50,"bills"))
        self._expenses.append(Expenses(17,400,"electricity"))
        self._expenses.append(Expenses(30,245,"kids"))
        self._expenses.append(Expenses(12,1000,"food"))
        self._expenses.append(Expenses(14,345,"car"))
        self._expenses.append(Expenses(12,600,"phone"))
        self._expenses.append(Expenses(23,800,"network"))

    """
    def add_10(self):
        types = ["rent", "gas", "internet", "bills", "electricity", "kids","food","car","phone","network"]
        expense = Expenses(random.randint(1, 32), random.randint(100, 1001), random.choice(types))
        self._expenses.append(expense)

    def get_all(self):
        return self._expenses

    def undo(self, liste):
        self._expenses=copy.deepcopy(liste)

    def remove(self, exp: int):
        self._expenses=list(filter(lambda x: (int(x.amount()) > exp) ,self._expenses))
