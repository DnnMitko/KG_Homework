export COMMON = $(PWD)/Makefile_Common

include $(COMMON)

.NOTPARALLEL :

MAKEFLAGS += -Otarget

SRCS = $(wildcard src/*.cpp)

export OBJ_DIR = $(PWD)/obj

OBJS = $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

EXE = run

# ============================================================================================

.PHONY : all
all : $(OBJ_DIR) _header $(OBJS) _submodules $(EXE)

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

.PHONY : _header
_header :
	@$(PRINT_DEPTH_HEADER)printf "$(LABEL_COLOR)═══════════[Src]═══════════$(NO_COLOR)\n"

$(OBJS) : CMD = $(CC) $(COMPILER_FLAGS) -c $< -o $@

$(OBJS) : $(OBJ_DIR)/%.o : src/%.cpp
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT)

.PHONY : _submodules
_submodules :
	@$(MAKE) --no-print-directory -C src/pugixml
	@$(MAKE) --no-print-directory -C src/grid
	@$(MAKE) --no-print-directory -C src/interface
	@printf "$(LABEL_COLOR)╚══$(NO_COLOR)\n"

$(EXE) : CMD = $(CC) $(OBJ_DIR)/*.o $(LINKER_FLAGS) -o $(EXE)

$(EXE) :
	@$(PRINT_DEPTH_HEADER)printf "$(LABEL_COLOR)═══[Linking executable]════$(NO_COLOR)\n"
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT_EXE)
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╚══$(NO_COLOR)\n"

# ============================================================================================

.PHONY : help
help : TARGET_COLOR = \033[01;35m

help :
	@printf "$(TARGET_COLOR)\"all\" or leave blank$(LABEL_COLOR):\n\
    1. Builds source files.\n\
    2. If there is no executable, links one together.\n\n"
	@printf "$(TARGET_COLOR)\"relink\"$(LABEL_COLOR):\n\
    1. Deletes executable.\n\
    2. Builds source files.\n\
    3. Links executable.\n\n"
	@printf "$(TARGET_COLOR)\"nolink\"$(LABEL_COLOR):\n\
    1. Builds source files.\n\n"
	@printf "$(TARGET_COLOR)\"tree\"$(LABEL_COLOR):\n\
    1. Print source tree.\n\n"
	@printf "$(TARGET_COLOR)\"clean\"$(LABEL_COLOR):\n\
    1. Deletes executable.\n\
    2. Deletes objects directory.\n\n"
	@printf "$(TARGET_COLOR)\"delete_executable\"$(LABEL_COLOR):\n\
    1. Deletes executable.\n\n"
	@printf "$(TARGET_COLOR)\"delete_objects\"$(LABEL_COLOR):\n\
    1. Deletes objects directory.\n\n"

# ============================================================================================

.PHONY : relink
relink : _headerClean delete_executable _footerClean all

# ============================================================================================

.PHONY : nolink
nolink : $(OBJ_DIR) _header $(OBJS) _submodules

# ============================================================================================

.PHONY : tree
tree : _header
	@$(LIST)
	@$(MAKE) --no-print-directory -C src/pugixml tree
	@$(MAKE) --no-print-directory -C src/grid tree
	@$(MAKE) --no-print-directory -C src/interface tree
	@printf "$(LABEL_COLOR)╚══$(NO_COLOR)\n"

# ============================================================================================

.PHONY : clean
clean : _headerClean delete_executable delete_objects _footerClean

.PHONY : _headerClean
_headerClean :
	@$(PRINT_DEPTH_HEADER)printf "$(LABEL_COLOR)════════[Cleaning]═════════$(NO_COLOR)\n"

.PHONY : delete_executable
delete_executable : CMD = rm $(EXE)

delete_executable :
	@-$(PRINT_DEPTH)printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT_EXE)

.PHONY : delete_objects
delete_objects : CMD = rm -r $(OBJ_DIR)

delete_objects : $(OBJ_DIR)
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT_EXE)

.PHONY : _footerClean
_footerClean :
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╚══$(NO_COLOR)\n"

# ============================================================================================