@echo off

set VERSION=..\tools\version.txt

if not exist %VERSION% >%VERSION% echo 0

for /f %%x in (%VERSION%) do (
	set /a var=%%x+1
)

>%VERSION% echo %var%
echo Building Autoincremental: %var%