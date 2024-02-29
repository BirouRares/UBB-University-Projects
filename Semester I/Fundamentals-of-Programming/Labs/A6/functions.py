#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions.

import math
import random
import copy
from sys import maxsize
import cmath


def add_complexnumber(complexnumbers_list: list, new_complexnumber):
    if new_complexnumber in complexnumbers_list:
        return 1
    complexnumbers_list.append(new_complexnumber)
    return 0


def insert_complexnumber(poz: int, complexnumbers_list: list, new_complexnumber):
    if new_complexnumber in complexnumbers_list:
        return 1
    complexnumbers_list.insert(poz, new_complexnumber)
    return 0


def list_new_complexnumber(re, im: int):
    return [re, im]


def list_get_real(complexnumber):
    return complexnumber[0]


def list_get_imaginary(complexnumber):
    return complexnumber[1]

def cloning(li1, undo_list: list):
    undo_list.append(copy.copy(li1))

def und(li1, undo_list: list):
    undo_list.pop()
    if len(undo_list)>=1:
        li1.clear()
        #print(undo_list[len(undo_list) - 1])
        #li1=(undo_list[len(undo_list) - 1]).copy()
        n=len(undo_list)
        m=len(undo_list[n-1])
        for i in range (0,m):
            re=list_get_real(undo_list[n-1][i])
            im=list_get_imaginary(undo_list[n-1][i])
            li1.append(list_new_complexnumber(re, im))
        return 1
    else:
        return 0

def make_random_complexnumber(count: int):
    assert count < 50 ** 2
    complexnumbers_list = []
    img = list(range(-25, 25))
    real = list(range(-25, 25))
    while count > 0:
        re = random.choice(real)
        im = random.choice(img)
        real.remove(re)
        img.remove(im)
        complexnumbers_list.append(list_new_complexnumber(re, im))
        count = count - 1
    return complexnumbers_list


def list_to_str(complexnumber):
    return "z=" + str(complexnumber[0]) + "+(" + str(complexnumber[1]) + "*i)"


def show_complexnumber(complexnumbers_list: list):
    print("List of complex numbers is:\n" + ",\n".join(map(list_to_str, complexnumbers_list)))


def number(s):
    l = len(s)
    ok = True
    for i in range(0, l):
        if s[i] < '0' or s[i] > '9':
            ok = False
            break
    return ok


def delete(complexnumbers_list: list, start):
    del complexnumbers_list[start]

def delete2(complexnumbers_list: list, start, end):
    del complexnumbers_list[start:end]

def replace_complex(complexnumbers_list: list, com1, com2):
    if com1 not in complexnumbers_list:
        return 0
    l = len(complexnumbers_list)
    for i in range(0, l):
        if complexnumbers_list[i] == com1:
            complexnumbers_list[i] = com2
    return 1


def list_real(complexnumbers_list: list, start, end):
    ok = True
    l = len(complexnumbers_list)
    if end >= l:
        return 0
    for i in range(start, end + 1):
        img = list_get_imaginary(complexnumbers_list[i])
        if img == 0:
            ok = False
            print(list_to_str(complexnumbers_list[i]))
    if ok == True:
        print("There is no complex number with imaginary part = 0")
    return 1


def calculate_modulus(complexnumbers_list, index):
    real = list_get_real(complexnumbers_list[index])
    img = list_get_imaginary(complexnumbers_list[index])
    real = real * real
    img = img * img
    return math.sqrt(real + img)


def list_modul(complexnumbers_list: list, sign, val):
    ok=False
    l = len(complexnumbers_list)
    for i in range(0, l):
        nr = calculate_modulus(complexnumbers_list, i)
        if sign == 1 and nr < val:
            ok=True
            print(list_to_str(complexnumbers_list[i]))
        if sign == 2 and nr == val:
            ok = True
            print(list_to_str(complexnumbers_list[i]))
        if sign == 3 and nr > val:
            ok = True
            print(list_to_str(complexnumbers_list[i]))
    if ok==False:
        print("None")

def while_img0(complexnumbers_list: list):
    for i in range(0, len(complexnumbers_list)):
        if list_get_imaginary(complexnumbers_list[i])!=0:
            return 1
    return 0
def filter_real(complexnumbers_list: list):
    while while_img0(complexnumbers_list):
        for i in range(0, len(complexnumbers_list)):
            img = list_get_imaginary(complexnumbers_list[i])
            if img != 0:
                del complexnumbers_list[i]
                break

def while_sign(complexnumbers_list: list, sign, val):
    for i in range(0, len(complexnumbers_list)):
        nr = calculate_modulus(complexnumbers_list, i)
        if sign == 1 and nr >= val:
            return 1
        if sign == 2 and nr != val:
            return 1
        if sign == 3 and nr <= val:
            return 1
    return 0

def filter_modul(complexnumbers_list: list, sign, val):
    while while_sign(complexnumbers_list, sign, val):
        l = len(complexnumbers_list)
        for i in range(0, l):
            nr = calculate_modulus(complexnumbers_list, i)
            if sign == 1 and nr >= val:
                del complexnumbers_list[i]
                break
            if sign == 2 and nr != val:
                del complexnumbers_list[i]
                break
            if sign == 3 and nr <= val:
                del complexnumbers_list[i]
                break
