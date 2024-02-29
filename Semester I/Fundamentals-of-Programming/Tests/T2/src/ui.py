from services import Serv
class UI:
    def __init__(self):
        self._serv = Serv()
    def start(self):#here we start the program
        v=self._serv.sort()
        print("\n")
        print("The players sorted by strength are:")
        for i in range(0, len(v)):
            print(v[i])
        print("\n")
        def is_power_of_two(n):
            return (n & (n - 1) == 0 and n != 0)
        def previous_power_of_two(n):
            return 2 ** (n.bit_length() - 1)

        if not is_power_of_two(self._serv.len()):
            print("Qualification round")
            print("Need to eliminate", self._serv.len() - previous_power_of_two(self._serv.len()), "players")


        elif self._serv.len() == 2:
            print("Final")
        elif self._serv.len() == 4:
            print("Last 4")
        elif self._serv.len() == 8:
            print("Last 8")
        elif self._serv.len() == 16:
            print("Last 16")
ui=UI()
ui.start()
