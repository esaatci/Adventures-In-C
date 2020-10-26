#compiler variables
CC = gcc


TARGET = preprocesor

###
### Target rules
###
$(TARGET): main.o hash_table.o get_word.o
	$(CC) -o $(TARGET) main.o hash_table.o get_word.o

main.o: main.c hash_table.h get_word.h
	$(CC) -c -g main.c

hash_table.o: hash_table.c hash_table.h
	$(CC) -c -g hash_table.c

get_word.o: get_word.h get_word.c
	$(CC) -c -g get_word.c

clean:
	rm $(TARGET) *.o