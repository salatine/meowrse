all: meowrse.c
	ifeq ($(OS),Windows_NT)
    gcc -o meowrse.exe meowrse.c
	else
    gcc -o meowrse meowrse.c
	endif