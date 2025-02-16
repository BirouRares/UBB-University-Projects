from SymbolTable import SymbolTable, Pair

def main():
    symbol_table = SymbolTable(5)

    symbol_table.add("1")
    print(f"'1' added: {symbol_table.contains_term('1')}")
    print(f"Position of '1': {symbol_table.find_position_of_term('1')}")

    symbol_table.add("6")  # Will collide with '1' because they will have the same hash for size=5
    print(f"'6' added: {symbol_table.contains_term('6')}")
    print(f"Position of '6': {symbol_table.find_position_of_term('6')}")

    symbol_table.add("5")
    print(f"'5' added: {symbol_table.contains_term('5')}")
    print(f"Position of '5': {symbol_table.find_position_of_term('5')}")

    symbol_table.add("10")
    print(f"'10' added: {symbol_table.contains_term('10')}")
    print(f"Position of '10': {symbol_table.find_position_of_term('10')}")

    added_duplicate = symbol_table.add("1")
    print(f"Trying to add '1' again: {added_duplicate}")

    # Retrieve terms by their positions
    position_1 = symbol_table.find_position_of_term("1")
    if position_1:
        print(f"Term at position {position_1}: {symbol_table.find_by_pos(position_1)}")

    position_6 = symbol_table.find_position_of_term("6")
    if position_6:
        print(f"Term at position {position_6}: {symbol_table.find_by_pos(position_6)}")

    symbol_table.add("abc")
    symbol_table.add("def")
    print(f"'abc' added: {symbol_table.contains_term('abc')}")
    print(f"Position of 'abc': {symbol_table.find_position_of_term('abc')}")
    print(f"'def' added: {symbol_table.contains_term('def')}")
    print(f"Position of 'def': {symbol_table.find_position_of_term('def')}")

    long_string = "a" * 50
    symbol_table.add(long_string)
    print(f"Long string added: {symbol_table.contains_term(long_string)}")
    print(f"Position of long string: {symbol_table.find_position_of_term(long_string)}")

    symbol_table.add("12345")
    print(f"'12345' added: {symbol_table.contains_term('12345')}")
    print(f"Position of '12345': {symbol_table.find_position_of_term('12345')}")

    print("\nFinal hash table structure:")
    print(symbol_table)

if __name__ == "__main__":
    main()
