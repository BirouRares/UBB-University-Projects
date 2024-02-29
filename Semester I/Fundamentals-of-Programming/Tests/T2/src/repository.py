from domain import Player
class TextRepository():
    def __init__(self):
        self._list=[]
        self._file_name = "players.txt"

    def read_file(self):#here we read the file
        output = []
        file = open("players.txt", "r") # open the file
        for line in file:
            line = line.split(',')
            id = int(line[0])
            name = str(line[1])
            strenght = int(line[2])
            play = Player(id, name, strenght)
            output.append(play)#we append the player to the list
        file.close() # close the file
        return output  #return the list of players that we read

    def split_in_lines(self, exp: list):#here we split the list in lines having a comma between the elements
        lines = []
        for s in exp:
            lines.append(f"{s.day()},{s.amount()},{s.name()}")
        return lines
    def write_file(self):
        file = open("players.txt.txt", "w")
        for i in range(0, len(self._list)):
            file.write(str(self._list[i]))
            file.write("\n")
        file.close()






