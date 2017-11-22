include Makefile_Common

SRCS = src/main.cpp

OBJ_DIR = src/obj

OBJS = $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

export CC = g++

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

EXE = run

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
	@printf "$(LABEL_COLOR)╚$(NO_COLOR)\n"

$(EXE) : CMD = $(CC) $(OBJ_DIR)/*.o $(LINKER_FLAGS) -o $(EXE)

$(EXE) :
	@$(PRINT_DEPTH_HEADER)printf "$(LABEL_COLOR)═══[Linking executable]════$(NO_COLOR)\n"
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT_EXE)
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╚$(NO_COLOR)\n"

clean : headerClean remove_exe remove_obj
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╚$(NO_COLOR)\n"

headerClean :
	@$(PRINT_DEPTH_HEADER)printf "$(LABEL_COLOR)════════[Cleaning]═════════$(NO_COLOR)\n"

remove_exe : CMD = rm $(EXE)

remove_exe :
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT_EXE)

remove_obj : CMD = rm -r src/obj

remove_obj : $(OBJ_DIR)
	@$(PRINT_DEPTH)printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT_EXE)