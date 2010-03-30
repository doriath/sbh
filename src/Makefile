CXXFLAGS=-O2 -g -Wall
TARGETS=brute-force
BINDIR=../bin/

all: $(TARGETS)

clean:
	$(RM) $(BINDIR)*

brute-force: brute-force.cpp
	$(CXX) $(CXXFLAGS) $? $(LDFLAGS) -o $(BINDIR)$@
