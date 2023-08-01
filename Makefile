all: meowrse.c
	ifeq ($(OS),Windows_NT)
    	gcc -no-pie -static -o meowrse.exe meowrse.c
	else
    	gcc -no-pie -static -o meowrse meowrse.c
	endif