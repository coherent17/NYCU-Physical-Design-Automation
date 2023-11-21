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
	./visualize/floorplan_visualize -i testcase/sample.block -o testcase/sample.rpt -p sample -d

do2:
	time ./$(TARGET) testcase/ami33.block testcase/ami33.rpt
	./visualize/floorplan_visualize -i testcase/ami33.block -o testcase/ami33.rpt -p ami33 -d

do3:
	time ./$(TARGET) testcase/ami49.block testcase/ami49.rpt
	./visualize/floorplan_visualize -i testcase/ami49.block -o testcase/ami49.rpt -p ami49 -d

do4:
	time ./$(TARGET) testcase/apte.block testcase/apte.rpt
	./visualize/floorplan_visualize -i testcase/apte.block -o testcase/apte.rpt -p apte -d

do5:
	time ./$(TARGET) testcase/hp.block testcase/hp.rpt
	./visualize/floorplan_visualize -i testcase/hp.block -o testcase/hp.rpt -p hp -d

do6:
	time ./$(TARGET) testcase/xerox.block testcase/xerox.rpt
	./visualize/floorplan_visualize -i testcase/xerox.block -o testcase/xerox.rpt -p xerox -d

do7:
	time ./$(TARGET) testcase/ami49_2.block testcase/ami49_2.rpt
	./visualize/floorplan_visualize -i testcase/ami49_2.block -o testcase/ami49_2.rpt -p ami49_2 -d

do8:
	time ./$(TARGET) testcase/ami49_3.block testcase/ami49_3.rpt
	./visualize/floorplan_visualize -i testcase/ami49_3.block -o testcase/ami49_3.rpt -p ami49_3 -d

do9:
	time ./$(TARGET) testcase/sample300.block testcase/sample300.rpt
	./visualize/floorplan_visualize -i testcase/sample300.block -o testcase/sample300.rpt -p sample300 -d

do10:
	time ./$(TARGET) testcase/ami49_5.block testcase/ami49_5.rpt
	./visualize/floorplan_visualize -i testcase/ami49_5.block -o testcase/ami49_5.rpt -p ami49_5 -d

do11:
	time ./$(TARGET) testcase/ami49_6.block testcase/ami49_6.rpt
	./visualize/floorplan_visualize -i testcase/ami49_6.block -o testcase/ami49_6.rpt -p ami49_6 -d

do12:
	time ./$(TARGET) testcase/ami49_9.block testcase/ami49_9.rpt
	./visualize/floorplan_visualize -i testcase/ami49_9.block -o testcase/ami49_9.rpt -p ami49_9 -d

do13:
	time ./$(TARGET) testcase/boundary_case1.block testcase/boundary_case1.rpt
	./visualize/floorplan_visualize -i testcase/boundary_case1.block -o testcase/boundary_case1.rpt -p boundary_case1 -d

do14:
	time ./$(TARGET) testcase/boundary_case2.block testcase/boundary_case2.rpt
	./visualize/floorplan_visualize -i testcase/boundary_case2.block -o testcase/boundary_case2.rpt -p boundary_case2 -d

do15:
	time ./$(TARGET) testcase/t300.txt testcase/t300.rpt
	./visualize/floorplan_visualize -i testcase/t300.txt -o testcase/t300.rpt -p t300 -d

clean:
	rm -rf $(OBJDIR) $(TARGET) testcase/*.rpt out
