CC=g++
CFLAGS=-I. -I/usr/include/SDL2/. -I../Output/lib/linux/include/. -I../Libs/RapidJSON/include/rapidjson -I/usr/include/python3.6m -L. -std=gnu++14 -lUK -lSDL2 -lSDL2main -lSDL2_image -lpython3.6m -lpthread -ldl -lutil -lm
DEPS=
OBJ=Unknown\ Test.o

Unknown\ Test.o: Unknown\ Test.cpp
	$(CC) -c "Unknown Test.cpp" -o "Unkown Test.o" $(CFLAGS)

%.o: %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)

test: $(OBJ)
	$(CC) $(CFLAGS) -o a.out $^

.PHONY: clean

clean:
	rm *.o

