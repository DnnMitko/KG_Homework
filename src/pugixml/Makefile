include ../../Makefile_Common

SRCS = pugixml.cpp

HDRS = pugixml.hpp

OBJ_DIR = ../obj

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

CC = g++

all : $(SRCS) $(HDRS) $(OBJS)
	@:

$(OBJS) : CMD = $(CC) $(COMPILER_FLAGS) -c $< -o $@

$(OBJS) : $(OBJ_DIR)/%.o : %.cpp
	@printf "$(LABEL_COLOR)╠═$(NO_COLOR)";$(PRINT)