# ompiler & Linker settings
CC = g++
CFLAGS = -g -Wall -O3 -I./include

# Valgrind for memory issue
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s --show-leak-kinds=all --track-origins=yes 

# Source files and object files
SRCDIR = src
OBJDIR = obj
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Name of the executable
TARGET = main

all: $(TARGET)

$(OBJDIR):
	mkdir $(OBJDIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) main.cpp $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

check:
	$(CHECKCC) $(CHECKFLAGS) ./$(TARGET) testcase/sample.dat

do1:
	time ./$(TARGET) testcase/input.hgr testcase/input.hgr.out
	./verifier/verifier testcase/input.hgr testcase/input.hgr.out

do2:
	time ./$(TARGET) testcase/input2.txt.hgr testcase/input2.txt.hgr.out
	./verifier/verifier testcase/input2.txt.hgr testcase/input2.txt.hgr.out

do3:
	time ./$(TARGET) testcase/input3.txt.hgr testcase/input3.txt.hgr.out
	./verifier/verifier testcase/input3.txt.hgr testcase/input3.txt.hgr.out

do4:
	time ./$(TARGET) testcase/input4.hgr testcase/input4.hgr.out
	./verifier/verifier testcase/input4.hgr testcase/input4.hgr.out

s:
	./$(TARGET) testcase/sample.dat

clean:
	rm -rf $(OBJDIR) $(TARGET) testcase/*.out testcase/*.part.2