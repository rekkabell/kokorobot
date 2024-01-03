RELEASE_flags=-std=c89 -Os -DNDEBUG -g0 -s -Wall -Wno-unknown-pragmas
DEBUG_flags=-std=c89 -DDEBUG -Wall -Wno-unknown-pragmas -Wpedantic -Wshadow -Wextra -Werror=implicit-int -Werror=incompatible-pointer-types -Werror=int-conversion -Wvla -g -Og -fsanitize=address -fsanitize=undefined


.PHONY: all run format clean

all: bin/kokorobo

run:
	bin/kokorobot
format:
	@ clang-format -i src/kokorobot.c
clean:
	rm -r site/
	rm bin/*
bin/kokorobo: src/kokorobot.c
	mkdir -p bin/
	cc ${DEBUG_flags} src/kokorobot.c -o bin/kokorobot