:: Script to compile source file & place it into the library
:: Created 2017-08-27
:: ---------------------------------------------------------
@echo off
cls
echo.

if XX==X%1X (
  echo Error: No filename given
  echo ------------------------
  call :Usage
  EXIT /B 1
)

:: See if the file exists before trying to compile it
if not exist tstFileExist.exe (
  echo Error: Need pgm tstFileExist.exe to work
  EXIT /B 1)

tstFileExist %1.c
if errorlevel 1 (
  echo Error: File %1.c does not exists, can't compile.
  echo -----------------------
  call :Usage
  EXIT /B 1
)

echo Compiling %1.c for library
gcc -Wall -std=c11 -c %1.c || goto :BAD

:: Compilation success if we got here
  echo Compilation successful.
  ar crs \src\lib\libwhr.a %1.o || goto :BAD2
  del %1.o

:: We are still good so show what's in the library
  echo.
  echo Library addition successful
  echo libwhr now contains:
  ar t \src\lib\libwhr.a
  EXIT /B 1

:BAD
echo Compilation failed.
:BAD2
echo Did not get into the library. Library contains:
ar t \src\lib\libwhr.a
EXIT /B 1

:END

:Usage
   echo usage: compile filename
   echo   Example: compile testPgm
   echo.
   echo This will compile filename.c and if successful,
   echo place it into the library \src\lib\libwhr.a
EXIT /B 1
