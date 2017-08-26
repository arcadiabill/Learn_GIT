from tkinter import *

root = Tk()

one = Label(root, text='One', bg='red', fg='white')
one.pack()
two = Label(root, text='two', bg='green', fg='black')
two.pack(fill=X)
thr = Label(root, text='three', bg='blue', fg='white')
thr.pack(side=LEFT, fill=Y)


root.mainloop()
