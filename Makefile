CXXFLAGS += -O3 -std=c++11 -Wall -Wextra -pedantic-errors

all: build/rand-muta-neural-network

build/rand-muta-neural-network: build/Neuron.o build/Net.o build/rand-muta-neural-network.o build/Util.o
	$(CXX) $(CXXFLAGS) -o build/rand-muta-neural-network build/*.o

build/Neuron.o: Neuron.cpp Neuron.h
	$(CXX) $(CXXFLAGS) -c Neuron.cpp -o build/Neuron.o

build/Net.o: Net.cpp Net.h
	$(CXX) $(CXXFLAGS) -c Net.cpp -o build/Net.o

build/Util.o: Util.cpp Util.h
	$(CXX) $(CXXFLAGS) -c Util.cpp -o build/Util.o
	
build/rand-muta-neural-network.o: rand-muta-neural-network.cpp 
	$(CXX) $(CXXFLAGS) -c rand-muta-neural-network.cpp -o build/rand-muta-neural-network.o

clean:
	$(RM) build/*.o build/rand-muta-neural-network
