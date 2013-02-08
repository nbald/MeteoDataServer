LDFLAGS = ../netcdf/lib/libnetcdf.a -ljsoncpp
CXXFLAGS = -g -Wall -DDEBUG -I.. -I../netcdf/include

all : test

CLASSES = uri config dataset datafile wrfgrid

test : $(CLASSES:=.o) main.o $(CLASSES:=.h)
	$(CXX) $(CLASSES:=.o) main.o -o $@ $(LDFLAGS)

clean:
	@rm -f test $(CLASSES:=.o) main.o
