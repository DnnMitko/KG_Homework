include ../../../Makefile_Common

SRCS = SetBresenham.cpp DrawBresenham.cpp DrawRevBresenham.cpp

OBJ_DIR = ../../obj

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

CC = g++

all : header $(SRCS) $(OBJS)
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╚$(NO_COLOR)\n"

header :
	@$(PRINT_DEPTH_HEADER)printf "$(LABEL_COLOR)════════[Bresenham]════════$(NO_COLOR)\n"

$(OBJS) : CMD = $(CC) $(COMPILER_FLAGS) -c $< -o $@

$(OBJS) : $(OBJ_DIR)/%.o : %.cpp
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT)