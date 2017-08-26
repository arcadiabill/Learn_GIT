#!python3
import turtle as t
 
def yt(length=100):
    """ Paints a branch of a tree with 2 smaller branches, like an yt"""
    if length < 10:
           return
    t.forward(length)   # paint the thick branch of the tree
    t.left(30)          # rotate left for smaller "fork" branch
    yt(length * 0.6)     # create a smaller branch with 2/3 the length of the parent branch
    t.right(60)         # rotate right for smaller "fork" branch
    yt(length * 0.6)     # create second smaller branch
    t.left(30)          # rotate back to original heading
    t.forward(-length)  # move back to original position
    return              # leave the function, continue with calling program
 
# calling the function the first time
yt(100) # create a tree, the first branch has a length of 200 pixel
