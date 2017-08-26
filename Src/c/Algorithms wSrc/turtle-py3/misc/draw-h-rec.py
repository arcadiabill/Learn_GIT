#!python3
# What: draw H recursively.
import sys, math, time, random
import turtle

def r():
  return 0
  # return random.random()*10

def line(x,y,x2,y2):
  turtle.penup()
  turtle.goto(x+r(),y+r())
  turtle.pendown()
  turtle.goto(x2+r(),y2+r())
  turtle.penup()

def hh(x,y,n):
  if n <= 0:
    return
  k = n/1.5
  if k < 40: k = 40
  line(x-k,y-k,x-k,y+k)
  line(x+k,y-k,x+k,y+k)
  line(x-k,y,x+k,y)
  for dx in [-1,+1]:
    for dy in [-1,+1]:
      turtle.color(x%255,y%255,x*y%255)
      hh(x+dx*n/2,y+dy*n/2,n-k)

def main():
    turtle.colormode(255)
    turtle.speed(0)
    hh(0,0,300)
    turtle.Screen().exitonclick()
   
if __name__ == "__main__":
    main()
