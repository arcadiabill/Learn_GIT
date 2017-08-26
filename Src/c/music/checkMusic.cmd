@echo off
echo Deleting current music text files
d:
cd \src\c\music
del *.txt
echo Music files Deleted.
echo.
echo Creating New Text Files (Assumes Drives G: and H: are online)
d:\src\c\PrintDir g:\music > d:\src\c\music\gMusic.txt
d:\src\c\PrintDir h:\music > d:\src\c\music\hMusic.txt
echo.
echo.
echo Files are prepared
d:
cd \src\c\music
fc gMusic.txt hMusic.txt
