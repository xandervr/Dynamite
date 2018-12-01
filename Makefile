TARGET = Dynamite
MKDIR_P = mkdir -p
BUILD_DIR = Build

all: sha2.o CPU.o SHA256.o Transaction.o MerkleTree.o Block.o Blockchain.o main.o
	g++ $(BUILD_DIR)/sha2.o $(BUILD_DIR)/CPU.o $(BUILD_DIR)/SHA256.o $(BUILD_DIR)/Transaction.o $(BUILD_DIR)/MerkleTree.o $(BUILD_DIR)/Block.o $(BUILD_DIR)/Blockchain.o $(BUILD_DIR)/main.o -o $(BUILD_DIR)/$(TARGET)
	make clean
main.o: Dynamite/main.cpp Dynamite/Blockchain/Blockchain.hpp
	g++ Dynamite/main.cpp -c -o $(BUILD_DIR)/main.o

Blockchain.o: Dynamite/Blockchain/Blockchain.cpp Dynamite/Blockchain/Blockchain.hpp Dynamite/CPU/CPU.hpp Dynamite/Block/Block.hpp Dynamite/Hashing/SHA256.hpp
	g++ Dynamite/Blockchain/Blockchain.cpp -c -o $(BUILD_DIR)/Blockchain.o

Block.o: Dynamite/Block/Block.cpp Dynamite/Block/Block.hpp Dynamite/Hashing/SHA256.hpp
	g++ Dynamite/Block/Block.cpp -c -o $(BUILD_DIR)/Block.o

MerkleTree.o: Dynamite/MerkleTree/MerkleTree.cpp Dynamite/MerkleTree/MerkleTree.hpp Dynamite/Transaction/Transaction.hpp Dynamite/Hashing/SHA256.hpp
	g++ Dynamite/MerkleTree/MerkleTree.cpp -c -o $(BUILD_DIR)/MerkleTree.o

Transaction.o: Dynamite/Transaction/Transaction.cpp Dynamite/Transaction/Transaction.hpp
	g++ Dynamite/Transaction/Transaction.cpp -c -o $(BUILD_DIR)/Transaction.o

SHA256.o: Dynamite/Hashing/SHA256.cpp Dynamite/Hashing/SHA256.hpp Dynamite/Hashing/sha2.h
	g++ Dynamite/Hashing/SHA256.cpp -c -o $(BUILD_DIR)/SHA256.o

CPU.o: Dynamite/CPU/CPU.cpp Dynamite/CPU/CPU.hpp
	g++ Dynamite/CPU/CPU.cpp -c -o $(BUILD_DIR)/CPU.o

sha2.o: Dynamite/Hashing/sha2.c Dynamite/Hashing/sha2.h
	$(MKDIR_P) $(BUILD_DIR)
	g++ Dynamite/Hashing/sha2.c -c -o $(BUILD_DIR)/sha2.o

clean:
	$(RM) $(BUILD_DIR)/*.o
