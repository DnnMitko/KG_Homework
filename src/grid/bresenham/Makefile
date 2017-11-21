include ../../../Makefile_Common

SRCS = SetBresenham.cpp DrawBresenham.cpp DrawRevBresenham.cpp

OBJ_DIR = ../../obj

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

CC = g++

all : $(SRCS) $(OBJS)

$(OBJS) : CMD = $(CC) $(COMPILER_FLAGS) -c $< -o $@

$(OBJS) : $(OBJ_DIR)/%.o : %.cpp
	@printf "   ";$(PRINT)