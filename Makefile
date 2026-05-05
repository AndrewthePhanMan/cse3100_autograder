CC = gcc
CFLAGS = -Wall -Wextra -g

OBJS = parser.o runner.o test.o main.o

grader: $(OBJS)
	$(CC) $(CFLAGS) -o grader $(OBJS)

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

runner.o: runner.c
	$(CC) $(CFLAGS) -c runner.c

test.o: test.c test.h runner.h
	$(CC) $(CFLAGS) -c test.c

main.o: main.c parser.h runner.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o grader