import random
from board import Board
class Player:
    def __init__(self, symbol):
        self.symbol = symbol

class HumanPlayer(Player):
    def get_move(self, board):
        while True:
            try:
                move = int(input("\n" f'{self.symbol}, choose a column (1-7): ')) - 1
                if move > 6 or move < 0:
                    print("Invalid input, try again.")
                    continue
                elif board.board[0][move] != ' ':
                    print("Column is full, try again.")
                    continue
                return move
            except ValueError:
                print("Invalid input, try again.")
"""
class AIPlayer(Player):
    def __init__(self, symbol):
        super().__init__(symbol)

    def get_move(self, board):
        best_score = float('-inf')
        best_col = None

        for col in range(7):
            if board.board[0][col] != ' ':
                continue
            row = board.get_next_open_row(col)
            board.board[row][col] = self.symbol
            score = self.minimax(board, 0, False)
            board.board[row][col] = ' '
            if score > best_score:
                best_score = score
                best_col = col
        return best_col

    def minimax(self, board, depth, is_maximizing):
        if depth == 6 or board.check_win():
            if board.check_win():
                if is_maximizing:
                    return -1
                else:
                    return 1
            else:
                return 0

        if is_maximizing:
            best_score = float('-inf')
            for col in range(7):
                if board.board[0][col] != ' ':
                    continue
                row = board.get_next_open_row(col)
                board.board[row][col] = self.symbol
                score = self.minimax(board, depth + 1, False)
                board.board[row][col] = ' '
                best_score = max(score, best_score)
            return best_score
        else:
            best_score = float('inf')
            for col in range(7):
                if board.board[0][col] != ' ':
                    continue
                row = board.get_next_open_row(col)
                board.board[row][col] = 'X' if self.symbol == 'O' else 'O'
                score = self.minimax(board, depth + 1, True)
                board.board[row][col] = ' '
                best_score = min(score, best_score)
            return best_score
"""
class AIPlayer(Player):
    def __init__(self, symbol):
        super().__init__(symbol)
        #self.board = Board()
    def get_move(self, board):
        #0-6 return values
        #check rows to win
        for row in range(6):
            for col in range(4):
                if board.board[row][col] == board.board[row][col + 1] == board.board[row][col + 2] == 'O' and board.board[row][col + 3] == ' ':
                    return col + 3
        #check columns to win
        for row in range(4):
            for col in range(7):
                if board.board[row][col] == board.board[row + 1][col] == board.board[row + 2][col] == 'O' and board.board[row-1][col] == ' ':
                    return col
        #check diagonals to win
        for row in range(3):
            for col in range(4):
                if board.board[row][col] == board.board[row + 1][col + 1] == board.board[row + 2][col + 2] == 'O' and board.board[row + 2][col + 3] != ' ' and board.board[row - 1][col - 1] == ' ':
                    return col+3
                if board.board[row][col + 3] == board.board[row + 1][col + 2] == board.board[row + 2][col + 1] == 'O' and board.board[row + 2][col] != ' ' and board.board[row - 1][col + 4] == ' ':
                    return col


        #check rows to block
        for row in range(6):
            for col in range(4):
                if board.board[row][col] == board.board[row][col + 1] == board.board[row][col + 2] == 'X' and board.board[row][col + 3] == ' ':
                    return col + 3
        #check columns block
        for row in range(4):
            for col in range(7):
                if board.board[row][col] == board.board[row + 1][col] == board.board[row + 2][col] == 'X' and board.board[row-1][col] == ' ':
                    return col
        #check diagonals to block
        for row in range(3):
            for col in range(4):
                if board.board[row][col] == board.board[row + 1][col + 1] == board.board[row + 2][col + 2] == 'X' and board.board[row + 2][col + 3] != ' ' and board.board[row - 1][col - 1] == ' ':
                    return col+3
                if board.board[row][col + 3] == board.board[row + 1][col + 2] == board.board[row + 2][col + 1] == 'X' and board.board[row + 2][col] != ' ' and board.board[row - 1][col + 4] == ' ':
                    return col

        #if no win or block, play random
        numar=random.randint(0,6)
        while board.board[0][numar] != ' ':
            numar=random.randint(0,6)
        return numar