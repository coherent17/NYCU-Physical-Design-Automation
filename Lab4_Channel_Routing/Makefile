# ompiler & Linker settings
CC = g++
#CFLAGS = -g -Wall -march=native -flto -funroll-loops -finline-functions -ffast-math -std=c++11 -pthread -O3 -I./include
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

s:
	time ./$(TARGET) testcase/sample.txt testcase/sample.out

do1:
	time ./$(TARGET) testcase/input1.txt testcase/input1.out

do2:
	time ./$(TARGET) testcase/input2.txt testcase/input2.out

do3:
	time ./$(TARGET) testcase/input3.txt testcase/input3.out

do4:
	time ./$(TARGET) testcase/input4.txt testcase/input4.out

do5:
	time ./$(TARGET) testcase/input5.txt testcase/input5.out

do6:
	time ./$(TARGET) testcase/input6.txt testcase/input6.out

do7:
	time ./$(TARGET) testcase/input7.txt testcase/input7.out

do8:
	time ./$(TARGET) testcase/input8.txt testcase/input8.out

do9:
	time ./$(TARGET) testcase/input9.txt testcase/input9.out

do10:
	time ./$(TARGET) testcase/input10.txt testcase/input10.out

clean:
	rm -rf $(OBJDIR) $(TARGET) testcase/*.out
