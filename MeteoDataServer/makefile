LDFLAGS = -ljsoncpp -lproj -lncmmap
CXXFLAGS = -g -Wall -DDEBUG -I..

all : test

CLASSES = uri config dataset datafile wrfgrid

test : $(CLASSES:=.o) main.o $(CLASSES:=.h)
	$(CXX) $(CLASSES:=.o) main.o -o $@ $(LDFLAGS)

clean:
	@rm -f test $(CLASSES:=.o) main.o
