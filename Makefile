CC = g++

CFLAGS =-Wall -Werror

all: huff

huff: FinalApp.o InBitStream.o OutBitStream.o FrequencyCounter.o HuffmanTree.o EmptyQueueException.o
	$(CC) $(CFLAGS) -o huff FinalApp.o InBitStream.o OutBitStream.o FrequencyCounter.o HuffmanTree.o EmptyQueueException.o

FinalApp.o: FinalApp.cpp OutBitStream.h InBitStream.h HuffmanTree.h FrequencyCounter.h
	$(CC) $(CFLAGS) -c FinalApp.cpp

InBitStream.o: InBitStream.cpp InBitStream.h
	$(CC) $(CFLAGS) -c InBitStream.cpp

OutBitStream.o: OutBitStream.cpp OutBitStream.h
	$(CC) $(CFLAGS) -c OutBitStream.cpp

FrequencyCounter.o: FrequencyCounter.cpp FrequencyCounter.h
	$(CC) $(CFLAGS) -c FrequencyCounter.cpp
	
HuffmanTree.o: HuffmanTree.cpp HuffmanTree.h TreeNode.h PriorityQueue.h
	$(CC) $(CFLAGS) -c HuffmanTree.cpp EmptyQueueException.cpp

EmptyQueueException.o: EmptyQueueException.cpp EmptyQueueException.h
	$(CC) $(CFLAGS) -c EmptyQueueException.cpp
	
clean:
	$(RM) huff *.o *~