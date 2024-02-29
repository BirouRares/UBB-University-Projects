from src.expenses_class import Expenses
from .memory_repository import MemoryRepository


class TextFileRepository(MemoryRepository):
    def __init__(self, file_name: str):
        super(TextFileRepository, self).__init__()
        self._file_name = file_name

    def add(self, expense):
        expenses = self.get_all()
        expenses.append(expense)
        self.write(expenses)

    def remove(self, exp: int):
        expenses = self.get_all()
        expenses = list(filter(lambda x: (int(x.amount()) > exp), expenses))
        self.write(expenses)

    def get_all(self):
        output = []
        file = open(self._file_name, 'r')

        lines = file.read()
        lines = lines.splitlines()
        for l in lines:
            values = l.split(',')
            exp = Expenses(int(values[0]), int(values[1]), values[2])
            output.append(exp)

        file.close()
        return output

    def split_in_lines(self, exp: list):
        lines = []
        for s in exp:
            lines.append(f"{s.day()},{s.amount()},{s.name()}")
        return lines

    def write(self, exp: list):
        file = open(self._file_name, "w")

        lines = self.split_in_lines(exp)

        for l in lines:
            file.write(l)
            file.write("\n")

        file.close()

    def undo(self, liste):
        self.write(liste)