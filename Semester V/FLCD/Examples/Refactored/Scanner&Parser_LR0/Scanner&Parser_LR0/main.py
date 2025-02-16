from Grammar import Grammar
from Parser import Parser

if __name__ == '__main__':
    input_path = 'input/g1.in'
    grammar = Grammar.loadFromFile(input_path)

    # print(grammar)
    # print(grammar.validateCFG())
    # print('[===================================]\n\n')

    analyzer = Parser(grammar)
    stateCollection = analyzer.canonicalCollection()
    print('States:')
    for index, state in enumerate(stateCollection.nodes):
        print(f'#{index} {state}')
    print(f'State transitions: {stateCollection.connectionMap}')
    print('[===================================]\n\n')

    print(grammar.listOrderedProductions())
    print('Parsing table:')
    print(analyzer.getParsingTable())

    parse_result = []
    try:
        parse_tree = analyzer.parse(['a', 'b', 'b', 'c'])
        # parse_tree = analyzer.parse(['a', 'b', 'b', 'c', 'a'])
        # parse_tree = analyzer.parse(['int', 'e', 'e'])
        # parse_tree = analyzer.parse(['{', 'bool', 'identifier', ';', '}'])
        # parse_tree = analyzer.parse(['{', 'print', '(', 'identifier', '+', 'constant', ')', ';', '}'])
        for node in parse_tree:
            parse_result.append(f'{node.index}: {node.info}, {node.parent}, {node.rightSibling}')
        for result in sorted(parse_result, key=lambda x: int(x.split(':')[0])):
            print(result)
    except Exception as error:
        print(error)
