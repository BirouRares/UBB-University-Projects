from Row import Row


class Table:
    def __init__(self):
        self.tableRow: dict[int, Row] = {}

    def __str__(self) -> str:
        return '\n'.join(f'{rowIndex}: {str(row)}' for rowIndex, row in sorted(self.tableRow.items()))
