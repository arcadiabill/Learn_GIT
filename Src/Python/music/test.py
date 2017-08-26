fileName = 'f:/src/c/music/iMusic.txt'
with open(fileName) as fp:
    nFiles = 0
    for Line in fp:
        length = len(Line) - 2
        if Line[0:4] == '    ' and Line[length] == ')':
            ++nFiles
        if Line[0:4] == '    ' and Line[length] != ')':
            print(Line)
    print('Number of files %d' % nFiles)
