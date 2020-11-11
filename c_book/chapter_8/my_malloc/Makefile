#compiler variables
CC = gcc


TARGET = my_malloc

###
### Target rules
###
$(TARGET): main.o
	$(CC) -o $(TARGET) main.o

main.o: main.c
	$(CC) -c -g main.c

# my_dirent.o: my_dirent.c my_dirent.h
	# $(CC) -c -g my_dirent.c

clean:
	rm $(TARGET) *.o
