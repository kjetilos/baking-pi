CC=gcc

SOURCES=../source/drawing.c
CFLAGS=-std=c99

test: driver.o random.o string.o font.o
	$(CC) -o $@ $^

driver.o: driver.c
	$(CC) $(CFLAGS) -o $@ -c $^

drawing.o: ../source/drawing.c
	$(CC) $(CFLAGS) -o $@ -c $^

random.o: ../source/random.c
	$(CC) $(CFLAGS) -o $@ -c $^

string.o: ../source/string.c
	$(CC) $(CFLAGS) -o $@ -c $^

font.o: font.s
	$(CC) -o $@ -c $^

clean:
	rm -f *.o test
