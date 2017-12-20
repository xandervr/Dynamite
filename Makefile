TARGET = Dynamite
MKDIR_P = mkdir -p
BUILD_DIR = Build

all: sha2.o SHA512.o Block.o Blockchain.o main.o
	g++ $(BUILD_DIR)/sha2.o $(BUILD_DIR)/SHA512.o $(BUILD_DIR)/Block.o $(BUILD_DIR)/Blockchain.o $(BUILD_DIR)/main.o -o $(BUILD_DIR)/$(TARGET)
	make clean
main.o: Dynamite/main.cpp Dynamite/Blockchain/Blockchain.hpp
	g++ Dynamite/main.cpp -c -o $(BUILD_DIR)/main.o

Blockchain.o: Dynamite/Blockchain/Blockchain.cpp Dynamite/Blockchain/Blockchain.hpp Dynamite/Block/Block.hpp Dynamite/Hashing/SHA512.hpp
	g++ Dynamite/Blockchain/Blockchain.cpp -c -o $(BUILD_DIR)/Blockchain.o

Block.o: Dynamite/Block/Block.cpp Dynamite/Block/Block.hpp Dynamite/Hashing/SHA512.hpp
	g++ Dynamite/Block/Block.cpp -c -o $(BUILD_DIR)/Block.o

SHA512.o: Dynamite/Hashing/SHA512.cpp Dynamite/Hashing/SHA512.hpp Dynamite/Hashing/sha2.h
	g++ Dynamite/Hashing/SHA512.cpp -c -o $(BUILD_DIR)/SHA512.o

sha2.o: Dynamite/Hashing/sha2.c Dynamite/Hashing/sha2.h
	$(MKDIR_P) $(BUILD_DIR)
	g++ Dynamite/Hashing/sha2.c -c -o $(BUILD_DIR)/sha2.o

clean:
	$(RM) $(BUILD_DIR)/*.o
