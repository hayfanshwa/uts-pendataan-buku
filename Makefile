CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = buku
OBJ = main.o buku.o berkas.o menu.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

main.o: main.cpp buku.h berkas.h menu.h
	$(CXX) $(CXXFLAGS) -c main.cpp

buku.o: buku.cpp buku.h
	$(CXX) $(CXXFLAGS) -c buku.cpp

berkas.o: berkas.cpp berkas.h buku.h
	$(CXX) $(CXXFLAGS) -c berkas.cpp

menu.o: menu.cpp menu.h berkas.h buku.h
	$(CXX) $(CXXFLAGS) -c menu.cpp

clean:
	rm -f $(OBJ) $(TARGET)
