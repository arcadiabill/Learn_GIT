#!python3
import math, random
import turtle as t

def yt(length=100):
    """ Paints a branch of a tree with 2 smaller branches, like an Y"""
    t.pencolor(random.random(), 0.5 + random.random()/2, random.random())
    if length < 10:
           return
    t.forward(length)   # paint the thick branch of the tree
    t.left(30)          # rotate left for smaller "fork" branch
    yt(length * 0.6)    # create a smaller branch with 2/3 the length of the parent branch
    t.right(60)         # rotate right for smaller "fork" branch
    yt(length * 0.6)    # create second smaller branch
    t.left(30)          # rotate back to original heading
    t.forward(-length)  # move back to original position
    return              # leave the function, continue with calling program

## import colorsys
## GRADIENT_SPEC = [
##     (1.0, 1.0, 1.0),  # white
##     (1.0, 0.0, 0.0),  # red
##     (0.0, 1.0, 0.0),  # green
##     (0.0, 0.0, 1.0),  # blue
##     (0.0, 0.0, 0.0)]  # black
## 
## def gradient(d, spec=GRADIENT_SPEC):
##     """ d in [0..1] """
##     N = len(spec)
##     idx = int(d * (N - 1))
##     t = math.fmod(d * (N - 1), 1.0)
##     col1 = colorsys.rgb_to_hsv(*spec[min(N - 1, idx)])
##     col2 = colorsys.rgb_to_hsv(*spec[min(N - 1, idx + 1)])
##     hsv = tuple(a * (1 - t) + b * t for a, b in zip(col1, col2))
##     r, g, b = colorsys.hsv_to_rgb(*hsv)
##     # return '#%02X%02X%02X' % (r * 255, g * 255, b * 255)
##     return r,g,b

# Main
t.colormode(1.0)
yt(100) # create a tree, the first branch has a length of 200 pixel
