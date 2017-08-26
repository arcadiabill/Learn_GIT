#!python3.3
import turtle
def turtle_cubic_bezier(x0, y0, x1, y1, x2, y2, x3, y3, n=20):
    turtle.penup()
    turtle.goto(x0,y0)
    turtle.pendown()
    for i in range(n+1):
        t = i / n
        a = (1. - t)**3
        b = 3. * t * (1. - t)**2
        c = 3.0 * t**2 * (1.0 - t)
        d = t**3
 
        x = int(a * x0 + b * x1 + c * x2 + d * x3)
        y = int(a * y0 + b * y1 + c * y2 + d * y3)
        turtle.goto(x,y)
    turtle.goto(x3,y3)


def main():
    turtle.speed(0)
    turtle_cubic_bezier(0,0, 0,100, 100,0, 100,100)
    turtle.Screen().exitonclick()
   
if __name__ == "__main__":
    main()
