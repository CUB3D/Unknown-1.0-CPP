CC=g++
CFLAGS=-I. -I../Output/lib/linux/include/. -I/usr/include/SDL2/. -I../Libs/RapidJSON/include/rapidjson/. -I/usr/include/python3.6m -L../Output/lib/linux/. -std=gnu++14 -lUK -lSDL2_ttf -lSDL2 -lSDL2main -lSDL2_image -lpython3.6m -lpthread -ldl -lutil -lm -ggdb
OBJ=UnknownTest.o

%.o: %.cpp
	$(CC) $(CFLAGS) -O2 -c $< -o $@

test: $(OBJ)
	$(CC) $(CFLAGS) -O2 UnknownTest.o -o a.out


.PHONY: clean

clean:
	rm *.o
