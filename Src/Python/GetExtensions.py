# ---------------------------------------------------------------
# GetExtensions [Start Directory]                Rev 0 2014/10/02
#               Defaults to current directory if start directory
#               isn't given.
#
# Purpose: Get the name and number of all files in the Directory
#          and all subdirectories of the directory given on the
#          command line. If no directory is given on the command
#          line, then use the current directory as the start Dir.
#
# RevHist: Version  -- Date --  Reason for change
#              0.0  2014/10/02  Initial Release
#
# ---------------------------------------------------------------
import sys
import os

os.system('cls')
sys.stdout._encoding = 'utf-8'
path = os.path.abspath('.') # default is the current directory

print('GetExtensions  Rev 0 (25 SEP 2014 whr)\n')
if len(sys.argv) == 2:
    path = sys.argv[1]
else:
    print('Usage:   GetExtensions.py [path]')
    print('            Program searching current directory since no path was given.')

print('\n   Searching %s for extensions and their number.\n' % path)


exts = {}
musicExt = ('.mp3', '.flac', '.m4a', '.wma', '.dts', '.mpc',
            '.ape', '.wav', '.wv', '.ogg', '.alac', '.aiff',
            '.aac', '.m4p')
for root, dirs, files in os.walk(os.path.expanduser(path)):
    for fn in files:
        bn, ext = os.path.splitext(fn)
        if not ext:
            continue
            
        if ext == ext.upper():
            ext = ext.lower()                # uppercase extensions to lower case
#            src = root + '\\' + bn + ext    # Uncomment these lines to rename
#            dst = root + '\\' + bn + ext    # NOTICE: If extension is a number
#            print(src)                      #         this dumb prg tries to rename it!!
#            print(dst)
#            os.rename(src, dst)

        exts[ext] = exts.get(ext, 0) + 1

items = [(v,k) for k,v in exts.items()]
items.sort()
items.reverse()

print('   Extensions   Number  AudioExt')
numAudio = 0
for v,k in items:
  key = '   ' + k.ljust(10)
  val = "{:,}".format(v).rjust(9)
  if k in musicExt:
    numAudio += v
    val += '     *'
  print(key+val)
 
if(numAudio):
    plural = ''
    if numAudio > 1: plural = 's'
    val = '\n   ' + "{:,}".format(numAudio) + ' Audio File' + plural + ' found.'
    print(val)
