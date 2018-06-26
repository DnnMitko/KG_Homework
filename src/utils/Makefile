include $(COMMON)

SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY : all
all : _header $(OBJS)
	@$(MAKE) --no-print-directory -C SDL
	@$(MAKE) --no-print-directory -C pugixml
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╚══$(NO_COLOR)\n"

.PHONY : _header
_header :
	@$(PRINT_DEPTH_HEADER)printf "$(LABEL_COLOR)══════════[utils]══════════$(NO_COLOR)\n"

$(OBJS) : CMD = $(CC) $(INCLUDES) $(COMPILER_FLAGS) -c $< -o $@

$(OBJS) : $(OBJ_DIR)/%.o : %.cpp
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT)

.PHONY : tree
tree : _header
	@$(LIST)
	@$(MAKE) --no-print-directory -C SDL tree
	@$(MAKE) --no-print-directory -C pugixml tree
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╚══$(NO_COLOR)\n"