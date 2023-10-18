# ompiler & Linker settings
CC = g++
CFLAGS = -g -Wall -std=c++11 -DNDEBUG -pthread -O3 -I./include

# Valgrind for memory issue
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s --show-leak-kinds=all --track-origins=yes 

# Source files and object files
SRCDIR = src
OBJDIR = obj
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Name of the executable
TARGET = Lab1

all: $(TARGET)

$(OBJDIR):
	mkdir $(OBJDIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) main.cpp $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

check:
	$(CHECKCC) $(CHECKFLAGS) time ./$(TARGET) testcase/sample1.dat testcase/sample1.out

s1:
	time ./$(TARGET) testcase/sample1.dat testcase/sample1.out
	./verifier/SolutionChecker testcase/sample1.dat	testcase/sample1.out

s2:
	time ./$(TARGET) testcase/sample2.dat testcase/sample2.out
	./verifier/SolutionChecker testcase/sample2.dat	testcase/sample2.out

s3:
	time ./$(TARGET) testcase/sample3.dat testcase/sample3.out
	./verifier/SolutionChecker testcase/sample3.dat	testcase/sample3.out

do0:
	time ./$(TARGET) testcase/input_0.dat testcase/input_0.out
	./verifier/SolutionChecker testcase/input_0.dat testcase/input_0.out

do1:
	time ./$(TARGET) testcase/input_1.dat testcase/input_1.out
	./verifier/SolutionChecker testcase/input_1.dat testcase/input_1.out

do2:
	time ./$(TARGET) testcase/input_2.dat testcase/input_2.out
	./verifier/SolutionChecker testcase/input_2.dat testcase/input_2.out

do3:
	time ./$(TARGET) testcase/input_3.dat testcase/input_3.out
	./verifier/SolutionChecker testcase/input_3.dat testcase/input_3.out

do4:
	time ./$(TARGET) testcase/input_4.dat testcase/input_4.out
	./verifier/SolutionChecker testcase/input_4.dat testcase/input_4.out

do5:
	time ./$(TARGET) testcase/input_5.dat testcase/input_5.out
	./verifier/SolutionChecker testcase/input_5.dat testcase/input_5.out

runall:
	perl run_case.pl

clean:
	rm -rf $(OBJDIR) $(TARGET) testcase/*.out log report*