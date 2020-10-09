#compiler variables
CC = gcc


TARGET = word_alph_print

###
### Target rules
###
$(TARGET): main.o bin_tree.o word_list.o get_word.o
	$(CC) -o $(TARGET) bin_tree.o main.o word_list.o get_word.o -lm

main.o: main.c bin_tree.h get_word.h
	$(CC) -c -g main.c

bin_tree.o: bin_tree.c bin_tree.h word_list.h
	$(CC) -c -g bin_tree.c

word_list.o : word_list.c word_list.h
	$(CC) -c -g word_list.c

get_word.o: get_word.c get_word.h
		$(CC) -c -g get_word.c

clean:
	rm $(TARGET) *.o