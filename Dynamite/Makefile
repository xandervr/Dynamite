TARGET = Dynamite

all: sha2.o SHA512.o Block.o Blockchain.o main.o
	g++ sha2.o SHA512.o Block.o Blockchain.o main.o -o $(TARGET)
	make clean
	./$(TARGET)
main.o: main.cpp Blockchain/Blockchain.hpp
	g++ main.cpp -c -o main.o

Blockchain.o: Blockchain/Blockchain.cpp Blockchain/Blockchain.hpp Block/Block.hpp Hashing/SHA512.hpp
	g++ Blockchain/Blockchain.cpp -c -o Blockchain.o

Block.o: Block/Block.cpp Block/Block.hpp Hashing/SHA512.hpp
	g++ Block/Block.cpp -c -o Block.o

SHA512.o: Hashing/SHA512.cpp Hashing/SHA512.hpp Hashing/sha2.h
	g++ Hashing/SHA512.cpp -c -o SHA512.o

sha2.o: Hashing/sha2.c Hashing/sha2.h
	g++ Hashing/sha2.c -c -o sha2.o

clean:
	$(RM) *.o
