all:
	$(CXX) $(CXXFLAGS) -c expr.cpp
	$(CXX) $(CXXFLAGS) -c interpreter.cpp
	$(CXX) $(CXXFLAGS) -o freeduce expr.o interpreter.o

clean:
	rm -f freeduce *.o
