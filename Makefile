prog.exe :main.o graphe.o pixel.o
	g++ -Wall -O3 -o prog.exe main.o graphe.o pixel.o

graphe.o : graphe.cpp
	g++ -Wall -O3 -c graphe.cpp

main.o:	main.cpp
	g++ -Wall -O3 -c main.cpp

pixel.o : pixel.cpp
	g++ -Wall -O3 -c pixel.cpp

clean :
	rm -f *.o ; rm -f *.exe