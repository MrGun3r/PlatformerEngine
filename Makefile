all:main.c
	gcc -g3 -fsanitize=undefined -fsanitize-undefined-trap-on-error main.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -o game