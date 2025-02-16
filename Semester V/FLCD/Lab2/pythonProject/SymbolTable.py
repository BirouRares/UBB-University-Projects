from HashTable import HashTable
from Pair import Pair


class SymbolTable:
    def __init__(self, size):
        self.hash_table = HashTable(size)

    def find_by_pos(self, pos):
        return self.hash_table.find_by_pos(pos)

    def add(self, term):
        return self.hash_table.add(term)

    def contains_term(self, term):
        return self.hash_table.contains_term(term)

    def find_position_of_term(self, term):
        return self.hash_table.find_position_of_term(term)

    def get_size(self):
        return self.hash_table.get_size()

    def __str__(self):
        return str(self.hash_table)