g++ pie.cpp -c -g -std=c++11 \
    -I/usr/include/SDL2 -D_GNU_SOURCE=1 -D_REENTRANT \
    -L/usr/lib -lSDL2 -lSDL2_ttf -o pie.o

g++ main.cpp pie.o -o main -g -std=c++11 \
    -I/usr/include/SDL2 -D_GNU_SOURCE=1 -D_REENTRANT \
    -L/usr/lib -lSDL2 -lSDL2_ttf
