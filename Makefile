
# Makefile for CS 70 HashSet
#

CXX = clang++
CXXFLAGS = -g -std=c++17 -Wall -Wextra -pedantic -I$(CURDIR)
LD = clang++
LDLIBS = -L/usr/lib/cs70lib -listring -ltestinglogger -lstringhashtest
TARGETS = stringhash-test hashset-cow-test hashset-test

# Note: The rules below use useful-but-cryptic make "Automatic variables"
#       to avoid duplicating information in multiple places, the most useful
#       of which are:
#
#   $@  The file name of the target of the rule
#   $^  The names of all the prerequisites, with spaces between them.
#   $<  The name of the first prerequisite
#
# For GNU make, you'll find that it supports quite an extensive list, at
#   http://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
# The most commonly used and supported are $@, $<, $?, $* and $^

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
	rm -rf *.o

stringhash-test: stringhash.o
	$(LD) $(LDFLAGS) $^ -o $@ $(LDLIBS)

hashset-cow-test: hashset-cow-test.o 
	$(LD) $(LDFLAGS) $^ -o $@ -L/usr/lib/cs70lib -ltestinglogger

hashset-test: hashset-test.o stringhash.o
	$(LD) $(LDFLAGS) $^ -o $@ -L/usr/lib/cs70lib -ltestinglogger

hashset-cow-test.o: hashset-cow-test.cpp hashset.hpp hashset-private.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

hashset-test.o: hashset-test.cpp hashset.hpp hashset-private.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

stringhash.o: stringhash.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
