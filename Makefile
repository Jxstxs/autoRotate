cc=gcc
cflags=-Wall
release=-O2

bins=bin
srcs=$(wildcard src/*.c)
objs=$(patsubst src/%.c, objs/%.o, $(srcs))
bin=autoRotate

all: autoRotate

binsdir:
	mkdir -p bin

objsdir:
	mkdir -p objs

autoRotate: $(objs) binsdir
	$(cc) $(cflags) $(objs) -o bin/$(bin)

objs/%.o: src/%.c objsdir
	$(cc) $(cflags) -c $< -o $@

clean:
	rm -rf bin/* objs/*
