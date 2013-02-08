LDFLAGS = ../netcdf/lib/libnetcdf.a -ljsoncpp
CXXFLAGS = -g -DDEBUG -I../netcdf/include

all : test

HEADERS = uri config dataset datafile wrfgrid
FILES = uri config dataset datafile wrfgrid main

test : $(FILES:=.o) $(HEADERS:=.h)
	$(CXX) $(FILES:=.o) -o $@ $(LDFLAGS)

clean:
	@rm -f test
	@rm -f $(FILES:=.o)
