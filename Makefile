all:
	g++ -I SDL2/include -L SDL2/lib/x86 -o exe/main main.cpp -lmingw32  -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf 

