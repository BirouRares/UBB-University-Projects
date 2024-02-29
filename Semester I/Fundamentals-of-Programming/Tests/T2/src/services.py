from repository import TextRepository
import random
class Serv:
    def __init__(self):
        self._repo = TextRepository()
        self._list= self._repo.read_file()#the list of players that we read from the file
    def sort(self):
        self._list.sort(key=lambda x: x.strength, reverse=True)#we sort the list by strength using sort function
        return self._list#retun the sorted list
    def len(self):#return the length of the list
        return len(self._list)
    def player_pair_qualifying(self):#here we pair the players
        self._list.sort(key=lambda x: x.strength, reverse=True)
        return self._list[0], self._list[1]
    def player_pair_random(self):#here we pair the players randomly
        p1= random.choice(self._list)
        self._list.remove(p1)
        p2= random.choice(self._list)
        self._list.remove(p2)

        return p1, p2