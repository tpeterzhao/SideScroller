main: main.o
	g++ main.o -o main -L"/opt/homebrew/Cellar/sfml/2.5.1_2/lib" -lsfml-graphics -lsfml-window -lsfml-system
main.o: main.cpp
	g++ -c main.cpp -I"/opt/homebrew/Cellar/sfml/2.5.1_2/include"
clean:
	rm -f main.o main