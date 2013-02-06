all:
	g++ -c uri.cpp
	g++ -c config.cpp
	g++ -c dataset.cpp
	g++ -c datafile.cpp
	g++ -I../netcdf/include -c main.cpp
	g++  *.o ../netcdf/lib/libnetcdf.a -o test -ljsoncpp

clean:
	rm -f test
	rm -f *.o