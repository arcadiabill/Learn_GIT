#!python2.5
# http://marioslapseofreason.blogspot.in/2011/01/simplex-method-in-python.html
# ========================================================
# Solve: Z = max z, A x <= b, x >= 0
# tableu is [Z z 0]
#           [b A I]
# ========================================================
# Example:
# Max: 0.5*x + 3*y + z + 4*w
# Subject to:  
#   x + y + z + w <= 40
# -2x - y + z + w <= 10
#       y     - w <= 10
# ========================================================
# z  = [ 0.0 , -0.5 , -3.0 ,-1.0 , -4.0,    0,    0,    0]
# x1 = [40.0 ,  1.0 ,  1.0 , 1.0 ,  1.0,  1  ,    0,    0]
# x2 = [10.0 , -2.0 , -1.0 , 1.0 ,  1.0,    0,  1  ,    0]
# x3 = [10.0 ,  0.0 ,  1.0 , 0.0 , -1.0,    0,    0,  1  ]
# ========================================================
 
def printTableu_plain(tableu):
  for row in tableu:
    print row  

def printTableu(tableu):
  print '----------------------'
  r = 0
  print "col=",
  for e in range(0,8):
    print "%7d" % e,
  print
  for row in tableu:
    print "r%d=[" % r,
    for e in row:
      print "%+7.2f" % e,
    print "]"
    r = r + 1
  print '----------------------'
  return

def print_tableau(var_names,tableu):
  for ti in tableu[1:]:
    i = 0
    for v in var_names:
      i = i+1
      if ti[i] == 1:
        print "+ %2s" % (v),
      elif ti[i] == -1:
        print "- %2s" % (v),
      elif ti[i] != 0:
        print "%+2.2f * %2s" % (ti[i],v),
      else:
        print '%7s'%'...',
    print " == ",ti[0]
 

def pivotOn(tableu, row, col):
  j = 0
  pivot = tableu[row][col]
  for x in tableu[row]:
    tableu[row][j] = tableu[row][j] / pivot
    j += 1
  i = 0
  for xi in tableu:
    if i != row:
      ratio = xi[col]
      j = 0
      for xij in xi:
        xij -= ratio * tableu[row][j]
        tableu[i][j] = xij
        j += 1
    i += 1
  return tableu


# assuming tablue in standard form with basis formed in last m columns
def simplex(tableu):
  
  THETA_INFINITE = -1
  opt   = False
  unbounded  = False
  n = len(tableu[0])     # 8 columns
  m = len(tableu) - 1    # 3 rows

  while ((not opt) and (not unbounded)):
    min = 0.0
    pivotCol = j = 0
    printTableu(tableu)
    while(j < (n-m)):
      cj = tableu[0][j]
      # We will simply choose the most negative column
      # which is called: "the nonbasic gradient method"
      # other methods as "all-variable method" could be used
      # but the nonbasic gradient method is simpler
      # and all-variable method has only been shown to be superior for some
      # extensive experiments by Kuhn and Quandt, the random tests used
      # by Kuhn and Quandt might not really represent "typical" LP's for
      # certain users.
      if (cj < min) and (j > 0):
        min = cj
        pivotCol = j
      j += 1   
    print "pivotCol=",pivotCol
    if min == 0.0:
      # We cannot profitably bring a column into the basis
      # which means that we've found an optimal solution
      opt = True
      continue
    pivotRow = i = 0
    minTheta = THETA_INFINITE
    for xi in tableu:
      # Bland's anticycling algorithm is theoretically a better
      # option than this implementation because it is guaranteed
      # finite while our simple policy can produce cycling.
      # Kotiath and Steinberg (1978) reported that cylcing does occur in practice
      # contradicting previous reports.
      # For simplicity, Bland's algorithm is not used here,
      # we just choose smallest xij for pivot row.
      if (i > 0):
        xij = xi[pivotCol]
        if xij > 0:
          theta = (xi[0] / xij)
          print "ratio = %2.2f = x[%d,%d]/x[%d,%d] = %2.2f/%2.2f" % (
            theta, i, 0, i, pivotCol, xi[0], xij)
          if (theta < minTheta) or (minTheta == THETA_INFINITE):
            minTheta = theta
            pivotRow = i
      i += 1
    if minTheta == THETA_INFINITE:
      # bringing pivotCol into the basis
      # we can move through that vector indefinetly without
      # becoming unfeasible so the polytope is not bounded in all directions
      unbounded = True
      continue
    
    # now we pivot on pivotRow and pivotCol
    print "pivot on (%d,%d)" % (pivotRow,pivotCol)
    tableu = pivotOn(tableu, pivotRow, pivotCol)

  print 'Final Tableu'
  printTableu(tableu)
  if opt:
    print "opt = ", tableu[0][0]
  else:
    print "No opt"
  print 'unbounded = ',unbounded
  return tableu

if __name__ == '__main__':

  # Max: 0.5*x + 3*y + z + 4*w
  # Subject to:  
  #   x + y + z + w <= 40
  # -2x - y + z + w <= 10
  #       y     - w <= 10

  z  = [ 0.0 , -0.5 , -3.0 ,-1.0 , -4.0,  0.0,  0.0,  0.0]
  x1 = [40.0 ,  1.0 ,  1.0 , 1.0 ,  1.0,  1.0,  0.0,  0.0]
  x2 = [10.0 , -2.0 , -1.0 , 1.0 ,  1.0,  0.0,  1.0,  0.0]
  x3 = [10.0 ,  0.0 ,  1.0 , 0.0 , -1.0,  0.0,  0.0,  1.0]

  tableu = []
  tableu.append(z)
  tableu.append(x1)
  tableu.append(x2)
  tableu.append(x3)

  var_names = ['x','y','z','w','s1','s2','s3'];
  print_tableau(var_names,tableu)

  tableu = simplex(tableu)
