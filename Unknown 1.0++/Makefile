CC=g++
CFLAGS=-I. -fpic -I/usr/include/SDL2/. -I../Libs/RapidJSON/include/rapidjson/. -I/usr/include/python3.6m -L. -std=gnu++14 -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lpython3.6m -lpthread -ldl -lutil -lm
OBJ=Animation.o Colour.o Entity.o Font.o Image.o Input.o Loader.o Log.o Map.o Particle.o Physics.o PythonScript.o Quadtree.o Sprite.o Timer.o UI.o UI2D.o Utils.o Vector.o Unknown.o Scene/SceneManager.o Scene/Scene.o

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -O2 -c $< -o $@

libUK: $(OBJ)
	$(CC) $(CFLAGS) -O2 -shared -o $@ $^
	mv libUK ../Output/lib/linux/libUK.so
	mkdir -p ../Output/lib/linux/include
	/usr/bin/python ../tools/build/exportHeaders.py


.PHONY: clean

clean:
	rm *.o
