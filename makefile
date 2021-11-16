CC				:= g++
#add flags if needed
CFLAGS			:= -g

#Where to put the object files
OBJ_DIR			:= ./bin

#SFML libs flags
SFML_LDFLAGS 	:= -lsfml-graphics -lsfml-window -lsfml-system
#SDL Include Flags + Lib Flags
SDL_CFLAGS 		:= $(shell sdl2-config --cflags)
SDL_LDFLAGS 	:= $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf

#final Include Flags (Add SFML or SDL here if needs be)
CXXFLAGS 		:= -I. -I./include $(SDL_CFLAGS) $(SDL_LDFLAGS)

#searches for all cpps inside the src file (WONT GO INTO FOLDERS)
SRC_FILES		:= $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)

#modifies extension on all cpps to object files
OBJ_FILES		:= $(patsubst %.cpp, %.o, $(SRC_FILES))

#changes from ./src to whatever the OBJ_DIR is 
#*Should be commented out if there's nested cpp folders (nesting cpp folders means obj file gets placed \
#with the cpp for at the minute - hopefully will be tuned soon*
OBJ_TARGET		:= $(foreach obj,$(OBJ_FILES), $(lastword $(subst /, $(OBJ_DIR)/,$(obj))))

#add more /* if more folders are nested
NESTED_CPP		:= $(OBJ_FILES)
OBJ_FOLDER		:= $(OBJ_DIR)/*.o

#for every object file it gets the cpp and creates an object file inside the DIR
#will be OBJ_DIR if obj_target is used, else will be inside the cpp folder if OBJ_FILES is used
$(OBJ_DIR)/%.o : ./src/%.cpp
	mkdir -p ./bin
	$(CC) $(CFLAGS) -c $< $(CXXFLAGS) -o $@

#Change OBJ_TARGET to OBJ_FILES if there is nested cpp folders (CURRENTLY THE WAY TO WORK WITH NESTED CPP's)
#whatever follows build: needs to be placed after $@ too
build: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES) $(CXXFLAGS)
	./$@
	
.PHONY: clean

.PHONY: original

.PHONY: remove	

#change the variable depending on if you used a nested folder or not
remove:
	rm -f $(NESTED_CPP)

original:
	$(CC) $(CFLAGS) -o $@ $(SRC_FILES) $(CXXFLAGS)

clean:
	rm -f $(NESTED_CPP)
	make