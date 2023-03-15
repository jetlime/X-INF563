CC=clang --std=gnu99
CFLAGS=#-Wall -Wextra -Werror -Weverything -Wpadded -pedantic 
LIBS=
BLDFLAGS=-O2 -g

TARGET=program.exe
DEPS=src/alg_c.c src/alg_d.c src/main.c
HEAD= 
OBJ=$(patsubst src/%.c,obj/%.o,$(DEPS))

.PHONY: all clean

all: $(TARGET)

obj/%.o: src/%.c $(DEPS)
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(BLDFLAGS)

clean:
	rm -f *.o *~ *.core $(OBJ) $(TARGET)
