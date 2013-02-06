all:
	g++ -c uri.cpp
	g++ -c config.cpp
	g++ -I../netcdf/include -c main.cpp
	g++  uri.o config.o main.o ../netcdf/lib/libnetcdf.a -o test -ljsoncpp

clean:
	rm -f test
	rm -f *.o