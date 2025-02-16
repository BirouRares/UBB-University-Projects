import sys
from domain.grammar import Grammar
from domain.parser import Parser

FILE_NAME = 'g1.txt'
GET_PRODUCTIONS_FOR = 'A'
SEQUENCE_G1 = 'abbc'
SEQUENCE = SEQUENCE_G1

OUTPUT_FILE = 'output.txt'
ERROR_FILE = 'message.txt'

def printBr():
    print('-----------------------------------------------------------------------------------------------------------')

class Console:
    def __init__(self):
        self.grammar = None
        self.parser = None

    def run(self):
        self.grammar = Grammar.fromFile(FILE_NAME)
        printBr()
        print('Non-terminals and Terminals:')
        print(self.grammar)
        printBr()
        print('Productions:')
        print(self.grammar.P)
        printBr()
        print('Productions for ' + GET_PRODUCTIONS_FOR + ':')
        print(self.grammar.getProductionsFor(GET_PRODUCTIONS_FOR))
        printBr()
        if self.grammar.isCFG:
            print('The grammar is CFG')
        else:
            print('The grammar is not CFG')
        printBr()
        print('Canonical Collection:')
        self.parser = Parser(grammar=self.grammar)
        self.parser.computeCanonicalCollection()
        self.parser.printCanonicalCollection()
        printBr()
        print('LR0 Table:')
        self.parser.computeTableActions()
        self.parser.printLr0Table()
        printBr()
        print('Parsing sequence: ' + SEQUENCE)
        self.parser.parseSequence(SEQUENCE)
        printBr()

if __name__ == '__main__':
    # ui = Console()
    # ui.run()
    # redirect the output to the files
    with open(OUTPUT_FILE, 'w') as output, open(ERROR_FILE, 'w') as error:
        sys.stdout = output
        sys.stderr = error

        try:
            ui = Console()
            ui.run()
        except Exception as e:
            print(f"An error occurred: {e}", file=sys.stderr)

        finally:
            sys.stderr = sys.__stderr__
            sys.stdout = sys.__stdout__
