from tkinter import *


def doNothing():
    print('in do nothing')

root = Tk()

menu = Menu(root)
root.config(menu=menu)

subMenu = Menu(menu)
menu.add_cascade(label='File', menu=subMenu)
subMenu.add_command(label='New Project...', command=doNothing)
subMenu.add_command(label='New', command=doNothing)
subMenu.add_separator()
subMenu.add_command(label='Exit', command=doNothing)

editMenu = Menu(menu)
menu.add_cascade(label='Edit', menu=editMenu)
editMenu.add_command(label='Redo', command=doNothing)

# ---- The Toolbar ---
toolBar = Frame(root, bg='blue')
insertButt = Button(toolBar, text='Insert Image', command=doNothing)
insertButt.pack(side=LEFT, padx=2, pady=2)
printButt = Button(toolBar, text='Print', command=doNothing)
printButt.pack(side=LEFT, padx=2, pady=2)

toolBar.pack(side=TOP, fill=X)

# ---- Status Bar ---
status = Label(root, text='Preparing to do nothing', bd=1, relief=SUNKEN, anchor=W)
status.pack(side=BOTTOM, fill=X)

root.mainloop()
