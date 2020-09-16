CPP  = g++
OBJ  = main.o MyFrame.o 
LIBS =  -L"./" `wx-config --libs core,base`
CXXINCS = -I"./" `wx-config --cxxflags`
CXXFLAGS = $(CXXINCS) -fno-pcc-struct-return -fstrict-aliasing -Wall -DNDEBUG
BIN  = mywximage

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	rm -rf $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o $(BIN) $(LIBS)
	strip $(BIN)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)

MyFrame.o: MyFrame.cpp
	$(CPP) -c MyFrame.cpp -o MyFrame.o $(CXXFLAGS)

