@echo off
cls
echo Checking for invalid music files ...
python music\checkfiles.py i:\music
pause
echo Checking for extension
python music\getExtensions.py i:\music
