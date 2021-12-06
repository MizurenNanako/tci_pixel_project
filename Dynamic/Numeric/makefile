N		= 
O		= 

test-m : N = m
test-m : O = rational.cpp
test-m : $(O) build-test

build-test : $(O)
	$(CXX) $(CPPFLAGS) ./test/$(N).cpp $(O) $(LDFLAGS) -o $(N)
