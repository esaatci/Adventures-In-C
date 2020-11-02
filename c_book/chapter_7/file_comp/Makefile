#compiler variables
CC = gcc


TARGET = file_comp

###
### Target rules
###
$(TARGET): main.o
	$(CC) -o $(TARGET) main.o

main.o: main.c
	$(CC) -c -g main.c

clean:
	rm $(TARGET) *.o