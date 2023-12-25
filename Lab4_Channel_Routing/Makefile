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
TARGET = Lab3

all: $(TARGET)

$(OBJDIR):
	mkdir $(OBJDIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) main.cpp $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

check:
	$(CHECKCC) $(CHECKFLAGS) ./$(TARGET) testcase/case7.sp testcase/s4.rpt

INV:
	time ./$(TARGET) testcase/INV.sp testcase/INV.rpt
	head -n 1 testcase/INV.rpt

NOR2:
	time ./$(TARGET) testcase/NOR2.sp testcase/NOR2.rpt
	head -n 1 testcase/NOR2.rpt

NAND4:
	time ./$(TARGET) testcase/NAND4.sp testcase/NAND4.rpt
	head -n 1 testcase/NAND4.rpt

s1:
	time ./$(TARGET) testcase/s1.sp testcase/s1.rpt
	head -n 1 testcase/s1.rpt

s2:
	time ./$(TARGET) testcase/s2.sp testcase/s2.rpt
	head -n 1 testcase/s2.rpt

s3:
	time ./$(TARGET) testcase/ASYNC_DFFHx1_ASAP7_75t_R.sp testcase/s3.rpt
	head -n 1 testcase/s3.rpt

s4:
	time ./$(TARGET) testcase/case7.sp testcase/s4.rpt
	head -n 1 testcase/s4.rpt

s5:
	time ./$(TARGET) testcase/dff_mtspc.sp testcase/s5.rpt
	head -n 1 testcase/s5.rpt

s6:
	time ./$(TARGET) testcase/XOR8.sp testcase/s6.rpt
	head -n 1 testcase/s6.rpt

s7:
	time ./$(TARGET) testcase/s7.sp testcase/s7.rpt
	head -n 1 testcase/s7.rpt

verify:
	chmod +x verifier/SolutionChecker
	./verifier/SolutionChecker testcase/INV.sp testcase/INV.rpt
	./verifier/SolutionChecker testcase/NOR2.sp testcase/NOR2.rpt
	./verifier/SolutionChecker testcase/NAND4.sp testcase/NAND4.rpt
	./verifier/SolutionChecker testcase/s1.sp testcase/s1.rpt
	./verifier/SolutionChecker testcase/s2.sp testcase/s2.rpt
	./verifier/SolutionChecker testcase/ASYNC_DFFHx1_ASAP7_75t_R.sp testcase/s3.rpt
	./verifier/SolutionChecker testcase/case7.sp testcase/s4.rpt
	./verifier/SolutionChecker testcase/dff_mtspc.sp testcase/s5.rpt
	./verifier/SolutionChecker testcase/XOR8.sp testcase/s6.rpt
	./verifier/SolutionChecker testcase/s7.sp testcase/s7.rpt

clean:
	rm -rf $(OBJDIR) $(TARGET) testcase/*.rpt log
