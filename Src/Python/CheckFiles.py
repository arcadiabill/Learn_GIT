# ---------------------------------------------------------------
# CheckFiles [Start Directory [true]]            Rev 1 2016/11/30
#               Defaults to current directory if start directory
#               isn't given.
#
# Purpose: Check all the audio files to see if they are formatted
#          according to the format 'nn[n] Song Title.ext'
#          A good name is '01 Endless summer.mp3'
#          A bad  name is '01-Endless summer.mp3'
#                      or '01 - Endless summer.MP3'
# Params : argv[1] - Starting Directory
#          argv[2] - If present and string = true, then the bad
#                    filenames will be renamed.
#
# RevHist: Version  -- Date --  Reason for change
#              0.0  2014/10/02  Initial Release
#              1.0  2016/11/30  Display's Usage, minor cleanup
#
# ---------------------------------------------------------------
import os
import sys
import locale
import re

utf8 = '65001'               # MSDN says this is codepage for utf-8
# Get Starting path -- Default is current dir
path = os.path.abspath('.')
if len(sys.argv) == 2:
    path = sys.argv[1]

if len(sys.argv) == 3 and sys.argv[2].lower() == 'true':
    path = sys.argv[1]
    fixFile = True
else:
    fixFile = False

# Print header and starting conditions
os.system('cls')
print('CheckFiles v1.0 whr')
print('  Usage  : Python CheckFiles.py [Start_Dir [true]] <--true fixes Files')
print('  Example: Python CheckFiles.py f:\music true\n')
print('Setting Codepage to 65001 (utf-8), Currently:',locale.getpreferredencoding(),
      '\n  Now, ', end='')
os.system('chcp %s' % utf8)

print('\nChecking audio files for non-standard format in: %s' % path)
print('  Preferred Fmt: nn[n] Song Title.ext')
print("  Example   Fmt: 01 I'm a Lonesome Traveler.mp3\n")

# Set regx to find files that are malformed.
# Well formed files are of the form: nn[n] filename.ext
# A good filename is '01 Endless summer.mp3'
# A bad  filename is '01-Endless summer.mp3'
#                 or '01 - Endless summer.mp3', etc.
regx = r'^(\d{2,3})([ .-]+)(.+)'  # one space between 2-3 digit number and rest of namespace

badSep = []
nBad = nBadSep = nFiles = nGood = 0
audioExt = ('.mp3', '.m4a', '.wma', '.mpc', '.ape', '.wav', '.flac', '.dts')
prtHdr = True
for root, dirs, files in os.walk(os.path.expanduser(path)):
    for fn in files:
        nFiles += 1
        bn, ext = os.path.splitext(fn)

        if ext not in audioExt:
          continue

        match = re.search(regx, bn)
        if not match:
            continue

        if not match.group(1).isdigit():
            continue

        if match.group(2) == ' ':
            nGood += 1
            continue
            
        # Files with undesirable separators handled next
        nBad += 1
        src = root + '\\' + fn
        dst = root + '\\' + match.group(1) + ' ' + match.group(3) + ext
        if fixFile:
            os.rename(src, dst)
        else:
            if prtHdr:
                print('Found Bad Separators in these Titles:')
                prtHdr = False
            print('     ', src)
            print('   ->', match.group(1) + ' ' + match.group(3) + ext)

        if match.group(2) not in badSep:
            badSep.append(match.group(2))
            nBadSep += 1
    # End 'for fn in files'

badSep.sort()
nOther = nFiles - (nGood + nBad)
warning = ''
if nBad > 0: warning = '<-- Files not fixed'
if nBadSep > 0:
    print('Number of Bad Separators : %d' % nBadSep, end=' ')
    print(badSep)
else:
    print('No Bad Separators')

print("\nTotal Files:%6d\nGood  Names:%6d" % (nFiles, nGood))
if nBad and fixFile:
    print('Poor  Names:%6d <-- Fixed these files' % nBad)
else:
    print('Poor  Names:%6d %s' % (nBad, warning))

print('Other Names:%6d' % nOther)
