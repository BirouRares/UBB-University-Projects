class Expenses:
    def __init__(self, day: int, amount: int, name: str):
        self.__day=day
        self.__amount=amount
        self.__name=name

    @property
    def get_day(self):
        return self.__day

    @property
    def get_amount(self):
        return self.__amount

    @get_amount.setter
    def get_amount(self, amountn):
        self.__amount = amountn

    @property
    def get_name(self):
        return self.__name

    def amount(self):
        return self.__amount
    def day(self):
        return self.__day
    def name(self):
        return self.__name

    def __str__(self):
        return str(self.__day)+","+str(self.__amount)+","+str(self.__name)

def test():
    new_expense = Expenses(20, 100, "fun")
    assert new_expense.get_day == 20
    assert new_expense.get_amount == 100
    assert new_expense.get_name == "fun"
    assert str(new_expense) == "20,100,fun"

    new_expense.get_amount = 2000
    assert str(new_expense) == "20,2000,fun"
    print(new_expense.__dict__)

if __name__ == "__main__":
    test()