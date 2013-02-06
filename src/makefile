LDFLAGS = -ljsoncpp

all : test

FILES = uri config main

test : $(FILES:=.o)
	$(CXX) $^ -o $@ $(LDFLAGS)

clean:
	@rm -f test
	@rm -f $(FILES:=.o)
