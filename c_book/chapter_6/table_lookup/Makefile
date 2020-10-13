#compiler variables
CC = gcc


TARGET = table_lookup

###
### Target rules
###
$(TARGET): main.o hash_table.o
	$(CC) -o $(TARGET) main.o hash_table.o

main.o: main.c hash_table.h
	$(CC) -c -g main.c

hash_table.o: hash_table.c hash_table.h
	$(CC) -c -g hash_table.c

clean:
	rm $(TARGET) *.o