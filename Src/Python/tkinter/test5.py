from tkinter import *

root = Tk()

def printName(event):
    print('Hello my name is bill')

button_1 = Button(root, text='Print Name')
button_1.bind('<Button-1>', printName)
button_1.pack()

root.mainloop()
