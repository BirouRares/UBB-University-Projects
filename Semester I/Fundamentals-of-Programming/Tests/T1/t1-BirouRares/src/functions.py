def new_flight(p1, p2, p3,p4):
    return [p1, p2, p3,p4]
def list_code(flight_list):
    return flight_list[0]
def list_duration(flight_list):
    return flight_list[1]
def list_departure(flight_list):
    return flight_list[2]
def list_destination(flight_list):
    return flight_list[3]
def list_code1(flight_list,val):
    flight_list[0]=val
def list_duration1(flight_list,val):
    flight_list[1]=val
def list_departure1(flight_list,val):
    flight_list[2]=val
def list_destination1(flight_list,val):
    flight_list[3] = val

def list_to_str(flight_list):
    return str(flight_list[0])+", "+str(flight_list[1])+", "+str(flight_list[2])+", "+str(flight_list[3])

def add_list(flight_list: list, code,duration,departure,destination):
    flight_list.append(new_flight(code, duration,departure,destination))

def create_list(flight_list):

    add_list(flight_list,"0B31",45,"Oradea", "Cluj")
    add_list(flight_list,"0B32",60,"Oradea", "Timis")
    add_list(flight_list, "0B33", 50, "Timis", "Cluj")
    add_list(flight_list, "0B34", 32, "Bucuresti", "Cluj")
    add_list(flight_list, "0B35", 70, "Oradea", "Teleorman")

def print_list(flight_list:list):
    print("List of flights is:\n" + ",\n".join(map(list_to_str, flight_list)))

def del_list(flight_list: list, code):
    for i in range(0,len(flight_list)-1):
        if list_code(flight_list[i])==code:
            flight_list.pop(i)
    if list_code(flight_list[len(flight_list)-1])==code:
        flight_list.pop(len(flight_list)-1)

def printt(flight_list, departure):
    for i in range(0, len(flight_list)):
        if (list_departure(flight_list[i]) == departure):
            print_list(flight_list[i])





