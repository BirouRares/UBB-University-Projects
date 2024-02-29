from .memory_repository import *
import pickle
class BinaryRepository(MemoryRepository):
    def __init__(self, file_name: str):
        super(BinaryRepository, self).__init__()
        self._file_name=file_name
        self.read()

    def read(self):
        f = open(self._file_name, "rb")
        self._expenses=pickle.load(f)
        f.close()

    def add(self, expense):
        super(BinaryRepository,self).add(expense)
        self.write()
    def write(self,):
        f=open(self._file_name, "wb")
        pickle.dump(self._expenses,f)
        f.close()
    def remove(self, exp: int ):
        super(BinaryRepository,self).remove(exp)
        self.write()

    def get_all(self):
        return self._expenses

    def split_in_lines(self, exp: list):
        lines = []
        for s in exp:
            lines.append(f"{s.day()},{s.amount()},{s.name()}")
        return lines

    def undo(self, liste):
        super(BinaryRepository,self).undo(liste)
        self.write()

    def add_10(self):
        super(BinaryRepository,self).add_10()
        self.write()