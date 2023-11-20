# ompiler & Linker settings
CC = g++
CFLAGS = -g -Wall -std=c++11 -pthread -O3 -DNDEBUG -I./include

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
	time ./$(TARGET) testcase/sample.block testcase/sample.rpt

do2:
	time ./$(TARGET) testcase/ami33.block testcase/ami33.rpt

do3:
	time ./$(TARGET) testcase/ami49.block testcase/ami49.rpt

do4:
	time ./$(TARGET) testcase/apte.block testcase/apte.rpt

do5:
	time ./$(TARGET) testcase/hp.block testcase/hp.rpt

do6:
	time ./$(TARGET) testcase/xerox.block testcase/xerox.rpt

do7:
	time ./$(TARGET) testcase/ami49_2.block testcase/ami49_2.rpt

do8:
	time ./$(TARGET) testcase/ami49_3.block testcase/ami49_3.rpt

do9:
	time ./$(TARGET) testcase/sample300.block testcase/sample300.rpt

do10:
	time ./$(TARGET) testcase/ami49_5.block testcase/ami49_5.rpt

clean:
	rm -rf $(OBJDIR) $(TARGET) testcase/*.rpt out
