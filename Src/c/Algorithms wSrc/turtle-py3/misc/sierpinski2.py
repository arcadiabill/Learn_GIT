#!python3
import turtle
w=turtle.Screen()

def Tri(t, order, size,color):
    if order==0:
        t.forward(size)
        t.left(120)
        t.forward(size)
        t.left(120)
        t.forward(size)
        t.left(120)
    else:
        t.pencolor('red')
        Tri(t, order-1, size/2, color-1)
        t.fd(size/2)
        t.pencolor('blue')
        Tri(t, order-1, size/2, color-1)
        t.fd(size/2)
        t.lt(120)
        t.fd(size)
        t.lt(120)
        t.fd(size/2)
        t.lt(120)
        t.pencolor('green')
        Tri(t, order-1, size/2,color-1)
        t.rt(120)
        t.fd(size/2)
        t.lt(120)


myTurtle = turtle.Turtle()
myTurtle.speed(0)
Tri(myTurtle, 4, 200,100)
w.exitonclick()
