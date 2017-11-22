include ../../Makefile_Common

SRCS = Grid.cpp

OBJ_DIR = ../obj

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

CC = g++

all : header $(SRCS) $(OBJS)
	@$(MAKE) --no-print-directory -C bresenham
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╚$(NO_COLOR)\n"

header :
	@$(PRINT_DEPTH_HEADER)printf "$(LABEL_COLOR)╦══════════[Grid]═══════════$(NO_COLOR)\n"

$(OBJS) : CMD = $(CC) $(COMPILER_FLAGS) -c $< -o $@

$(OBJS) : $(OBJ_DIR)/%.o : %.cpp
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT)