include $(COMMON)

SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY : all
all : _header $(OBJS)
	@$(MAKE) --no-print-directory -C grid
	@$(MAKE) --no-print-directory -C interface
	@$(MAKE) --no-print-directory -C utils
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╚══$(NO_COLOR)\n"

.PHONY : _header
_header :
	@$(PRINT_DEPTH_HEADER)printf "$(LABEL_COLOR)═══════════[src]═══════════$(NO_COLOR)\n"

$(OBJS) : CMD = $(CC) $(INCLUDES) $(COMPILER_FLAGS) -c $< -o $@

$(OBJS) : $(OBJ_DIR)/%.o : %.cpp
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT)

.PHONY : tree
tree : _header
	@$(LIST)
	@$(MAKE) --no-print-directory -C grid tree
	@$(MAKE) --no-print-directory -C interface tree
	@$(MAKE) --no-print-directory -C utils tree
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╚══$(NO_COLOR)\n"