CC = g++
CFLAGS = -Wall -Wextra

csv_parser.o: csv_parser.cpp
	$(CC) $^ -c -o $@ $(CFLAGS)

viewer.o: viewer.cpp
	$(CC) $^ -c -o $@ $(CFLAGS)

main.o: main.cpp 
	$(CC) $^ -c -o $@ $(CFLAGS)

cell_method.o: cell_method.cpp
	$(CC) $^ -c -o $@ $(CFLAGS)

main: main.o csv_parser.o viewer.o cell_method.o
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm *~ *.o main
