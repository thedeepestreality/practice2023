@echo off
REM some scary dumb code
REM DO NOT REPEAT
set var=123
set var = 321
set concat=%var % %var%
echo %concat%

REM user input
set /P user_input="Enter value: "
echo %user_input%

REM numeric variables
set x=1
set y=2
set /a res = x + y
echo %x%+%y%
echo %res%