# James Dunlap
# jcd160230@utdallas.edu
# cs3377.501

CXX = g++
CXXFLAGS = -Wall -g -std=c++11
CPPFLAGS = -I/scratch/perkins/include -Wno-write-strings
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses 


# PROJECTNAME is a descriptive name used for the backup target
EXECFILE = cdk

OBJS = cdk.o

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

