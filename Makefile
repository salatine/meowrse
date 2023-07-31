all: meowrse.c
	gcc -o meowrse meowrse.c
	x86_64-w64-mingw32-gcc -o meowrse.exe meowrse.c