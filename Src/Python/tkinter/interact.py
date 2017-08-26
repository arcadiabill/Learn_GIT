from tkinter import *

root = Tk()

def printName():
    print('Hello my name is Bill')

button_1 = Button(root, text='Print Name', command=printName)
button_1.pack()

root.mainloop()
