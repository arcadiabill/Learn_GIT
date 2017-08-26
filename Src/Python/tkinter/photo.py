from tkinter import *
from tkinter import ttk

root = Tk()

photo = PhotoImage(file='fileName.png')
label = Label(root, image=phot)
label.pack()


root.mainloop()
