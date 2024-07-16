CFLAGS=-Wall -O3 -pedantic -I./include/
LIBS_LINUX=-L./lib/raylib-5.0_linux_amd64 -l:libraylib.a -lm
LIBS_WIN=-L./lib/raylib-5.0_win64_mingw-w64 -l:libraylib.a -lwinmm -lgdi32 -static -lm
SRC=src/main.c src/fish.c src/snake.c src/lizard.c src/chain.c src/math_utils.c src/drawing_utils.c

main: $(wildcard src/*.c) $(wildcard src/*.h)
	$(CC) $(CFLAGS) -o main $(SRC) $(LIBS_LINUX)

main.exe: $(wildcard src/*.c) $(wildcard src/*.h)
	x86_64-w64-mingw32-gcc $(CFLAGS) -o main.exe $(SRC) $(LIBS_WIN)
