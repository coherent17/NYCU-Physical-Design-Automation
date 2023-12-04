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

sample:
	time ./$(TARGET) testcase/sample.block testcase/sample.rpt
	./visualize/floorplan_visualize -i testcase/sample.block -o testcase/sample.rpt -p sample -d

ami33:
	time ./$(TARGET) testcase/ami33.block testcase/ami33.rpt
	./visualize/floorplan_visualize -i testcase/ami33.block -o testcase/ami33.rpt -p ami33 -d

ami49:
	time ./$(TARGET) testcase/ami49.block testcase/ami49.rpt
	./visualize/floorplan_visualize -i testcase/ami49.block -o testcase/ami49.rpt -p ami49 -d

apte:
	time ./$(TARGET) testcase/apte.block testcase/apte.rpt
	./visualize/floorplan_visualize -i testcase/apte.block -o testcase/apte.rpt -p apte -d

hp:
	time ./$(TARGET) testcase/hp.block testcase/hp.rpt
	./visualize/floorplan_visualize -i testcase/hp.block -o testcase/hp.rpt -p hp -d

xerox:
	time ./$(TARGET) testcase/xerox.block testcase/xerox.rpt
	./visualize/floorplan_visualize -i testcase/xerox.block -o testcase/xerox.rpt -p xerox -d

ami49_3:
	time ./$(TARGET) testcase/ami49_3.block testcase/ami49_3.rpt
	./visualize/floorplan_visualize -i testcase/ami49_3.block -o testcase/ami49_3.rpt -p ami49_3 -d

ami49_5:
	time ./$(TARGET) testcase/ami49_5.block testcase/ami49_5.rpt
	./visualize/floorplan_visualize -i testcase/ami49_5.block -o testcase/ami49_5.rpt -p ami49_5 -d

ami49_6:
	time ./$(TARGET) testcase/ami49_6.block testcase/ami49_6.rpt
	./visualize/floorplan_visualize -i testcase/ami49_6.block -o testcase/ami49_6.rpt -p ami49_6 -d

ami49_9:
	time ./$(TARGET) testcase/ami49_9.block testcase/ami49_9.rpt
	./visualize/floorplan_visualize -i testcase/ami49_9.block -o testcase/ami49_9.rpt -p ami49_9 -d

boundary_case1:
	time ./$(TARGET) testcase/boundary_case1.block testcase/boundary_case1.rpt
	./visualize/floorplan_visualize -i testcase/boundary_case1.block -o testcase/boundary_case1.rpt -p boundary_case1 -d

boundary_case2:
	time ./$(TARGET) testcase/boundary_case2.block testcase/boundary_case2.rpt
	./visualize/floorplan_visualize -i testcase/boundary_case2.block -o testcase/boundary_case2.rpt -p boundary_case2 -d

t300:
	time ./$(TARGET) testcase/t300.block testcase/t300.rpt
	./visualize/floorplan_visualize -i testcase/t300.block -o testcase/t300.rpt -p t300 -d

c1:
	time ./$(TARGET) testcase/case1.txt testcase/case1.rpt
	./visualize/floorplan_visualize -i testcase/case1.txt -o testcase/case1.rpt -p case1 -d

c2:
	time ./$(TARGET) testcase/case2.txt testcase/case2.rpt
	./visualize/floorplan_visualize -i testcase/case2.txt -o testcase/case2.rpt -p case2 -d

c3:
	time ./$(TARGET) testcase/case3.txt testcase/case3.rpt
	./visualize/floorplan_visualize -i testcase/case3.txt -o testcase/case3.rpt -p case3 -d

c4:
	time ./$(TARGET) testcase/case4.txt testcase/case4.rpt
	./visualize/floorplan_visualize -i testcase/case4.txt -o testcase/case4.rpt -p case4 -d

c5:
	time ./$(TARGET) testcase/case5.txt testcase/case5.rpt
	./visualize/floorplan_visualize -i testcase/case5.txt -o testcase/case5.rpt -p case5 -d

c6:
	time ./$(TARGET) testcase/case6.txt testcase/case6.rpt
	./visualize/floorplan_visualize -i testcase/case6.txt -o testcase/case6.rpt -p case6 -d

clean:
	rm -rf $(OBJDIR) $(TARGET) testcase/*.rpt out *.png
