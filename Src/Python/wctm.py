import string

# Open HG Wells 'The Time Machine.txt'
# file = r'c:/users/bill/downloads/TheTimeMachine_HGWells.txt'
# tm = open(file, 'r')

line = r'    This table 4.1 is (reference 3) [quote 7] or so.   '
line = line.strip()
print(line)
line = line.lower()
line = ''.join(c for c in line if c in string.ascii_lowercase or c == ' ')
list = line.split(' ')
line = " ".join(list)
print(list)
print(line)