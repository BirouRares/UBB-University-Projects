from Pair import Pair


class HashTable:
    def __init__(self, size):
        #I need a list of lists to store the elements
        self.size = size
        self.table = [[] for _ in range(size)]

    def hash(self, key):
        #Hash function: sum of the ASCII values of the characters of
        #the key modulo the size of the hash table
        sum_chars = sum(ord(c) for c in key)
        return sum_chars % self.size

    def add(self, term):
        if self.contains_term(term):
            return False

        pos = self.hash(term)
        self.table[pos].append(term)
        return True

    def contains_term(self, term):
        return self.find_position_of_term(term) is not None

    def find_position_of_term(self, term):
        pos = self.hash(term)
        if self.table[pos]:
            elems = self.table[pos]
            for i, elem in enumerate(elems):
                if elem == term:
                    return Pair(pos, i)
        return None

    def find_by_pos(self, pos):
        if pos.get_first() >= len(self.table) or pos.get_second() >= len(self.table[pos.get_first()]):
            raise IndexError("Invalid position")
        return self.table[pos.get_first()][pos.get_second()]

    def get_size(self):
        return self.size

    def __str__(self):
        return f"HashTable(size={self.size}, elements={self.table})"