#A player at PRONOSPORT wants to choose score options for four games.
#The options may be 1, X, 2. Generate all possible alternatives, knowing that:
#The last score option may not be X
#There should be no more than two score options of 1


import array as arr
sol=arr.array('i',[0,0,0,0,0])
elm=[1,2,"x"]
def init(k):
    sol[k]=-1

def succesor(k):
    if sol[k]<n-1:
        sol[k]=sol[k]+1
        return 1
    return 0

def valid(k):
    if elm[sol[k]]=='x' and k==n+1:
        return 0
    nr1=0
    for i in range(1,k+1):
        if elm[sol[i]]==1:
            nr1=nr1+1
    if nr1>2:
        return 0
    return 1

def solution(k):
    if k==n+1:
        return 1
    return 0

def afisare(k):
    for i in range(1,k+1):
    # print(sol[i], end=" ")
        print(elm[sol[i]], end=" ")
    print("\n")

def bkt_recursive(k):
    init(k)
    while succesor(k):
        if valid(k):
            if solution(k):
                afisare(k)
            else:
                bkt_recursive(k+1)

def bkt_iterative(k):
    init(k)
    while k>0:
        #print(sol, end=" ")
        found=False
        ok=True
        while ok:
            #l=succesor(k)
            sol[k]=sol[k]+1#we generate the succesor
            if sol[k]>n-1:
                break
            if valid(k)==1:#if we have a valid seq.
                found=True
            if found==True:#if we found a seq. we stop
                ok=False
        if found==False:#go back
            k=k-1
        else:
            if solution(k)==0:#if we find a combination
                k=k+1
                init(k)#initia
            else:
                afisare(k)

n=3
arr=[]
option=int(input("Type 1 for recursive algorithm or 2 for iterative algorithm: "))
if option==1:
    bkt_recursive(1)
if option==2:
    bkt_iterative(1)
if option!=1 and option!=2:
    print("Wrong command")