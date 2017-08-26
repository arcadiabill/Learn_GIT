import os
os.system('cls')

text = r"f:\jt\music\IT KEEPS YOU RUNNIN´.mp3"
txt2 = r"f:\jt\music\IT KEEPS YOU RUNNIN.mp3"

print('File is:' + text)
root, name = os.path.split(text)
print('Root: ' + root + '\n' + 'Name: ' + name)

name, ext = os.path.splitext(name)
print('\nFile is: ' + name + '\n' + 'Ext  is: ' + ext)

print('\nText 2 ' + '\n' + txt2)
root, name = os.path.split(txt2)
print('\n' + root + '\n' + name)

print('Length str 1:', len(text))
print('Length str 2:', len(txt2))
