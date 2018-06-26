include $(COMMON)

SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY : all
all : _header $(OBJS)
	@$(MAKE) --no-print-directory -C bresenham
	@$(MAKE) --no-print-directory -C boundry_full
	@$(MAKE) --no-print-directory -C michener
	@$(MAKE) --no-print-directory -C spline
	@$(MAKE) --no-print-directory -C liang_barsky
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╚══$(NO_COLOR)\n"

.PHONY : _header
_header :
	@$(PRINT_DEPTH_HEADER)printf "$(LABEL_COLOR)══════════[grid]═══════════$(NO_COLOR)\n"

$(OBJS) : CMD = $(CC) $(INCLUDES) $(COMPILER_FLAGS) -c $< -o $@

$(OBJS) : $(OBJ_DIR)/%.o : %.cpp
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT)

.PHONY : tree
tree : _header
	@$(LIST)
	@$(MAKE) --no-print-directory -C bresenham tree
	@$(MAKE) --no-print-directory -C boundry_full tree
	@$(MAKE) --no-print-directory -C michener tree
	@$(MAKE) --no-print-directory -C spline tree
	@$(MAKE) --no-print-directory -C liang_barsky tree
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╚══$(NO_COLOR)\n"