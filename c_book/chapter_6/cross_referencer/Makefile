#compiler variables
CC = gcc


TARGET = cross_referencer

###
### Target rules
###
$(TARGET): main.o referencer.o
	$(CC) -o $(TARGET) main.o referencer.o

main.o: main.c referencer.h
	$(CC) -c -g main.c

referencer.o: referencer.c referencer.h
	$(CC) -c -g referencer.c

clean:
	rm $(TARGET) *.o