main: main.o
	g++ main.o -o main -L"C:\Users\tpete\OneDrive\Desktop\Projects\SFML\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system
main.o: main.cpp
	g++ -c main.cpp -I"C:\Users\tpete\OneDrive\Desktop\Projects\SFML\SFML-2.5.1\include"
clean:
	rm -f main.o main