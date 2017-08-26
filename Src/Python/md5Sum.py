import sys
import hashlib
from functools import partial

def md5sum(filename):
    with open(filename, mode='rb') as f:
        d = hashlib.md5()
        for buf in iter(partial(f.read, 128), b''):
            d.update(buf)
    return d.hexdigest()

print("  Program: %s\n" % sys.argv[0])
if len(sys.argv) == 1:
  print("    Usage: %s filename" % sys.argv[0])
  exit()
  
hashValue = md5sum(sys.argv[1])

print("md5sum of %s: %s" % (sys.argv[1], hashValue))
print("Int value %s: %d" % (sys.argv[1], int(hashValue, 16)))