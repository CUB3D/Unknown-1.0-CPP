CC=g++
CFLAGS=-I. -I../Unknown\ 1.0++/. -I../Libs/RapidJSON/include/RapidJSON -I/usr/include/python3.6m -L. -std=gnu++14 -lUK -lSDL2 -lSDL2main -lSDL2_image -lpython3.6m -lpthread -ldl -lutil -lm
DEPS=
OBJ=Unknown\ Test.o

Unkown\ Test.o:
	$(CC) -c "Unknown Test.cpp" -o "Unkown Test.o" $(CFLAGS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

test: $(OBJ)
	$(CC) $(CFLAGS) -o a.out $^

