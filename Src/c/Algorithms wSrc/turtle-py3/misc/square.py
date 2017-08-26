#!python3
import turtle
wn = turtle.Screen()
alex = turtle.Turtle()

def square(dist):
  if dist < 1:
    return
  for aColor in ["yellow", "red", "green", "blue"]:
    alex.color(aColor)
    alex.forward(dist)
    alex.left(90)

square(50)
wn.exitonclick()
