pantry: pantry.o
	g++ -o result.out pantry.o -Wall -pedantic  -fsanitize=leak -g2 -Wshadow

pantry.o: pantry.cpp
	g++ -c pantry.cpp -Wall -pedantic  -fsanitize=leak -g2 -Wconversion -Wshadow -std=c++17

clean:
	rm -f result.out
