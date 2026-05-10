CC = gcc
CFLAGS = -Wall -Wextra -g

OBJS = parser.o runner.o test.o output.o main.o

grader: $(OBJS)
	$(CC) $(CFLAGS) -o grader $(OBJS)

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

runner.o: runner.c
	$(CC) $(CFLAGS) -c runner.c

test.o: test.c test.h runner.h
	$(CC) $(CFLAGS) -c test.c

output.o: output.c
	$(CC) $(CFLAGS) -c output.c

main.o: main.c parser.h test.h output.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o grader