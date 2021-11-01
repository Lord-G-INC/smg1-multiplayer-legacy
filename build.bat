@echo off
cd compiler
py project.py

del project.o
del project.bin
del tmplink
rmdir tmp

cd ../source/
del main.c.o
del main.c.s

pause
