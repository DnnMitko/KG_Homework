include Makefile_Common

SRCS = $(wildcard src/*.cpp)

OBJ_DIR = src/obj

OBJS = $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

EXE = run

# ============================================================================================

.PHONY : all
all : $(SRCS) $(OBJ_DIR) header $(OBJS) submodules $(EXE)

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

header :
	@$(PRINT_DEPTH_HEADER)printf "$(LABEL_COLOR)═══════════[Src]═══════════$(NO_COLOR)\n"

$(OBJS) : CMD = $(CC) $(COMPILER_FLAGS) -c $< -o $@

$(OBJS) : $(OBJ_DIR)/%.o : src/%.cpp
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT)

submodules :
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
relink : headerClean delete_executable footerClean all

# ============================================================================================

.PHONY : nolink
nolink : $(SRCS) $(OBJ_DIR) header $(OBJS) submodules

# ============================================================================================

.PHONY : tree filetree
tree : header filetree
	@printf "$(LABEL_COLOR)╚══$(NO_COLOR)\n"

filetree : $(SRCS)
	@$(LIST)
	@$(MAKE) --no-print-directory -C src/pugixml tree
	@$(MAKE) --no-print-directory -C src/grid tree
	@$(MAKE) --no-print-directory -C src/interface tree


# ============================================================================================

.PHONY : clean
clean : headerClean delete_executable delete_objects footerClean

headerClean :
	@$(PRINT_DEPTH_HEADER)printf "$(LABEL_COLOR)════════[Cleaning]═════════$(NO_COLOR)\n"

delete_executable : CMD = rm $(EXE)

delete_executable :
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT_EXE)

delete_objects : CMD = rm -r src/obj

delete_objects : $(OBJ_DIR)
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT_EXE)

footerClean :
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╚══$(NO_COLOR)\n"

# ============================================================================================