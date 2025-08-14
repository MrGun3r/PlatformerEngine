# Try to detect OS with uname; if not found, echo unknown

CFLAGS :=

ifeq ($(OS),Windows_NT)
    CFLAGS += -lmingw32
else 
    UNAME_S := $(shell uname -s 2>/dev/null)
    ifeq ($(UNAME_S),Linux)
      CFLAGS += -g -lm
	endif
endif
all: main.c    
	gcc main.c $(CFLAGS) -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -o game