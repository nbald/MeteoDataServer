LDFLAGS = -ljsoncpp

all : test

HEADERS = uri config
FILES = uri config main

test : $(FILES:=.o) $(HEADERS:=.h)
	$(CXX) $(FILES:=.o) -o $@ $(LDFLAGS)

clean:
	@rm -f test
	@rm -f $(FILES:=.o)
