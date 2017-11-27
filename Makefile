export COMMON = $(PWD)/Makefile_Common

include $(COMMON)

.NOTPARALLEL :

MAKEFLAGS += -Otarget

SRCDIR = src

export OBJ_DIR = $(PWD)/obj

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

EXE = run

# ============================================================================================

.PHONY : all
all : $(OBJ_DIR) _submodules $(EXE)

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

.PHONY : _submodules
_submodules :
	@$(MAKE) --no-print-directory -C $(SRCDIR)

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
    2. If there is no executable, links one together.$(NO_COLOR)\n\n"
	@printf "$(TARGET_COLOR)\"link\"$(LABEL_COLOR):\n\
    1. Deletes executable.\n\
    2. Links executable.$(NO_COLOR)\n\n"
	@printf "$(TARGET_COLOR)\"relink\"$(LABEL_COLOR):\n\
    1. Deletes executable.\n\
    2. Builds source files.\n\
    3. Links executable.$(NO_COLOR)\n\n"
	@printf "$(TARGET_COLOR)\"nolink\"$(LABEL_COLOR):\n\
    1. Builds source files.$(NO_COLOR)\n\n"
	@printf "$(TARGET_COLOR)\"tree\"$(LABEL_COLOR):\n\
    1. Print source tree.$(NO_COLOR)\n\n"
	@printf "$(TARGET_COLOR)\"clean\"$(LABEL_COLOR):\n\
    1. Deletes executable.\n\
    2. Deletes objects directory.$(NO_COLOR)\n\n"
	@printf "$(TARGET_COLOR)\"delete_executable\"$(LABEL_COLOR):\n\
    1. Deletes executable.$(NO_COLOR)\n\n"
	@printf "$(TARGET_COLOR)\"delete_objects\"$(LABEL_COLOR):\n\
    1. Deletes objects directory.$(NO_COLOR)\n\n"

# ============================================================================================

.PHONY : link
link : _headerClean delete_executable _footerClean $(EXE)

# ============================================================================================

.PHONY : relink
relink : _headerClean delete_executable _footerClean all

# ============================================================================================

.PHONY : nolink
nolink : $(OBJ_DIR) _submodules

# ============================================================================================

.PHONY : tree
tree :
	@$(MAKE) --no-print-directory -C $(SRCDIR) tree

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
