CC=g++
CFLAGS=-I. -fpic -I/usr/include/SDL2/. -I../Libs/RapidJSON/include/rapidjson/. -I/usr/include/python3.6m -L. -std=gnu++14 -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lpython3.6m -lpthread -ldl -lutil -lm

all: libUK

SRC=$(shell find . -name "*.cpp")
OBJ=$(patsubst %.cpp, %.o, $(SRC))

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -O2 -c $< -o $@

libUK: $(OBJ)
	$(CC) $(CFLAGS) -O2 -shared -o $@ $^
	mkdir -p ../Output/lib/linux
	mv libUK ../Output/lib/linux/libUK.so
	mkdir -p ../Output/lib/linux/include
	/usr/bin/python ../tools/build/exportHeaders.py


.PHONY: clean

clean:
	rm *.o
