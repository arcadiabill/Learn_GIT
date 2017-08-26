import sys, os, _locale

_locale._getdefaultlocale = (lambda *args: ['en_US', 'utf8'])

def main(argv):
    if len(argv) != 2:
        raise Exception('Syntax: FindUnicodeFiles.py <directory>')

    startdir = argv[1]
    if not os.path.isdir(startdir):
        raise Exception('"%s" is not a directory' % startdir)
    for r in recurse_breadth_first(startdir, is_unicode_filename):
        print(r)

def recurse_breadth_first(dirpath, test_func):
    namesandpaths = [(f, os.path.join(dirpath, f)) for f in os.listdir(dirpath)]

    for (name, path) in namesandpaths:
        if test_func(name):
            yield path

    for (_, path) in namesandpaths:
        if os.path.isdir(path):
            for r in recurse_breadth_first(path, test_func):
                yield r

def is_unicode_filename(filename):
    return any(ord(c) >= 0x7F for c in filename)

if __name__ == '__main__':
    main(sys.argv)
