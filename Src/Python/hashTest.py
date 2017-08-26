# Create & Test MD5 Hash function
#
# need os & hashlib
import os
import hashlib
import time

def md5(fname):
    hash_md5 = hashlib.md5()
    with open(fname, 'rb') as f:
        for chunk in iter(lambda: f.read(4096), b''):
            hash_md5.update(chunk)
    return hash_md5.hexdigest()

start_time = time.time()
hName = r'h:\music\a\a flock of sea gulls  {whr}\the best of a flock of sea gulls  (flac)\01 I ran.flac'
iName = r'i:\music\a\a flock of sea gulls  {whr}\the best of a flock of sea gulls  (flac)\01 I ran.flac'

for i in range(10):
    if os.path.exists(hName) and os.path.exists(iName):
        hHash = md5(hName)
        iHash = md5(iName)
        print('', hHash, '\n', iHash)
        if hHash == iHash:
            print('Hashes are the same')
        else:
            print('Hashes are different')
    else:
        if os.path.exists(hName):
            print(hName, 'Exists')
        else:
            print(iName, 'Missing')
        
        if os.path.exist(iName):
            print(iName, 'Exists')
        else:
            print(hName, 'Missing')
end_time = time.time()
print('End time  :', end_time)
print('Start time:', start_time)
print('Total time:', end_time - start_time)

