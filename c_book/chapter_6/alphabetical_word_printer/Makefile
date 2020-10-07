#compiler variables
CC = gcc


TARGET = word_alph_print

###
### Target rules
###
$(TARGET): main.o bin_tree.o word_list.o
	$(CC) -o $(TARGET) bin_tree.o main.o word_list.o -lm

main.o: main.c word_list.h
	$(CC) -c -g main.c

bin_tree.o: bin_tree.c bin_tree.h
	$(CC) -c -g bin_tree.c

word_list.o : word_list.c word_list.h
	$(CC) -c -g word_list.c

clean:
	rm $(TARGET) *.o