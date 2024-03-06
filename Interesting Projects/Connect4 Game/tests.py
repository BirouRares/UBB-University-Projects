import unittest
from board import Board
from player import HumanPlayer, AIPlayer

class Test(unittest.TestCase):
    def setUp(self) -> None:
        self.board = Board()
    def test(self):
        self.assertEqual(1, 1)
    def test_board(self):
        self.assertEqual(self.board.board, [[' ', ' ', ' ', ' ', ' ', ' ', ' '], [' ', ' ', ' ', ' ', ' ', ' ', ' '], [' ', ' ', ' ', ' ', ' ', ' ', ' '], [' ', ' ', ' ', ' ', ' ', ' ', ' '], [' ', ' ', ' ', ' ', ' ', ' ', ' '], [' ', ' ', ' ', ' ', ' ', ' ', ' ']])
    def test_get_next_open_row(self):
        self.assertEqual(self.board.get_next_open_row(0), 5)
    def test_drop_piece(self):
        self.board.make_move(0, 'X')
        self.assertEqual(self.board.board, [[' ', ' ', ' ', ' ', ' ', ' ', ' '], [' ', ' ', ' ', ' ', ' ', ' ', ' '], [' ', ' ', ' ', ' ', ' ', ' ', ' '], [' ', ' ', ' ', ' ', ' ', ' ', ' '], [' ', ' ', ' ', ' ', ' ', ' ', ' '], ['X', ' ', ' ', ' ', ' ', ' ', ' ']])
    def test_check_win(self):
        self.board.make_move(0, 'X')
        self.board.make_move(1, 'X')
        self.board.make_move(2, 'X')
        self.board.make_move(3, 'X')
        self.assertEqual(self.board.check_win(), True)
    def test_check_win2(self):
        self.board.make_move(0, 'X')
        self.board.make_move(1, 'X')
        self.board.make_move(2, 'X')
        self.assertEqual(self.board.check_win(), False)
    def test_check_win3(self):
        self.board.make_move(0, 'X')
        self.board.make_move(1, 'X')
        self.board.make_move(2, 'X')
        self.board.make_move(3, 'X')
        self.board.make_move(4, 'X')
        self.board.make_move(5, 'X')
        self.board.make_move(6, 'X')
        self.assertEqual(self.board.check_win(), True)

    def test_check_win4(self):
        self.board.make_move(0, 'O')
        self.board.make_move(1, 'O')
        self.board.make_move(2, 'O')
        self.board.make_move(3, 'O')
        self.assertEqual(self.board.check_win(), True)
    def test_check_win5(self):
        self.board.make_move(0, 'O')
        self.board.make_move(1, 'O')
        self.board.make_move(2, 'O')
        self.assertEqual(self.board.check_win(), False)
    def test_check_draw(self):
        #first column
        self.board.make_move(0, 'X')
        self.board.make_move(0, 'X')
        self.board.make_move(0, 'O')
        self.board.make_move(0, 'X')
        self.board.make_move(0, 'O')
        self.board.make_move(0, 'X')

        #second column
        self.board.make_move(1, 'X')
        self.board.make_move(1, 'X')
        self.board.make_move(1, 'O')
        self.board.make_move(1, 'X')
        self.board.make_move(1, 'O')
        self.board.make_move(1, 'X')

        #third column
        self.board.make_move(2, 'O')
        self.board.make_move(2, 'O')
        self.board.make_move(2, 'X')
        self.board.make_move(2, 'O')
        self.board.make_move(2, 'O')
        self.board.make_move(2, 'X')

        #fourth column
        self.board.make_move(3, 'O')
        self.board.make_move(3, 'O')
        self.board.make_move(3, 'X')
        self.board.make_move(3, 'O')
        self.board.make_move(3, 'X')
        self.board.make_move(3, 'O')

        #fifth column
        self.board.make_move(4, 'X')
        self.board.make_move(4, 'X')
        self.board.make_move(4, 'O')
        self.board.make_move(4, 'O')
        self.board.make_move(4, 'O')
        self.board.make_move(4, 'X')

        #sixth column
        self.board.make_move(5, 'O')
        self.board.make_move(5, 'X')
        self.board.make_move(5, 'O')
        self.board.make_move(5, 'X')
        self.board.make_move(5, 'O')
        self.board.make_move(5, 'X')

        #seventh column
        self.board.make_move(6, 'X')
        self.board.make_move(6, 'O')
        self.board.make_move(6, 'X')
        self.board.make_move(6, 'O')
        self.board.make_move(6, 'O')
        self.board.make_move(6, 'X')

        self.assertEqual(self.board.check_draw(), True)
    #test ai player
    def test_ai_player1(self):
        ai = AIPlayer('X')
        self.assertGreater(ai.get_move(self.board), -1)
    def test_ai_player2(self):
        ai = AIPlayer('X')
        self.assertLess(ai.get_move(self.board), 7)
    def test_human_player1(self):
        human = HumanPlayer('X')
        self.assertEqual(human.get_move(self.board), 0)


