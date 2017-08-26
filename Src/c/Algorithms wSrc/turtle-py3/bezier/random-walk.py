#!python3
import turtle, random
wn = turtle.Screen() 
turtle.colormode(255)
turtle.speed(0)
for i in range(1000):
    turtle.forward(5) 
    turtle.left(random.random() * 180 - 90)
    turtle.color(i%255,(i+100)%255,(i+200)%255)
wn.mainloop() 
