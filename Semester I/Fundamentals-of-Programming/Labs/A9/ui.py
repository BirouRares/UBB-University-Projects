from board import Board
from player import HumanPlayer, AIPlayer


class Game:
    def __init__(self):
        self.board = Board()
        self.player1 = HumanPlayer('X')
        self.player2 = AIPlayer('O')
        self.current_player = self.player1

    def play(self):
        while not self.board.check_win() and not self.board.check_draw():
            print("\n",self.board)
            move = self.current_player.get_move(self.board)
            self.board.make_move(move, self.current_player.symbol)
            if self.current_player == self.player2:
                print("\n","Computer move: ", move+1)
            self.current_player = self.player2 if self.current_player == self.player1 else self.player1

        if self.board.check_win():
            print("\n",self.board,"\n")
            self.current_player = self.player2 if self.current_player == self.player1 else self.player1
            print(f'{self.current_player.symbol} wins!')
        else:
            print("\n",self.board,"\n")
            print("It's a draw!")

if __name__ == '__main__':
    game = Game()
    game.play()