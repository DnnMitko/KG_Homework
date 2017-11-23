include $(COMMON)

SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY : all
all : header $(SRCS) $(OBJS)
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╚══$(NO_COLOR)\n"

.PHONY : header
header :
	@$(PRINT_DEPTH_HEADER)printf "$(LABEL_COLOR)═════════[PugiXML]═════════$(NO_COLOR)\n"

$(OBJS) : CMD = $(CC) $(COMPILER_FLAGS) -c $< -o $@

$(OBJS) : $(OBJ_DIR)/%.o : %.cpp
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT)

.PHONY : tree
tree : $(SRCS) header
	@$(LIST)
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╚══$(NO_COLOR)\n"