CC=gcc

SOURCES=../source/drawing.c
CFLAGS=-std=c99

test: drawing.o driver.o random.o string.o
	$(CC) -o $@ $^

driver.o: driver.c
	$(CC) $(CFLAGS) -o $@ -c $^

drawing.o: ../source/drawing.c
	$(CC) $(CFLAGS) -o $@ -c $^

random.o: ../source/random.c
	$(CC) $(CFLAGS) -o $@ -c $^

string.o: ../source/string.c
	$(CC) $(CFLAGS) -o $@ -c $^

clean:
	rm -f *.o test
