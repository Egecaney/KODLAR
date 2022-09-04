
""" Lecture 2 """
""" Prime Numbers
def PrimeNumberorNot(Number):
    PrimeControl = 0
    if (Number > 1):
        for i in range(2, Number):
            if (Number % i == 0):
                PrimeControl = 1
        return (PrimeControl)

def FindPrimeNumbers(Number):
    for i in range(2,Number):
        PrimeOrder = PrimeNumberorNot(i)
        if PrimeOrder == 0:
            print(i)

Number = int(input("Enter a positive number: "))
PrimeorNot = PrimeNumberorNot(Number)
if PrimeorNot == 0:
    print(Number,"is Prime Number.")
else:
    print(Number,"is not Prime Number.")

print("All Prime Numbers in Region: ")
FindPrimeNumbers(Number)
"""

""" Fahrenheit TO Centigrade (With Fuction)
def FahrenheittoCentigrade(Fahrenheit):
    Celcius = (Fahrenheit-32)*5/9
    return Celcius

print("Output:\nFahrenheit(F)  Centigrade(C)")
for Fahrenheit in [-40, 0, 32, 68, 98.6, 212]:
    Celcius = FahrenheittoCentigrade(Fahrenheit)
    print("   ","{0:.2f}".format(Fahrenheit),"        ", "{0:.2f}".format(Celcius))
print("All Done!")
"""

"""
Name = ['Egemen Can','Eren Yağız','Ozan']
Surname = ['Ayduğan','Tumbul','Coşgun']
for i in range(len(Name)):
    print("Name Surname: ",Name[i],Surname[i])
print("All Done!")
"""

""" Divisors
def findDivisors (n1, n2):
    # Assumes n1 and n2 are positive ints Returns a tuple containing all common divisors of n1 & n2
    divisors = ()  # the empty tuple
    for i in range(1, min(n1, n2) + 1):
        if n1 % i == 0 and n2 % i == 0:
            divisors = divisors + (i,)
            # print(divisors,i)
    return divisors

divisors = findDivisors(20, 100)
print(divisors)
total = 0
for d in divisors:
    total += d
print(total)
"""









""" Lecture 3 """
""" List Insertion
list1 = [1,2,3]
list2 = [10,20]
list1.append(4)
print(list1)                    #[1,2,3,4]
list1.append(5)
print(list1)                    #[1,2,3,4,5]
list1.insert(2,10)
print(list1)                    #[1,2,10,3,4,5]
list1.extend(list2)
print(list1)                    #[1,2,10,3,4,5,10,20]
list1.append(list2)
print(list1)                    #[1,2,10,3,4,5,10,20,[10,20]]
print(list1[7]*list2[1])        # 20*20 = 400
print(list1[8][0],list1[8][1])  # 10,20
list1.remove(3)
print(list1)                    #[1,2,10,4,5,10,20,[10,20]]
list1.pop()
print(list1)                    #[1,2,10,4,5,10,20]
list1.pop()
print(list1)                    #[1,2,10,4,5,10]
list1.pop(3)
print(list1)                    #[1,2,10,5,10]
list1[len(list1)-1] = 0
print(list1)                    #[1,2,10,5,0]
list1[1:2] = list2
print(list1)                    #[1,10,20,10,5,0]
list1[1:3] = list2
print(list1)                    #[1,10,20,10,5,0]
list1[1:4] = list2
print(list1)                    #[1,10,20,5,0]
list2 = list1
list1[1:3] = list2
print(list1)                    #[1,1,10,20,5,0,5,0]
list2[3:7] = []
print(list1,list2)              #[1,1,10,0] [1,1,10,0]
list2 = [5,6]
print(list1,list2)              #[1,1,10,0] [5,6]
"""
""" Ternary Assignment
the_list = []
for i in range(16):
    the_list.append('even' if i % 2 == 0 else 'odd')
print(the_list)
# the_list = ['even' if i%2 == 0 else 'odd' for i in range(16)]
"""










"""Tuples
t1 = (1,'two',3)
t2 = (t1,3.25)
print(t2)                 # ((1,'two',3),3.25)
print((t1+t2))            # (1,'two',3,(1,'two',3),3.25)
print((t1+t2)[3])         # (1,'two',3)
print((t1+t2)[2])         # 3
print((t1+t2)[2:4])       # (3,(1,'two',3))
print((t1+t2)[2:5])       # (3,(1,'two',3),3.25)
"""










""" Lecture 4 """
""" File Input Output
# Open Modes
# r = open for read (default)
# w = open for write, truncate
# r+ = open for read/write
# w+ = open for read/write, truncate
# a+ = open for read/append

# Reading Files
TxtFile = open('Name.txt')
for Line in TxtFile:
    for Word in Line.split():
        print(Word.strip('.,'))

with open('Name.Txt') as Txt:
    for line in Txt:
        for word in line.split():
            print(word.strip('.,'))

# Total Words in File
MyFile = open("Name.txt")
NumWords = 0
for LineofText in MyFile:
    WordList = LineofText.split()
    NumWords += len(WordList)
MyFile.close()
print("Total Words in File: ",NumWords)

# Writing Files
OpenFiles = open('Name.txt','w')
OpenFiles.write('Turtles\n')
OpenFiles.write('Goat(Messi)\n')
OpenFiles.close()

OpenFiles = open('Name.txt','r')
for Animal in OpenFiles:
    print(Animal,end='')
OpenFiles.close()

NameHandle = open('Name.txt','a')
NameHandle.write('Rick and Morty\n')
NameHandle.write('ToM and Jerry\n')
NameHandle.close()

NameHandle = open('Name.txt','r')
for ExtraLine in NameHandle:
    print(ExtraLine[:-1])
NameHandle.close()

# Numbers
Numbers = open('Number.txt')
Total = 0
People = 0
for Lines in Numbers:
    print(Lines.strip())
    Student = Lines.strip()
    Information = Student.split("-")
    Total += int(Information[2])
    People += 1

print("Total of Exams: ",Total,"\nExam Average:",Total/People)
"""








""" Homework """
""" 1. Soru
print("Output:\nFahrenheit(F)  Centigrade(C)")
for Fahrenheit in [-40, 0, 32, 68, 98.6, 212]:
    Celcius = (Fahrenheit-32)*5/9
    print("   ",Fahrenheit,"        ", "{0:.1f}".format(Celcius))
print("All Done!")
"""
""" 2. Soru
def square(x):
    return x*x

def fahr_to_cent(fahr):
    return ((fahr-32)/9.0)*5

def cent_to_fahr(cent):
    result = (cent/5.0)*9+32
    return result

def abs(x):
    if x<0:
        return (-x)
    else:
        return (x)

def print_hello():
    print("Hello, world")

def print_fahr_to_cent(fahr):
    result = fahr_to_cent(fahr)
    print(result)

x = 42
print(x)
result = square(3)+square(4)
boiling = fahr_to_cent(212)
cold = cent_to_fahr(-40)
print(result)
print(abs(-22))
print(print_fahr_to_cent(32))
"""

""" 3.Soru """
import cv2
import scipy
import openpyxl
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from skimage import io,color,data

# Displaying Image
Image = io.imread("Egemen.jpg")

io.imshow(Image)
plt.show()

# Getting Image Resolution
print("Image Resolution: ",Image.shape)

# Getting Pixel Values
DataFrame = pd.DataFrame(Image.flatten())
FilePath ='pixel_values1.xlsx'
DataFrame.to_excel(FilePath,index=False)

# Converting Color Space
Image_HSV = color.rgb2hsv(Image)
Image_RGB = color.hsv2rgb(Image_HSV)
plt.figure(0)
io.imshow(Image_HSV)
plt.figure(1)
io.imshow(Image_RGB)
plt.show()



