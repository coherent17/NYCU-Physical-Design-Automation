# ompiler & Linker settings
CC = g++
CFLAGS = -g -Wall -march=native -flto -funroll-loops -finline-functions -ffast-math -std=c++11 -pthread -O3 -DNDEBUG -I./include
#CFLAGS = -g -Wall -std=c++11 -pthread -O3 -I./include

# Valgrind for memory issue
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s --show-leak-kinds=all --track-origins=yes 

# Source files and object files
SRCDIR = src
OBJDIR = obj
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Name of the executable
TARGET = Lab4

all: $(TARGET)

$(OBJDIR):
	mkdir $(OBJDIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) main.cpp $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

check:
	$(CHECKCC) $(CHECKFLAGS) ./$(TARGET) testcase/case7.sp testcase/s4.rpt

s1:
	time ./$(TARGET) testcase/sample.in testcase/sample.out

s2:
	time ./$(TARGET) testcase/text_sample.in testcase/sample.out

clean:
	rm -rf $(OBJDIR) $(TARGET) testcase/*.out
