include ../../Makefile_Common

SRCS = Grid.cpp

HDRS = Grid.h

OBJ_DIR = ../obj

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

CC = g++

all : $(SRCS) $(HDRS) $(OBJS)
	@printf "$(LABEL_COLOR)╠══╦══════[Bresenham]══════════$(NO_COLOR)\n"
	@$(MAKE) --no-print-directory -C bresenham

$(OBJS) : CMD = $(CC) $(COMPILER_FLAGS) -c $< -o $@

$(OBJS) : $(OBJ_DIR)/%.o : %.cpp
	@printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT)