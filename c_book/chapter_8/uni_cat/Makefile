#compiler variables
CC = gcc


TARGET = uni_cat

###
### Target rules
###
$(TARGET): main.o
	$(CC) -o $(TARGET) main.o

main.o: main.c
	$(CC) -c -g main.c

clean:
	rm $(TARGET) *.o