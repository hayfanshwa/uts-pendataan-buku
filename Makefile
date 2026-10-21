CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2 -Iinclude
TARGET = perpustakaan.exe
OBJECTS = main.o buku.o berkas.o menu.o

.PHONY: all run clean kill

all: $(TARGET)

$(TARGET): $(OBJECTS)
	-taskkill /F /IM $(TARGET) 2>NUL
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

main.o: src/main.cpp include/buku.h include/berkas.h include/menu.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o main.o

buku.o: src/buku.cpp include/buku.h
	$(CXX) $(CXXFLAGS) -c src/buku.cpp -o buku.o

berkas.o: src/berkas.cpp include/berkas.h include/buku.h
	$(CXX) $(CXXFLAGS) -c src/berkas.cpp -o berkas.o

menu.o: src/menu.cpp include/menu.h include/buku.h include/berkas.h
	$(CXX) $(CXXFLAGS) -c src/menu.cpp -o menu.o

run: all
	./$(TARGET)

kill:
	-taskkill /F /IM $(TARGET) 2>NUL

clean: kill
	-del /Q $(TARGET) $(OBJECTS) 2>NUL || rm -f $(TARGET) $(OBJECTS)
