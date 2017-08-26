import fileinput
import os
import locale
file = r'e:\src\c\test.txt'

def getpreferredencoding(do_setlocale = True):
    return "utf-16"
locale.getpreferrendencoding = getpreferredencoding

try:
    f = open(file, encoding='utf-8')
except:
    print("Couldn't open file: %s" % file)
    exit
f.close()

n = 0
nFound = 0
nBad = 0
for line in fileinput.input(file):
    n += 1
    # Strip \n from end
    line = line.rstrip()
    if os.path.isfile(line):  # Can find the UTF-8 files, can I open them?
        nFound += 1
        opened = False
        try:
            f = open(line, encodings='utf-8')
            opened=True
        except:
            nBad += 1
            print(line)
        if opened:
            f.close()
    else:
        nBad += 1
f.close()
print('Total Files:%6d' % n)
print('Good  Files:%6d' % nFound)
print('Bad   Files:%6d' % nBad)

