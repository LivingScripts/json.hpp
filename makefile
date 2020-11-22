json.o: main.o json_concrete.o
	g++ main.o json_concrete.o -o json.o

main.o: main.cpp
	g++ -c main.cpp

json_concrete.o: src/json_concrete.hpp src/json_concrete.cpp src/core/json_abstract.hpp
	g++ -c src/json_concrete.cpp

clean:
	rm *.o
