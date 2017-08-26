from tkinter import *
root = Tk()

# mymenu = Menu(parent, **options)

# Adding Menubar in the widget
menubar = Menu(root)
filemenu = Menu(menubar, tearoff=0)
root.config(menu=menubar)

root.mainloop()
