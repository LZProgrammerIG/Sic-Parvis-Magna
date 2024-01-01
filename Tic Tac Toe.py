#Tic Tac Toe
import random
D={1:"1",4:"4",7:"7",2:"2",5:"5",8:"8",3:"3",6:"6",9:"9"}
L2=["1","2","3","4","5","6","7","8","9"]

def display():
    L3=[]
    L1=D.values()
    for i in L1:
        L3.append(i) 
    for i in range(3):
        print(L3[i],L3[i+3],L3[i+6])
display()

def check():
    m=0
    b=0
    #Verical checking
    for i in range(1,4):
        if D[i]==D[i+3]==D[i+6]:
            m=1
            b=D[i]
    #Horizontal checking
    for i in [1,4,7]:
        if D[i]==D[i+1]==D[i+2]:
            m=1
            b=D[i]
    #Diagonal checking
    if D[1]==D[5]==D[9] or D[3]==D[5]==D[7]:
      m=1
      b=D[5]
    #Match winner checking
    if m==1:
        if b=="X":
            display()
            print("Congratulations, You won!!!")
            return 0
        else:
            display()
            print("You lost. Better luck next time.")
            return 0
    elif len(L2)==0:
        display()
        print("Nobody won. Match is draw.")
        return 0
    else:
      return 1 

while True:
    ch=input("Enter the box number where you have to place 'X' :-  ")
    if ch not in L2:
      print("Enter the correct box number.")
    else:
      D[int(ch)]="X"
      L2.remove(ch)
      y=check()
      if y==0:
        break

      a=random.choice(L2)
      D[int(a)]="O"
      L2.remove(a)
      display()
      y=check()
      if y==0:
        break