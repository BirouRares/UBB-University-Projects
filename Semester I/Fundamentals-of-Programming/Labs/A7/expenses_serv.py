import copy
from src.expenses_class import Expenses

class Expenses_service:
    def __init__(self, repo):
        self._repository= repo
        self._operation = 0
        self._archive = []
        self._archive.append(copy.deepcopy(self._repository.get_all()))
    def add(self, exp: Expenses):
        self._repository.add(exp)
    def erase_expense(self, exp):

        v = self._repository.get_all()
        v = list(filter(lambda x: ( int(x.amount()) <= int(exp) ), v))
        for s in v:
            self._repository.remove(s.amount())

        self._operation =self._operation+1
        self._archive.append(copy.deepcopy(self._repository.get_all()))
    def getAll(self):
        return self._repository.get_all()
    def undo(self):
        self._operation -=1
        _ = self._archive.pop()
        self._repository.undo(copy.deepcopy(self._archive[len(self._archive)-1]))

    def clone(self):
        self._operation+=1
        self._archive.append(copy.deepcopy(self._repository.get_all()))



