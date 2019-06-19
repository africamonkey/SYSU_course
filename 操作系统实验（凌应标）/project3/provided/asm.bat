@echo off
set name=%~n1
tasm %name%.asm %name%.obj  > amsg.txt
type amsg.txt |find "Error"
type amsg.txt |find "Warn"

