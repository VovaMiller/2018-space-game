DIR_ROOT = ../..

# "Digger Offline" properties.
DIR_DO_OBJ = obj_do
DIR_DO_SRC = $(DIR_ROOT)/src
DIR_DO_INCLUDE = $(DIR_ROOT)/include
DO_HEADERS = $(wildcard $(DIR_DO_INCLUDE)/DiggerOffline/*.h)
DO_SRCS = $(patsubst $(DIR_DO_INCLUDE)/DiggerOffline/%.h,$(DIR_DO_SRC)/%.cpp,$(DO_HEADERS))
DO_OBJS = $(patsubst $(DIR_DO_SRC)/%.cpp,$(DIR_DO_OBJ)/%.o,$(DO_SRCS))

# Linker
DIR_BIN = $(DIR_ROOT)/bin/Windows
EXE = $(DIR_BIN)/DiggerOffline.exe
LIBS = -L$(DIR_BIN) -lsfml-audio-2 -lsfml-graphics-2 -lsfml-system-2 -lsfml-window-2


############
# Building #
############
all: compile_do compile_main $(EXE)

$(EXE): $(DO_OBJS) main.o
	$(CXX) $(LIBS) -o $@ $^

clean: clean_do clean_main


###############################
# Compiling "Digger Offline". #
###############################
compile_do: mkdir_obj_do $(DO_OBJS)

mkdir_obj_do:
	mkdir -p $(DIR_DO_OBJ)

$(DIR_DO_OBJ)/%.o: $(DIR_DO_SRC)/%.cpp
	$(CXX) -std=c++11 -I$(DIR_DO_INCLUDE) -c -o $@ $<

clean_do:
	rm -rf $(DIR_DO_OBJ)


######################
# Compiling main.cpp #
######################
compile_main: main.o

main.o: $(DIR_DO_SRC)/main.cpp
	$(CXX) -std=c++11 -I$(DIR_DO_INCLUDE) -c $<

clean_main:
	rm -f main.o
