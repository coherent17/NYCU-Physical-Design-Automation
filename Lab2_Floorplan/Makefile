# ompiler & Linker settings
CC = g++
CFLAGS = -g -Wall -std=c++11 -pthread -O3 -I./include

# Valgrind for memory issue
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s --show-leak-kinds=all --track-origins=yes 

# Source files and object files
SRCDIR = src
OBJDIR = obj
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Name of the executable
TARGET = Floorplan

all: $(TARGET)

$(OBJDIR):
	mkdir $(OBJDIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) main.cpp $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

check:
	$(CHECKCC) $(CHECKFLAGS) time ./$(TARGET) testcase/sample1.dat testcase/sample1.out

do1:
	./$(TARGET) testcase/sample.block

do2:
	./$(TARGET) testcase/ami33.block testcase/ami33.rpt

do3:
	./$(TARGET) testcase/ami49.block

do4:
	./$(TARGET) testcase/apte.block

do5:
	./$(TARGET) testcase/hp.block

do6:
	./$(TARGET) testcase/xerox.block

do7:
	time ./$(TARGET) testcase/sample300.block

clean:
	rm -rf $(OBJDIR) $(TARGET) testcase/*.out out
