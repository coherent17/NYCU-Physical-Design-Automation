# ompiler & Linker settings
CC = g++
#CFLAGS = -g -Wall -std=c++11 -pthread -O3 -DNDEBUG -I./include
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
TARGET = Lab3

all: $(TARGET)

$(OBJDIR):
	mkdir $(OBJDIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) main.cpp $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

check:
	$(CHECKCC) $(CHECKFLAGS) time ./$(TARGET) testcase/NOR2.sp testcase/NOR2.rpt

NOR2:
	./$(TARGET) testcase/NOR2.sp testcase/NOR2.rpt

NAND4:
	./$(TARGET) testcase/NAND4.sp testcase/NAND4.rpt

s1:
	./$(TARGET) testcase/s1.sp testcase/s1.rpt

s2:
	./$(TARGET) testcase/s2.sp testcase/s2.rpt

s3:
	./$(TARGET) testcase/ASYNC_DFFHx1_ASAP7_75t_R.sp testcase/s3.rpt

clean:
	rm -rf $(OBJDIR) $(TARGET) testcase/*.rpt
