import functions

def start():
    flight_list=[]
    functions.create_list(flight_list)
    while True:
        print()
        print("1.Add a flight")
        print("2.Delete a flight")
        print("3.Show all flights with a given departure city")
        print("4.Delay")
        print("5.Exit")
        opt=input(">>>")
        if opt=='5':
            print("Take care!")
            return
        if opt=='1':
            try:
                print("Enter the code:")
                code = input(">")
                print("Enter the duration:")
                duration = int(input(">"))
                print("Enter the departure city:")
                departure = input(">")
                print("Enter the destination city:")
                destination = input(">")
                if len(code) < 3 or len(departure) < 3 or len(destination) < 3 or duration < 20:
                    print("Sorry, the provided data is not correct")
                else:
                    functions.add_list(flight_list, code, duration, departure, destination)
            except ValueError:
                print("Sorry, the provided data is not correct")

        if opt=='2':
            try:
                print("Enter the code:")
                code = input(">")
                if len(code) < 3:
                    print("Sorry, the provided data is not correct")
                else:
                    functions.del_list(flight_list, code)
            except ValueError:
                print("Sorry, the provided data is not correct")
        if opt=='3':
            print("Enter the departure city:")
            opt=input(">")
            functions.print_list(flight_list)
        if opt=='4':
            pass

start()