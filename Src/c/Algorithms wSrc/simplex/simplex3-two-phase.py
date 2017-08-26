#!python2.5
# from http://marioslapseofreason.blogspot.com/2011/01/two-phase-simplex-algorithm-python-code.html
# Two-Phase (or Artificial Variable) Simplex algorithm
# from Combinatorial Optimization
# by Papadimitriou and Steiglitz.

# Given a Linear Program of the form:
# Minimize:      c x
# subject to:    Ax<=b

# The function get_tableau takes the cost vector c, matrix A,
# and the vector b. You must make b>=0.
# So get_tableau will return the tableau ready for the function
# two_phase_simplex to do the work and return the final tableau
# from which we can get the information about the optimal bfs.
 
# Example:
# Min: z = x1 + x2 + x3 + x4 + x5
# Subject to:
# 3x1 + 2x2 + x3           = 1
# 5x1 +  x2 + x3 + x4      = 3
# 2x1 + 5x2 + x3 +     x5  = 4

#   z = [ 1, 1, 1, 1, 1]
#
# eq1 = [ 3, 2, 1, 0, 0]
# eq2 = [ 5, 1, 1, 1, 0]
# eq3 = [ 2, 5, 1, 0, 1]
#
#   b = [1 , 3, 4]
 


def print_tableau(tableau, message):
  print "%s:" % message
  r = 0
  print "col=",
  for e in range(0,9):
    print "%6d" % e,
  print
  for row in tableau:
    # print row
    print "r%d=[" % r,
    for e in row:
      if int(e) == e:
        print "%6d" % e,
      else:
        print "%+6.2f" % e,
    print "]"
    r = r + 1
  print '----------------------'
  return
 

def pivotOn(tableau, row, col):
  j = 0
  pivot = tableau[row][col]
  for x in tableau[row]:
    tableau[row][j] = tableau[row][j] / pivot
    j += 1
  i = 0
  for xi in tableau:
    if i != row:
      ratio = xi[col]
      j = 0
      for xij in xi:
        xij -= ratio * tableau[row][j]
        tableau[i][j] = xij
        j += 1
    i += 1
  return tableau


# Assuming tableau in standard form with basis formed in last m columns
def phase_1_simplex(tableau):
  
  THETA_INFINITE = -1
  opt   = False
  unbounded  = False
  n = len(tableau[0])
  m = len(tableau) - 2
  
  while ((not opt) and (not unbounded)):
    min = 0.0
    pivotCol = j = 1
    while(j < (n-m)):
      cj = tableau[1][j]
      if (cj < min):
        min = cj
        pivotCol = j
      j += 1   
    if abs(min) <= 1e-5:
      opt = True
      continue
    pivotRow = i = 0
    minTheta = THETA_INFINITE
    for xi in tableau:
      if (i > 1):
        xij = xi[pivotCol]
        if xij > 0:
          theta = (xi[0] / xij)
          if (theta < minTheta) or (minTheta == THETA_INFINITE):
            minTheta = theta
            pivotRow = i
      i += 1
    if minTheta == THETA_INFINITE:
      unbounded = True
      continue
    tableau = pivotOn(tableau, pivotRow, pivotCol)
  return tableau
  
def simplex(tableau):
  
  THETA_INFINITE = -1
  opt   = False
  unbounded  = False
  n = len(tableau[0])
  m = len(tableau) - 1
  
  while ((not opt) and (not unbounded)):
    min = 0.0
    pivotCol = j = 0
    while(j < (n-m)):
      cj = tableau[0][j]
      if (cj < min) and (j > 0):
        min = cj
        pivotCol = j
      j += 1   
    if min == 0.0:
      opt = True
      continue
    pivotRow = i = 0
    minTheta = THETA_INFINITE
    for xi in tableau:
      if (i > 0):
        xij = xi[pivotCol]
        if xij > 0:
          theta = (xi[0] / xij)
          if (theta < minTheta) or (minTheta == THETA_INFINITE):
            minTheta = theta
            pivotRow = i
      i += 1
    if minTheta == THETA_INFINITE:
      unbounded = True
      continue
    print "pivotOn(%d,%d)" % (pivotRow,pivotCol)
    tableau = pivotOn(tableau, pivotRow, pivotCol)
  return tableau
    
def drive_out_artificial_basis(tableau):
  n = len(tableau[0])
  j = n - 1
  isbasis = True
  while(j > 0):
    found = False
    i = -1
    row = 0
    for xi in tableau:
      i += 1
      if (xi[j] == 1):
        if (found):
          isbasis = False
          continue
        elif (i > 1):
          row = i
          found = True
      elif (xi[0] != 0):
        isbasis = False
        continue
    if (isbasis and found):
      if (j >= n):
        tableau = pivotOn(tableau, row, j)
      else:
        return tableau
    j -= 1

  return tableau
    
def two_phase_simplex(tableau):
  infeasible  = False
  tableau = phase_1_simplex(tableau)
  print_tableau(tableau, "after phase_1_simplex")
  sigma = tableau[1][0]
  if (sigma > 0):
    infeasible  = True
    print 'infeasible'
  else:
    # sigma is equals to zero
    tableau = drive_out_artificial_basis(tableau)
    print_tableau(tableau, "after drive_out_artificial_basis")
    m = len(tableau) - 2
    n = len(tableau[0])
    n -= m
    tableau.pop(1)
    i = 0
    while (i < len(tableau)):
      tableau[i] = tableau[i][:n]
      i += 1
    tableau = simplex(tableau)
    print_tableau(tableau,"in two_phase_simplex")
  return tableau
  
def get_tableau(c, eqs, b):
  # assume b >= 0 so if there is any b[i] negative make sure to enter
  # it positive by multiplying (-1 * eqs[i]) and (-1 * b[i]) for all i
  tableau = []
  m = len(eqs)
  n = len(c)
  c.insert(0, 0.0)
  artificial = []
  sigma = [0.0]
  i = 0
  while (i < n):
    sigma.append(0.0)
    i += 1
  i = 0
  while (i < m):
    artificial.append(0.0)
    sigma.append(1.0)
    i += 1
  c.extend(artificial)
  tableau.append(c)
  tableau.append(sigma)
  i = 0
  for eq in eqs:
    eq.insert(0, b[i])
    eq.extend(artificial)
    eq[n+1+i] = 1.0
    tableau.append(eq)
    i += 1
  i = 0 
  for xi in tableau:
    if (i > 1):
      j = 0
      for xij in xi:
        tableau[1][j] -= xij
        j += 1
    i += 1
  return tableau


if __name__ == '__main__':
  # Minimize: z = x1 + x2 + x3 + x4 + x5
  # Subject to:
  # 3x1 + 2x2 + x3           = 1
  # 5x1 +  x2 + x3 + x4      = 3
  # 2x1 + 5x2 + x3 +     x5  = 4

  c = [ 1.0, 1.0, 1.0, 1.0, 1.0,]

  eq1 = [ 3.0 ,  2.0 , 1.0 ,  0.0,  0.0]
  eq2 = [ 5.0 ,  1.0 , 1.0 ,  1.0,  0.0]
  eq3 = [ 2.0 ,  5.0 , 1.0 ,  0.0,  1.0]

  b = [1.0 , 3.0 , 4.0]

  eqs = []
  eqs.append(eq1)
  eqs.append(eq2)
  eqs.append(eq3)

  tableau = get_tableau(c,eqs,b)
  print_tableau(tableau, "initial tableau")
  tableau = two_phase_simplex(tableau)
  print_tableau(tableau, "final tableau")
  print 'minimum cost is ',-tableau[0][0]
