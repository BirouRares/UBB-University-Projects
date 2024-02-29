from texttable import Texttable
class Board:
    def __init__(self):
        self.board = [[' ' for _ in range(7)] for _ in range(6)]
    def __getitem__(self, item):
        return self.board[item]

    def get_next_open_row(self, col):
        for row in range(5, -1, -1):
            if self.board[row][col] == ' ':
                return row
    def make_move(self, col, symbol):
        for row in range(5, -1, -1):
            if self.board[row][col] == ' ':
                self.board[row][col] = symbol
                return
    def check_win(self):
        # Check rows
        for row in range(6):
            for col in range(4):
                if self.board[row][col] == self.board[row][col + 1] == self.board[row][col + 2] == self.board[row][col + 3] != ' ':
                    return True
        # Check columns
        for row in range(3):
            for col in range(7):
                if self.board[row][col] == self.board[row + 1][col] == self.board[row + 2][col] == self.board[row + 3][col] != ' ':
                    return True
        # Check diagonals
        for row in range(3):
            for col in range(4):
                if self.board[row][col] == self.board[row + 1][col + 1] == self.board[row + 2][col + 2] == self.board[row + 3][col + 3] != ' ':
                    return True
                if self.board[row][col + 3] == self.board[row + 1][col + 2] == self.board[row + 2][col + 1] == self.board[row + 3][col] != ' ':
                    return True
        return False

    def check_draw(self):
        for row in range(6):
            for col in range(7):
                if self.board[row][col] == ' ':
                    return False
        return True

    def __str__(self):
        t=Texttable()
        header = ['1', '2', '3', '4', '5', '6', '7']
        t.header(header)

        for i in range(1,7):
            t.set_cols_dtype(['t'] * 7)
            t.add_row(self.board[i-1])
        return t.draw()
