CXXFLAGS += -O3 -std=c++11 -Wall -Wextra -pedantic-errors

all: rand-muta-neural-network

rand-muta-neural-network: Neuron.o Net.o rand-muta-neural-network.o Util.o
	$(CXX) $(CXXFLAGS) -o rand-muta-neural-network *.o

Neuron.o: Neuron.cpp Neuron.h
	$(CXX) $(CXXFLAGS) -c Neuron.cpp -o Neuron.o

Net.o: Net.cpp Net.h
	$(CXX) $(CXXFLAGS) -c Net.cpp -o Net.o

Util.o: Util.cpp Util.h
	$(CXX) $(CXXFLAGS) -c Util.cpp -o Util.o
	
rand-muta-neural-network.o: rand-muta-neural-network.cpp 
	$(CXX) $(CXXFLAGS) -c rand-muta-neural-network.cpp -o rand-muta-neural-network.o

clean:
	$(RM) *.o rand-muta-neural-network
