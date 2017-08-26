@echo off
test.exe %1.c
if errorlevel 1 (
  echo %1.c does not exists.
) else (
  echo %1.c does exists.
)
  


