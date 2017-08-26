import os, string

def getMusicDirs():
    musicDirs = ['%s:\\Music' %d for d in string.ascii_uppercase if os.path.exists('%s:\\music' %d)]
    return musicDirs

musicDirs = getMusicDirs()
numMusicDirs = len(musicDirs)
if numMusicDirs != 2:
    print('Error: Should be 2 Music Dirs at root but found %d' % numMusicDirs)
    exit(1)

print('Found %d Music Directories\nMusic Dirs:' % numMusicDirs)
for i in range(numMusicDirs):
    print('%s' % musicDirs[i], end='')
    if i+1 < numMusicDirs: print(', ', end='')
    

