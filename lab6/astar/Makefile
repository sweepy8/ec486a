CXX=g++
CXXFLAGS=-O3

SPEC_FLAGS=-DSPEC_CPU

all:
	$(CXX) $(CXXFLAGS) $(SPEC_FLAGS) -c CreateWay_.cpp
	$(CXX) $(CXXFLAGS) $(SPEC_FLAGS) -c Library.cpp
	$(CXX) $(CXXFLAGS) $(SPEC_FLAGS) -c Places_.cpp
	$(CXX) $(CXXFLAGS) $(SPEC_FLAGS) -c Random.cpp
	$(CXX) $(CXXFLAGS) $(SPEC_FLAGS) -c RegBounds_.cpp
	$(CXX) $(CXXFLAGS) $(SPEC_FLAGS) -c Region_.cpp
	$(CXX) $(CXXFLAGS) $(SPEC_FLAGS) -c RegMng_.cpp
	$(CXX) $(CXXFLAGS) $(SPEC_FLAGS) -c RegWay_.cpp
	$(CXX) $(CXXFLAGS) $(SPEC_FLAGS) -c Way2_.cpp
	$(CXX) $(CXXFLAGS) $(SPEC_FLAGS) -c Way_.cpp
	$(CXX) $(CXXFLAGS) $(SPEC_FLAGS) -c WayInit_.cpp
	$(CXX) -o astar CreateWay_.o Library.o Places_.o Random.o Region_.o RegBounds_.o RegMng_.o RegWay_.o Way2_.o Way_.o WayInit_.o

clean:
	rm -f astar *.o
