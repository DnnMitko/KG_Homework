SRCS = pugixml.cpp

HDRS = pugixml.hpp

OBJ_DIR = ../obj

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

CC = g++

COMPILER_FLAGS = -Wall

all : $(SRCS) $(HDRS) $(OBJS)

$(OBJS) : $(OBJ_DIR)/%.o : %.cpp
	$(CC) $(COMPILER_FLAGS) -c $< -o $@