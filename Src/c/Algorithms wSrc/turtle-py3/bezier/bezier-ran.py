#!python3
import turtle, random, time

def turtle_cubic_bezier(p0,p1,p2,p3, n=20):
    x0, y0 = p0[0], p0[1]
    x1, y1 = p1[0], p1[1]
    x2, y2 = p2[0], p2[1]
    x3, y3 = p3[0], p3[1]
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

def r01(): return random.random()
def r(): return int(r01()*200-100)
def rr(): return(r(),r())
def rmid(x1,x2): return int(x1+x2+r()/2)/2

def next_points(points):
  p0, p3 = points[3], rr()
  p1 = rmid(p0[0],p3[0]), rmid(p0[1], p3[1])
  p2 = rmid(p0[0],p3[0]), rmid(p0[1], p3[1])
  return [p0,p1,p2,p3] 

# # globals that control slow color change.
# rk,rd = 0,0
# rbg = [r01(),r01(),r01()]
# 
# def random_color():
#     global rbg, rk, rd
#     # rk: which component to change, once in a while only.
#     if r01() < 0.1: rk = int(r01()*3)
#     # rd: how much to change the color
#     if r01() < 0.1: rd = r01()/6.
#     # Change the color component.
#     rbg[rk] += rd
#     if not 0 < rbg[rk] < 1.: # bounce off, if out of range.
#       rd = -rd
#       rbg[rk] += rd
#     print("rbg=(%3.2f,%3.2f,%3.2f)" % (rbg[0],rbg[1],rbg[2]))
#     turtle.color(*rbg)

def random_color():
  def t(i): return time.clock() * i % 1
  rbg =  [t(1), t(3), t(5)]
  print("rbg=(%3.2f,%3.2f,%3.2f)" % (rbg[0],rbg[1],rbg[2]))
  turtle.color(*rbg)

def main():
    turtle.speed(0)
    turtle.colormode(1.)

    points = [rr(),rr(),rr(),rr()]
    i = 0
    while True:
      i=i+1
      print(i,*points)
      turtle_cubic_bezier(*points)
      points = next_points(points)
      random_color()
    turtle.Screen().exitonclick()
   
if __name__ == "__main__":
    main()
