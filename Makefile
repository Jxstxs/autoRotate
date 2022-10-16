cc=gcc
cflags=-Wall
release=-O2

bins=bin
srcs=$(wildcard src/*.c)
objs=$(patsubst src/%.c, objs/%.o, $(srcs))
bin=autoRotate

install_path=/usr/local/bin/

all: autoRotate

binsdir:
	mkdir -p bin

objsdir:
	mkdir -p objs

autoRotate: $(objs) binsdir
	$(cc) $(cflags) $(objs) -o bin/$(bin)

objs/%.o: src/%.c objsdir
	$(cc) $(cflags) -c $< -o $@

install: autoRotate
	sudo cp ./bin/autoRotate $(install_path)

uninstall:
	sudo rm $(install_path)/$(bin)

clean:
	rm -rf bin/* objs/*
