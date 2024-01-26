RELEASE_flags=-std=c89 -Os -DNDEBUG -g0 -s -Wall -Wno-unknown-pragmas
DEBUG_flags=-std=c89 -DDEBUG -Wall -Wno-unknown-pragmas -Wpedantic -Wshadow -Wextra -Werror=implicit-int -Werror=incompatible-pointer-types -Werror=int-conversion -Wvla -g -Og -fsanitize=address -fsanitize=undefined

.PHONY: all run format clean

all: bin/kokorobot bin/dir

run: all
	@ mkdir -p site/
	@ bin/kokorobot
	@ bin/dir media/content/oldart/
	@ bin/dir media/content/sketch/
format:
	@ clang-format -i src/main.c
clean:
	rm -r site/
	rm bin/*
bin/kokorobot: src/main.c
	mkdir -p bin/
	cc ${RELEASE_flags} src/main.c -o bin/kokorobot
bin/dir: src/dir.c
	mkdir -p bin/
	cc ${RELEASE_flags} src/dir.c -o bin/dir
