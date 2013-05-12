#
# Based off of the Makefile Chris Patton made for our CSC 476 project.
# And when I say based, I mean I changed about 2 lines.
# :D
#

SRC_DIR = src
OBJ_DIR = obj

INCS = $(SRC_DIR) third_party/glm/
WARN = all extra

SRCS = $(shell find $(SRC_DIR) -name "*.cpp")
DEPS = $(shell find $(SRC_DIR) -name "*.h")
OBJS = $(patsubst $(SRC_DIR)/%.o,$(OBJ_DIR)/%.o,$(SRCS:.cpp=.o))
SRC_SUB_DIRS = $(shell find $(SRC_DIR) -type d)
OBJ_SUB_DIRS = $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SRC_SUB_DIRS))
EXEC = $(shell basename `pwd`)

CXX = g++
CFLAGS = -pipe $(foreach d,$(INCS),-I$d) $(foreach d,$(WARN),-W$d)
LD = g++
LDFLAGS =

.PHONY: all run debug release profile prepare clean remove

all: debug
run: all
debug: CFLAGS += -g
debug: DEFS += DEBUG
release: CFLAGS += -Ofast
release: DEFS += NDEBUG
profile: CFLAGS += -g -pg -Ofast
profile: LDFLAGS += -pg
profile: DEFS += NDEBUG

debug release profile: $(EXEC)

refraction: $(EXEC)
	./$(EXEC) 640 480 -S p -I povray_files/simple_refract.pov
	./$(EXEC) 600 400 -S p -I povray_files/recurse_simp.pov
	./$(EXEC) 600 400 -S p -I povray_files/modified_recurse_simp.pov
	./$(EXEC) 640 480 -S p -I povray_files/recurse_simp2.pov
	./$(EXEC) 640 480 -S p -I povray_files/modified_recurse_simp2.pov
	./$(EXEC) 640 480 -S p -I povray_files/simple_tri.pov
	./$(EXEC) 640 480 -S p -I povray_files/ugly_part.pov
	./$(EXEC) 640 480 -S p -I povray_files/my_scene.pov
	./$(EXEC) 640 480 -S p -I povray_files/recurses.pov
	./$(EXEC) 640 480 -S p -I povray_files/modified_recurses.pov

prepare:
	mkdir -p $(OBJ_SUB_DIRS)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJ_SUB_DIRS)

remove: clean
	rm -f $(EXEC)

$(EXEC): prepare $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<
