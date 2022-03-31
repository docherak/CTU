all: quicksort

quicksort: quicksort.o
	g++ -o quicksort quicksort.o

quicksort.o: quicksort.cpp
	g++ -c quicksort.cpp

clean:
	rm quicksort.o quicksort
