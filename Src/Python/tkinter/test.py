from tkinter import *

root = Tk()

topFrame = Frame(root)
topFrame.pack()
botFrame = Frame(root)
botFrame.pack(side=BOTTOM)

button1 = Button(topFrame, text='Button 1', fg='red')
button2 = Button(topFrame, text='Button 2', fg='blue')
button3 = Button(topFrame, text='Button 3', fg='green')
button4 = Button(botFrame, text='Button 4', fg='purple')
button1.pack(side=LEFT)
button2.pack(side=LEFT)
button3.pack(side=LEFT)
button4.pack(side=BOTTOM)

root.mainloop()
