CC=g++
CFLAGS=-c -fpic -I. -I/usr/include/SDL2/. -I../Unknown\ 1.0++/. -I../Libs/RapidJSON/include/rapidjson/. -I/usr/include/python3.6m -L. -std=gnu++14 -lUK -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lpython3.6m -lpthread -ldl -lutil -lm
DEPS=Animation.h Colour.h Entity.h Font.h Image.h Input.h Loader.h Log.h Map.h Particle.h Physics.h PythonScript.h Quadtree.h Sprite.h Timer.h UI.h UI2D.h Util.h Vector.h Unknown.h
OBJ=Animation.o Colour.o Entity.o Font.o Image.o Input.o Loader.o Log.o Map.o Particle.o Physics.o PythonScript.o Quadtree.o Sprite.o Timer.o UI.o UI2D.o Utils.o Vector.o Unknown.o

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $< -o $@

libUK: $(OBJ)
	$(CC) -shared -o $@ $^
	mv libUK ../Output/lib/linux/libUK.so
	mkdir -p ../Output/lib/linux/include
	cp *.h ../Output/lib/linux/include


.PHONY: clean

clean:
	rm *.o
