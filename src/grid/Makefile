include ../../Makefile_Common

SRCS = $(wildcard *.cpp)

OBJ_DIR = ../obj

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all : header $(SRCS) $(OBJS)
	@$(MAKE) --no-print-directory -C bresenham
	@$(MAKE) --no-print-directory -C michener
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╚══$(NO_COLOR)\n"

header :
	@$(PRINT_DEPTH_HEADER)printf "$(LABEL_COLOR)══════════[Grid]═══════════$(NO_COLOR)\n"

$(OBJS) : CMD = $(CC) $(COMPILER_FLAGS) -c $< -o $@

$(OBJS) : $(OBJ_DIR)/%.o : %.cpp
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT)

.PHONY : tree
tree : $(SRCS) header
	@$(LIST)
	@$(MAKE) --no-print-directory -C bresenham tree
	@$(MAKE) --no-print-directory -C michener tree
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╚══$(NO_COLOR)\n"