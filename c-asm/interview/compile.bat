@echo off
set PATH="C:\Users\joshu\Desktop\AllyLocal v9\libraries\tcc";
tcc -r -o string.o string_class.c
tcc -r -o classdef.o classdef.c
tcc -r -o node.o node_class.c
tcc -r -o main.o main.c classdef.o string.o node.o
tcc -run main.o
del string.o
del classdef.o
del node.o
del main.o
@echo.
pause