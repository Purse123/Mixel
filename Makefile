CC = g++
CFLAGS = -Wall -Wextra

build/table_model.o: src/table_model.cpp
	$(CC) $^ -c -o $@ $(CFLAGS) -I./include/

build/csv_parser.o: src/csv_parser.cpp
	$(CC) $^ -c -o $@ $(CFLAGS) -I./include/

build/viewer.o: src/viewer.cpp
	$(CC) $^ -c -o $@ $(CFLAGS) -I./include/

build/main.o: main.cpp 
	$(CC) $^ -c -o $@ $(CFLAGS) -I./include/

build/cell_method.o: src/cell_method.cpp
	$(CC) $^ -c -o $@ $(CFLAGS) -I./include/

main: build/main.o build/csv_parser.o build/viewer.o build/cell_method.o build/table_model.o
	$(CC) $^ -o $@ $(CFLAGS) -I./include/

clean:
	rm *~ build/*.o main
