CC = gcc
CFLAGS = -Wall -Wextra -g -I. 
LDFLAGS = -lm 
TARGET = run
SRCS = src/main.c src/hashmap/hashmap.c test/hashmap/testHashmap.c src/bplustree/bplustree.c test/bplustree/testBPlusTree.c src/linkedList/linkedList.c test/linkedList/testLinkedList.c src/dynamicArray/dynamicArray.c test/dynamicArray/testDynamicArray.c dependency/unity.c

OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

VPATH = src:test

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGET)