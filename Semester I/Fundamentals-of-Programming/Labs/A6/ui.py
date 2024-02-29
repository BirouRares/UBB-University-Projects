# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here

import functions
import copy
def start_program():
    complexnumber_list = functions.make_random_complexnumber(10)
    undo_list= []
    functions.cloning(complexnumber_list,undo_list)
    while True:
        ok=False
        print()
        print("Please select what operation should execute:")
        opt=input(">")
        if opt=='exit':
            print("Take care!")
            return
        if opt=='list':
            ok = True
            if len(complexnumber_list)>0:
                functions.show_complexnumber(complexnumber_list)
            else:
                print("Empty list!")
        if opt=='undo':
            ok=True
            value=functions.und(complexnumber_list,undo_list)
            if value==0:
                print("No more undo!")
        else:
            if ' ' not in opt:
                pass
            else:
                comand,params =opt.split(" ", maxsplit=1)
                if comand=='add':
                    ok=True
                    try:
                        aux=params.replace("i","j")
                        complex_number = complex(aux)
                        real=int(complex_number.real)
                        img=int(complex_number.imag)
                        complexnumber=functions.list_new_complexnumber(real,img)
                        exists = functions.add_complexnumber(complexnumber_list, complexnumber)
                        if exists:
                            print("Complex number already exists!")
                        else:
                            functions.cloning(complexnumber_list, undo_list)
                            print("Complex number added successfully!")
                    except ValueError:
                        print("Wrong format for complex number!")


                if comand=='insert':
                    ok=True
                    ok1=True
                    ok2=True
                    if ' at ' not in params:
                        print("Wrong format for command!")
                        ok1=False
                    if ok1==True:
                        com,po=params.split(" at ")
                        l=len(po)
                        for i in range(0,l):
                            if po[i]<'0' or po[i]>'9':
                                ok2=False
                                break
                        if ok2==True:
                            try:
                                p=int(po)
                                aux=com.replace("i","j")
                                complex_number = complex(aux)
                                real=int(complex_number.real)
                                img=int(complex_number.imag)
                                complexnumber=functions.list_new_complexnumber(real,img)
                                if p<len(complexnumber_list):
                                    exists = functions.insert_complexnumber(p, complexnumber_list, complexnumber)
                                else:
                                    exists=True
                                if exists:
                                    print("Complex number was not inserted!")
                                else:
                                    functions.cloning(complexnumber_list, undo_list)
                                    print("Complex number added successfully!")
                            except ValueError:
                                print("Wrong format for complex number!")
                        else:
                            print("Wrong format for command!")


                if comand=='remove':
                    ok=True
                    try:
                        if ' to ' not in params:
                            if functions.number(params):
                                poz=int(params)
                                if poz<len(complexnumber_list):
                                    functions.delete(complexnumber_list, poz)
                                    functions.cloning(complexnumber_list, undo_list)
                                    print("Elemet removed successfully!")
                                else:
                                    print("Number does not exist!")
                            else:
                                print("Wrong format for command!")
                        else:
                            try:
                                st,en=params.split(" to ")
                                if functions.number(st) and functions.number(en):
                                    beg=int(st)
                                    fin=int(en)
                                    functions.delete2(complexnumber_list, beg, fin+1)
                                    functions.cloning(complexnumber_list, undo_list)
                                else:
                                    print("Wrong format for command!")
                            except ValueError:
                                print("Wrong format for command!")
                    except ValueError:
                        print("Wrong format for command!")

                if comand=='replace':
                    ok=True
                    if ' with ' not in params:
                        print("Wrong format for command!")
                    else:
                        try:
                            com1, com2 = params.split(" with ")
                            aux = com1.replace("i", "j")
                            complex_number = complex(aux)
                            real = int(complex_number.real)
                            img = int(complex_number.imag)
                            complexnumber1 = functions.list_new_complexnumber(real, img)

                            aux = com2.replace("i", "j")
                            complex_number = complex(aux)
                            real = int(complex_number.real)
                            img = int(complex_number.imag)
                            complexnumber2 = functions.list_new_complexnumber(real, img)

                            value=functions.replace_complex(complexnumber_list,complexnumber1,complexnumber2)
                            if value==0:
                                print("First complex number is not in the list!")
                            else:
                                functions.cloning(complexnumber_list, undo_list)
                                print("Complex number replaced successfully!")
                        except ValueError:
                            print("Wrong format for command!")
                if comand=='list':
                    ok=True
                    try:
                        fct, rest=params.split(" ", maxsplit=1)
                        if fct=='real':
                            if ' to ' not in rest:
                                print("Wrong format for command!")
                            else:
                                com1, com2=rest.split(" to ")
                                if functions.number(com1) and functions.number(com2):
                                    nr1=int(com1)
                                    nr2=int(com2)
                                    val=functions.list_real(complexnumber_list,nr1,nr2)
                                    if val==0:
                                        print("Second value is to big!")
                                else:
                                    print("Wrong format for command!")
                        elif fct=='modulo':
                            l=len(rest)
                            ce=False
                            for i in range (0,l):
                                if rest[i]=='<' and rest[i+1]==' ':
                                    ce=True
                                    break
                                if rest[i]=='=' and rest[i+1]==' ':
                                    ce=True
                                    break
                                if rest[i]=='>' and rest[i+1]==' ':
                                    ce=True
                                    break
                            if ce==False:
                                print("Wrong format for command!")
                            else:
                                com1, com2 = rest.split(" ")
                                if functions.number(com2):
                                    nr=int(com2)
                                    if com1=='<':
                                        x=1
                                    if com1=='=':
                                        x=2
                                    if com1=='>':
                                        x=3
                                    functions.list_modul(complexnumber_list, x , nr)
                                else:
                                    print("Wrong format for command!")
                        else:
                            print("Wrong format for command!")
                    except ValueError:
                        print("Wrong format for command!")

                if comand=='filter':
                    ok=True
                    try:
                        if params == 'real':
                            functions.filter_real(complexnumber_list)
                            functions.cloning(complexnumber_list, undo_list)
                        elif 'modulo ' in params:
                            fct, rest = params.split(" ", maxsplit=1)
                            l = len(rest)
                            ce = False
                            for i in range(0, l):
                                if rest[i] == '<' and rest[i + 1] == ' ':
                                    ce = True
                                    break
                                if rest[i] == '=' and rest[i + 1] == ' ':
                                    ce = True
                                    break
                                if rest[i] == '>' and rest[i + 1] == ' ':
                                    ce = True
                                    break
                            if ce == False:
                                print("Wrong format for command!")
                            else:
                                com1, com2 = rest.split(" ")
                                if functions.number(com2):
                                    nr = int(com2)
                                    if com1 == '<':
                                        x = 1
                                    if com1 == '=':
                                        x = 2
                                    if com1 == '>':
                                        x = 3
                                    functions.filter_modul(complexnumber_list, x, nr)
                                    functions.cloning(complexnumber_list, undo_list)
                                else:
                                    print("Wrong format for command!")
                        else:
                            print("Wrong format for command!")
                    except ValueError:
                        print("Wrong format for command!")
        if ok==False:
            print("Wrong format for the commnad!")