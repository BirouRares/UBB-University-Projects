import copy
import json
import ui
from expenses_class import *
from Repositories.memory_repository import *
from Repositories.textfile_repository import *
from expenses_serv import *
from src import expenses_serv
from src.Repositories.binaryfile_repository import BinaryRepository


def start():
    f=open("package.json", "r")
    settings = json.load(f)
    repoType = settings["RepositoryType"].lower()
    repository = MemoryRepository()

    if repoType == "memory":
        repository = MemoryRepository()
        nr=10
        while nr>0:
            nr-=1
            repository.add_10()

    elif repoType == "textfile":
        file_name = settings["FileName"]
        repository = TextFileRepository(file_name)
    elif repoType=="binary":
        file_name = settings["FileName"]
        repository=BinaryRepository(file_name)
        """
        nr = 10
        while nr > 0:
            nr -= 1
            repository.add_10()
        """

    expenses_serv=Expenses_service(repository)

    while True:
        ui.menu()
        opt=input(">")

        if opt.isdigit() !=True:
            print("Invalid command")
        else:
            opt=int(opt)
            if opt == 5:
                return

            if opt<1 or opt>5:
                print("Wrong command, write something else \n")

            if opt==1:
                expense=ui.read_expense()
                if expense :
                    repository.add(expense)
                    expenses_serv.clone()
                else:
                    print("Invalid data!\n")

            if opt==2:
                exp = repository.get_all()
                for i in exp:
                    print(i)
                print()
            if opt==3:
                sum = input("Enter amount: ")
                if sum.isdigit():
                    expenses_serv.erase_expense(int(sum))
                else:
                    print("Invalid data!\n")
            if opt==4:
                if expenses_serv._operation==0:
                    print("No more undo to be done! We are back to origin!\n")
                else:
                    expenses_serv.undo()
start()