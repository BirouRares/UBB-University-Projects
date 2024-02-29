"""
Problem A:Length and elements of a longest subarray of numbers having the same modulus.
Problem B:The length and elements of a maximum subarray sum, when considering each number's real part
"""
import math
import random
from sys import maxsize


# Functions to deal with imaginary numbers - dictionary representation + functions:

def dict_new_complexnumber(re, im: int):
    return {"re": re, "im": im}

def dict_get_real(complexnumber):
    return complexnumber["re"]

def dict_get_imaginary(complexnumber):
    return complexnumber["im"]

def dict_to_str(complexnumber):
    return "z=" + str(complexnumber["re"]) + str(complexnumber["im"]) + "*i"

# Generating, adding and deleting functions:

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
        complexnumbers_list.append(dict_new_complexnumber(re, im))
        count =count-1
    return complexnumbers_list


def add_complexnumber(complexnumbers_list: list, new_complexnumber):
    if new_complexnumber in complexnumbers_list:
        return 1
    complexnumbers_list.append(new_complexnumber)
    return 0


def delete_complexnumber(complexnumbers_list: list, complexnumber):
    if complexnumber not in complexnumbers_list:
        return 1
    complexnumbers_list.remove(complexnumber)
    return 0


def calculate_modulus(complexnumbers_list, index):
    #Calculate the module of a complex number z=a+b*i => |z|=sqrt(a^2+b^2)
    #In order to have a much precise compariosn we are going to return the modulus^2
    real=dict_get_real(complexnumbers_list[index])
    img=dict_get_imaginary(complexnumbers_list[index])
    real=real*real
    img=img*img
    return real+img


def set_a(complexnumbers_list: list):
    #Length and elements of a longest subarray of numbers having the same modulus.

    modulus = [None] * len(complexnumbers_list)
    for i in range(0, len(complexnumbers_list)):
        modulus[i] = calculate_modulus(complexnumbers_list, i)
    write_listofmodulus(modulus)
    n = len(modulus)
    poz = 0
    lmax = 1
    v = []
    while poz < n:
        p = poz
        while poz + 1 < n and modulus[poz] == modulus[poz + 1]:
            poz += 1
        if poz - p + 1 > lmax:
            lmax = poz - p + 1
            v = complexnumbers_list[p:poz + 1]
        poz += 1
    write_setA(v)


def set_b(complexnumbers_list: list):
    max_so_far = -maxsize - 1
    max_ending_here = 0
    st = 0
    sf = 0
    s = 0
    for i in range(0, len(complexnumbers_list)):
        max_ending_here += int(dict_get_real(complexnumbers_list[i]))
        if max_so_far < max_ending_here:
            max_so_far = max_ending_here
            st = s
            sf = i
        if max_ending_here < 0:
            max_ending_here = 0
            s = i + 1
    write_setB(max_so_far, st, sf, complexnumbers_list)

# Function for UI:

def write_listofmodulus(list_modulus):
    print("The list of modulus is:")
    for i in range(0, len(list_modulus)):
        print("{0:.2f}".format(math.sqrt(list_modulus[i])), end="  ")
    print()


def write_setA(res):
    print("The lenght of the longest subarray of numbers having the same modulus is: " + str(len(res)))
    for i in range(0, len(res)):
        print(res[i], end=" ")


def write_setB(Max, start, end, complexnumbers_list):
    print("Maximum sum is " + str(Max))
    for i in range(start, end + 1):
        print(dict_get_real(complexnumbers_list[i]), end=" ")


def read_complexnumber(complexnumbers_list):
    print()
    real = int(input("Real part:"))
    img = int(input("Imaginary part:"))
    return dict_new_complexnumber(real, img) # Add the number to the list


def show_complexnumber(complexnumbers_list: list):
    print("List of complex numbers is:\n" + ",\n".join(map(dict_to_str, complexnumbers_list)))


def start():
    complexnumber_list = make_random_complexnumber(10)
    while True:
        print()
        print("Please select what operation should execute:")
        print()
        print("1.Add a complex number")
        print("2.Show the list of complex numbers:")
        print("3.Resolve the task from set A")
        print("4.Resolve the task from set B")
        print("5.Exit the program")
        opt = input("Your option is: ")
        if opt == "1":
            complexnumber = read_complexnumber(complexnumber_list)
            exists = add_complexnumber(complexnumber_list, complexnumber)
            if exists:
                print("Complex number already exists")
            else:
                print("Complex number added successfully")
        elif opt == "2":
            show_complexnumber(complexnumber_list)
        elif opt == "3":
            print()
            print("Set A:")
            print("Length and elements of a longest subarray of numbers having the same modulus:")
            set_a(complexnumber_list)

        elif opt == "4":
            print()
            print("Set B")
            print("The length and elements of a maximum subarray sum, when considering each number's real part")
            set_b(complexnumber_list)
        elif opt == "5":
            print("Take care!")
            return False
        else:
            print("Wrong commnad, please type from the ones listed above")
start()
"""
# Functions to deal with imaginary numbers - list representation + functions:

def list_new_complexnumber(re, im: int):
    return [re, im]

def list_get_real(complexnumber):
    return complexnumber[0]

def list_get_imaginary(complexnumber):
    return complexnumber[1]

def list_to_str(complexnumber):
    return "z=" + str(complexnumber[0]) + "+(" + str(complexnumber[1]) + "*i)"

# Generating, adding and deleting functions:

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
        count =count-1
    return complexnumbers_list


def add_complexnumber(complexnumbers_list: list, new_complexnumber):
    if new_complexnumber in complexnumbers_list:
        return 1
    complexnumbers_list.append(new_complexnumber)
    return 0


def delete_complexnumber(complexnumbers_list: list, complexnumber):
    if complexnumber not in complexnumbers_list:
        return 1
    complexnumbers_list.remove(complexnumber)
    return 0


def calculate_modulus(complexnumbers_list, index):
    #Calculate the module of a complex number z=a+b*i => |z|=sqrt(a^2+b^2)
    #In order to have a much precise compariosn we are going to return the modulus^2
    real=list_get_real(complexnumbers_list[index])
    img=list_get_imaginary(complexnumbers_list[index])
    real=real*real
    img=img*img
    return real+img


def set_a(complexnumbers_list: list):
    #Length and elements of a longest subarray of numbers having the same modulus.

    modulus = [None] * len(complexnumbers_list)
    for i in range(0, len(complexnumbers_list)):
        modulus[i] = calculate_modulus(complexnumbers_list, i)
    write_listofmodulus(modulus)
    n = len(modulus)
    poz = 0
    lmax = 1
    v = []
    while poz < n:
        p = poz
        while poz + 1 < n and modulus[poz] == modulus[poz + 1]:
            poz += 1
        if poz - p + 1 > lmax:
            lmax = poz - p + 1
            v = complexnumbers_list[p:poz + 1]
        poz += 1
    write_setA(v)


def set_b(complexnumbers_list: list):
    max_so_far = -maxsize - 1
    max_ending_here = 0
    st = 0
    sf = 0
    s = 0
    for i in range(0, len(complexnumbers_list)):
        max_ending_here += int(list_get_real(complexnumbers_list[i]))
        if max_so_far < max_ending_here:
            max_so_far = max_ending_here
            st = s
            sf = i
        if max_ending_here < 0:
            max_ending_here = 0
            s = i + 1
    write_setB(max_so_far, st, sf, complexnumbers_list)

# Function for UI:

def write_listofmodulus(list_modulus):
    print("The list of modulus is:")
    for i in range(0, len(list_modulus)):
        print("{0:.2f}".format(math.sqrt(list_modulus[i])), end="  ")
    print()


def write_setA(res):
    print("The lenght of the longest subarray of numbers having the same modulus is: " + str(len(res)))
    for i in range(0, len(res)):
        print(res[i], end=" ")


def write_setB(Max, start, end, complexnumbers_list):
    print("Maximum sum is " + str(Max))
    for i in range(start, end + 1):
        print(list_get_real(complexnumbers_list[i]), end=" ")


def read_complexnumber(complexnumbers_list):
    print()
    real = int(input("Real part:"))
    img = int(input("Imaginary part:"))
    return list_new_complexnumber(real, img) # Add the number to the list


def show_complexnumber(complexnumbers_list: list):
    print("List of complex numbers is:\n" + ",\n".join(map(list_to_str, complexnumbers_list)))


def start():
    complexnumber_list = make_random_complexnumber(10)
    while True:
        print()
        print("Please select what operation should execute:")
        print()
        print("1.Add a complex number")
        print("2.Show the list of complex numbers:")
        print("3.Problem from set A")
        print("4.Problem from set B")
        print("5.Close the program")
        opt = input("Your option is: ")
        if opt == "1":
            complexnumber = read_complexnumber(complexnumber_list)
            exists = add_complexnumber(complexnumber_list, complexnumber)
            if exists:
                print("Complex number already exists")
            else:
                print("Complex number added successfully")
        elif opt == "2":
            show_complexnumber(complexnumber_list)
        elif opt == "3":
            print()
            print("Set A:")
            print("Length and elements of a longest subarray of numbers having the same modulus:")
            set_a(complexnumber_list)

        elif opt == "4":
            print()
            print("Set B:")
            print("The length and elements of a maximum subarray sum, when considering each number's real part:")
            set_b(complexnumber_list)
        elif opt == "5":
            print("Take care!")
            return False
        else:
            print("Wrong commnad, please type from the ones listed above")
start()
"""