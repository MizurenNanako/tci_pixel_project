CC		= gcc
CXX		= g++
N		= 
CFLAGS	+= -g

test-vec : N = t_vec
test-vec : build-test

test-mat : N = t_mat
test-mat : build-test

build-test : 
	$(CXX) $(CFLAGS) test/$(N).cpp -o t$(N) $(LDFLAGS)