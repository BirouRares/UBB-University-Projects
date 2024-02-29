from memory_repository import *
from src.expenses_class import *

def test_add():
    repo = MemoryRepository()

    exp = Expenses(1,200,"Test")
    repo.add(exp)
    exp2=exp
    exp = repo.get_all()


    assert exp[0] == exp2

def test_get_all():
    repo = MemoryRepository()

    exp1 = Expenses(1, 200, "Test1")
    exp2 = Expenses(2, 400, "Test2")
    exp_exp=[exp1,exp2]

    repo.add(exp1)
    repo.add(exp2)
    exp_actual=repo.get_all()

    assert exp_actual[0] == exp_exp[0] and exp_actual[1] == exp_exp[1]

#test_add()
#test_get_all()