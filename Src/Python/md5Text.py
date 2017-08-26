import hashlib
import sys

from functools import partial

def md5sum(filename):
    with open(filename, mode='rb') as f:
        d = hashlib.md5()
        for buf in iter(partial(f.read, 128), b''):
            d.update(buf)
    return d.hexdigest()

nArgs = len(sys.argv)
if nArgs > 1:
    print(md5sum(sys.argv[1]))
else:
    print('Usage: md5Text fileName')
