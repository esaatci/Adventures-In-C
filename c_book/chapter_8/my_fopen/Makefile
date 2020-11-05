#compiler variables
CC = gcc


TARGET = my_fopen

###
### Target rules
###
$(TARGET): main.o
	$(CC) -o $(TARGET) main.o

main.o: main.c
	$(CC) -c -g main.c

clean:
	rm $(TARGET) *.o