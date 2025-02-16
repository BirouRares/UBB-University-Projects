from Grammar import Grammar
from Parser import Parser

if __name__ == '__main__':
    input_file = 'g3.txt'
    # input_file = 'g1.txt'
    # input_file = 'g2.txt'


    grammar = Grammar.fromFile(input_file)

    print(grammar.N)
    print(grammar.E)
    print(grammar.P)
    print(grammar.S)

    print(grammar.checkIfCFG())
    print('\n\n')

    parser = Parser(grammar)
    canonicalCollection = parser.canonicalCollection()
    print('states:')
    for i, s in enumerate(canonicalCollection.states):
        print(f'#{i} {s}')
    print('\n')
    print(f'state transitions: {canonicalCollection.adjacencyList}')

    print(grammar.getOrderedProductions())

