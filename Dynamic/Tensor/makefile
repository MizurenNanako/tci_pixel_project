CC		= gcc
CXX		= g++
N		= 
CFLAGS	+= -g

test-m : N = m
test-m : build-test
test-m : 

build-test : 
	$(CXX) $(CFLAGS) test/$(N).cpp -o $(N) $(LDFLAGS)