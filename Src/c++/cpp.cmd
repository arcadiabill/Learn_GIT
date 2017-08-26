@echo off
rem Compile c++ programs with -std=c++11 flag
g++ -std=c++11 %1.cpp -o%1
