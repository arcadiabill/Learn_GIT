@echo off
h:\src\python\music\checkfiles.py g:\Music
pause

h:\src\python\music\getextensions.py g:\music
pause

echo Deleting current music text files
h:
cd \src\c\music
del *.txt
echo Music files Deleted.
echo.
echo Creating New Text Files (Assumes Drives G: and I: are online)
ListDir g:\music > \src\c\music\gMusic.txt
ListDir i:\music > \src\c\music\iMusic.txt
echo.
echo.
echo Files are prepared
fc gMusic.txt iMusic.txt
music2 gMusic.txt
