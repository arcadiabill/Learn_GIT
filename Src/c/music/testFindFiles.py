import os, fnmatch


def find_files(directory, pattern):
    for root, dirs, files in os.walk(directory):
        for basename in files:
            if fnmatch.fnmatch(basename, pattern):
                filename = os.path.join(root, basename)
                yield filename

n = 0
nFiles = 0
for filename in find_files(r'h:\Music', '*.flac'):
    n += 1
    if os.path.isfile(filename):
        nFiles += 1;
    if n % 200 == 0:
        print('%5d: %s' % (n, filename))
print('Total found: %5d', n)
print('Total open : %5d', nFiles)
