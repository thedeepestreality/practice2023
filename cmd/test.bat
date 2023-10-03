@echo off

if "%1" EQU ""  (
    echo missing first argument
    exit /b
)

if exist %1 (
    echo dir %1 already exist
    rmdir /s %1
)
mkdir %1
cd %1
echo %1 > %1.txt