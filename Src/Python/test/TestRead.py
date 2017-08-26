import re
line = 0
other = 0
p = re.compile(r'\bPortland IN\b')
with open("johnJayCenter.txt") as inFile:
    inFile.readline()       # Skip Header Line
    for aLine in inFile:
        if not p.search(aLine):
            other += 1
        else:
            line += 1
print("Number Portland INs in file: %4d." % line)
print("Number other cities in file: %4d." % other)


