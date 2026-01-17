CC = g++
CFLAGS = -Wall -Wextra

build/table_model.o: table_model.cpp
	$(CC) $^ -c -o $@ $(CFLAGS)

build/csv_parser.o: csv_parser.cpp
	$(CC) $^ -c -o $@ $(CFLAGS)

build/viewer.o: viewer.cpp
	$(CC) $^ -c -o $@ $(CFLAGS)

build/main.o: main.cpp 
	$(CC) $^ -c -o $@ $(CFLAGS)

build/cell_method.o: cell_method.cpp
	$(CC) $^ -c -o $@ $(CFLAGS)

main: build/main.o build/csv_parser.o build/viewer.o build/cell_method.o build/table_model.o
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm *~ build/*.o main
