include ../../Makefile_Common

SRCS = Button.cpp Interface.cpp InterfaceButtons.cpp Label.cpp TextField.cpp

HDRS = Button.h Interface.h Label.h TextField.h

OBJ_DIR = ../obj

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

CC = g++

all : $(SRCS) $(HDRS) $(OBJS)
	@:

$(OBJS) : CMD = $(CC) $(COMPILER_FLAGS) -c $< -o $@

$(OBJS) : $(OBJ_DIR)/%.o : %.cpp
	@printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT)