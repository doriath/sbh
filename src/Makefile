CXXFLAGS=-g -Wall
TARGETS=$(BINDIR)sbh_lib.o $(BINDIR)sbh_general $(BINDIR)sbh_positive $(BINDIR)sbh_check
BINDIR=../bin/

all: clean $(TARGETS)

clean:
	$(RM) $(BINDIR)*

$(BINDIR)sbh_lib.o: sbh_lib.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

$(BINDIR)sbh_general: sbh_general.cpp $(BINDIR)sbh_lib.o
	$(CXX) $(CXXFLAGS) $? $(LDFLAGS) -o $@

$(BINDIR)sbh_positive: sbh_positive.cpp $(BINDIR)sbh_lib.o
	$(CXX) $(CXXFLAGS) $? $(LDFLAGS) -o $@

$(BINDIR)sbh_check: sbh_check.cpp $(BINDIR)sbh_lib.o
	$(CXX) $(CXXFLAGS) $? $(LDFLAGS) -o $@
