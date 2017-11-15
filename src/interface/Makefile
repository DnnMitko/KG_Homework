SRCS = Button.cpp Interface.cpp InterfaceButtons.cpp Label.cpp TextField.cpp

HDRS = Button.h Interface.h Label.h TextField.h

OBJ_DIR = ../obj

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

CC = g++

COMPILER_FLAGS = -Wall

all : $(SRCS) $(HDRS) $(OBJS)

$(OBJS) : $(OBJ_DIR)/%.o : %.cpp
	$(CC) $(COMPILER_FLAGS) -c $< -o $@