class Grammar:
    startSymbol = 'Start0'

    @staticmethod
    def processLine(line) -> list[str]:
        return [item.strip() for item in line.split('$')[1].strip().split('#')[0].strip().split(' ')]

    @staticmethod
    def loadFromFile(filePath) -> 'Grammar':
        with open(filePath) as file:
            nonTerminals = Grammar.processLine(file.readline())
            terminals = Grammar.processLine(file.readline())
            start = file.readline().split('=')[1].strip()
            rules = Grammar.extractRules([line.strip() for line in file][1:-1])

            return Grammar(nonTerminals, terminals, rules, start)

    @staticmethod
    def extractRules(lines):
        result = []

        for line in lines:
            lhs, rhs = line.split('->')
            lhs = lhs.strip().split(' ')
            rhs = [alt.split(' ') for alt in [part.strip() for part in rhs.split('|')]]

            result.append((lhs, rhs))

        return result

    def __init__(self, nonTerminals: list[str], terminals: list[str], rules: list[tuple[list[str], list[list[str]]]], start: str):
        self.nonTerminals: list[str] = nonTerminals
        self.terminals: list[str] = terminals
        self.rules: list[tuple[list[str], list[list[str]]]] = rules
        self.start: str = start

    def isSymbolNonTerminal(self, symbol):
        return symbol in self.nonTerminals

    def isSymbolTerminal(self, symbol):
        return symbol in self.terminals

    def fetchProductionsFor(self, nonTerminal):
        if not self.isSymbolNonTerminal(nonTerminal):
            raise Exception(f'Only productions for non-terminals are allowed: {nonTerminal} is not valid.')
        return [rule for rule in self.rules if rule[0][0] == nonTerminal]

    def displayProductionsFor(self, nonTerminal):
        productions = self.fetchProductionsFor(nonTerminal)
        print(', '.join([' -> '.join(prod) for prod in productions]))

    def listOrderedProductions(self) -> list[tuple[list[str], list[list[str]]]]:
        orderedList: list[tuple[list[str], list[list[str]]]] = []
        for rule in self.rules:
            for rhs in rule[1]:
                orderedList.append((rule[0], rhs))
        return orderedList

    def validateCFG(self):
        startSymbolFound = False

        for rule in self.rules:
            lhs, rhs = rule
            for leftSymbol in lhs:
                if self.start == leftSymbol:
                    startSymbolFound = True
                    break
            if startSymbolFound:
                break

        if not startSymbolFound:
            return False

        for rule in self.rules:
            lhs, rhs = rule
            if len(lhs) > 1:
                return False
            for leftSymbol in lhs:
                if leftSymbol not in self.nonTerminals:
                    return False

            for rhsList in rhs:
                for symbol in rhsList:
                    if not (symbol in self.nonTerminals or symbol in self.terminals or symbol == 'epsilon'):
                        return False

        return True

    def enrichGrammar(self) -> 'Grammar':
        if self.start == Grammar.startSymbol:
            raise Exception('The grammar is already enriched.')
        enrichedGrammar = Grammar(self.nonTerminals, self.terminals, self.rules, Grammar.startSymbol)
        enrichedGrammar.nonTerminals.append(Grammar.startSymbol)
        enrichedGrammar.rules.append(([Grammar.startSymbol], [[self.start]]))
        return enrichedGrammar

    def __str__(self):
        rulesStr = ''
        for rule in self.rules:
            lhsStr = ' '.join(rule[0])
            rhsStr = ''
            for rhs in rule[1]:
                rhsStr += ' '.join(rhs) + ' | '
            rhsStr = rhsStr[:-2]
            rulesStr += '\t' + lhsStr + ' -> ' + rhsStr + '\n'
        return 'Non-Terminals = { ' + ', '.join(self.nonTerminals) + ' }\n' \
               + 'Terminals = { ' + ', '.join(self.terminals) + ' }\n' \
               + 'Rules = {\n' + rulesStr + '}\n' \
               + 'Start = ' + str(self.start) + '\n'
