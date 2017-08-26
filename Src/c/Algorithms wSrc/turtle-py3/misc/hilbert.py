#!python3
import turtle
from turtle import left, right, forward, speed, Screen

size = 10

def hilbert(level, angle):
    if level == 0:
        return

    turtle.color("Blue")
    right(angle)
    hilbert(level - 1, -angle)

    turtle.color("Red")
    forward(size)
    left(angle)
    hilbert(level - 1, angle)

    turtle.color("Purple")
    forward(size)
    hilbert(level - 1, angle)
    left(angle)
    forward(size)

    turtle.color("Green")
    hilbert(level - 1, -angle)
    right(angle)

speed(0)
hilbert(4,90)
Screen().exitonclick()
