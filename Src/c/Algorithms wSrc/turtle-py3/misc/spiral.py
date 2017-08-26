#!python3
import turtle

myTurtle = turtle.Turtle()
myWin = turtle.Screen()

def drawSpiral(myTurtle, lineLen):
    if lineLen > 0:
        myTurtle.forward(lineLen)
        myTurtle.right(60)
        drawSpiral(myTurtle,lineLen-2)

drawSpiral(myTurtle,100)
myWin.exitonclick()

