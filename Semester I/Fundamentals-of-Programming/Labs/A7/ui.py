from expenses_class import Expenses
def menu():
    print("Choose an option from below:")
    print("1. Add an expense")
    print("2. Display the list of expenses")
    print("3. Filter the list")
    print("4. Undo")
    print ("5. Exit")

def read_expense():
    day= input("Day: ")
    amount=input("Amount of money: ")
    name=input("Type of expense: ")

    if day.isdigit() and amount.isdigit() and int(day)<=30 and int(day)>=1 and int(amount)>=0:
        expense=Expenses(int(day), int(amount), name)
        return expense
    else:
        return False