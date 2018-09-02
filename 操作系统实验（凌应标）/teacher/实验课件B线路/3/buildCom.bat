@echo off
set output=%~n1
set file1=%~n2
set file2=%~n3
set file3=%~n4
set file4=%~n5

tlink  /t %file1% %file2%  %file3% %file4% ,%output%.com,, >t.txt

goto :exit
rem ********convert .exe to .com
if exist %output%.com del /f /q %output%.com
exe2bin %output%.exe %output%.com
if exist %output%.exe del /f /q %output%.exe

:exit

