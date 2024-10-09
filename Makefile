# Directories
SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib
BIN_DIR := bin
SFML_INC := $(LIB_DIR)/SFML/include
SFML_LIB := $(LIB_DIR)/SFML/lib
SFML_DLL := $(LIB_DIR)/SFML

FN_INC := $(LIB_DIR)/FastNoise2/include
FN_LIB := $(LIB_DIR)/FastNoise2/build/src/Release/

SERVER_SRC_DIR := Server/src
SERVER_OBJ_DIR := Server/obj

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# Function to recursively list directories only
define recursive_dirs
  $(wildcard $(1)*/) $(foreach d,$(wildcard $(1)*/),$(call recursive_dirs,$d))
endef

# Get unique directories in SRC_DIR (preserve subdirectory structure)
BP_SUBDIRS := $(call recursive_dirs,$(SRC_DIR))

# Remove the base path (SRC_DIR/) from the directories
BP_SUBDIRS := $(patsubst $(SRC_DIR)/%,%,$(BP_SUBDIRS))

# Remove trailing slashes from each directory path
BP_SUBDIRS := $(patsubst %/,%,$(BP_SUBDIRS))

# Ensure the list is unique
BP_SUBDIRS := $(sort $(BP_SUBDIRS))


# Source and object files
BP_SOURCES := $(call rwildcard,${SRC_DIR},*.cpp)
#BP_SUBDIRS := blocks ui
#BP_SUBDIRS := $(shell ls -d $(SRC_DIR)/*/ | sed 's|$(SRC_DIR)/||;s|/||')

BP_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(BP_SOURCES))

# Source and object files for Server
SERVER_SOURCES := $(wildcard $(SERVER_SRC_DIR)/*.cpp)
SERVER_OBJECTS := $(patsubst $(SERVER_SRC_DIR)/%.cpp,$(SERVER_OBJ_DIR)/%.o,$(SERVER_SOURCES))
SERVER_DEPS := $(OBJ_DIR)/Player.o $(OBJ_DIR)/Entity.o

# Targets
TARGET_BP := $(BIN_DIR)/BlockPlanet.exe
TARGET_SERVER := $(BIN_DIR)/Server.exe

prep-obj-subdirs:
	@for dir in $(BP_SUBDIRS); do \
		mkdir -p $(OBJ_DIR)/$${dir}; \
	done

print:
	@echo "BP_OBJS: $(BP_OBJECTS)"
	@echo "BP_SOURCES: $(BP_SOURCES)"
	@echo "SUB_DIRS:  $(BP_SUBDIRS)"
# Default target
all:  copy-dlls prep-obj-subdirs $(TARGET_BP) $(TARGET_SERVER)

bp: prep-obj-subdirs $(TARGET_BP) copy-dlls

server: $(TARGET_SERVER) copy-dlls

# Rule to build object files from source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	g++ -I$(SFML_INC) -I$(FN_INC) -c $< -o $@


# Rule to build object files for Server from source files
$(SERVER_OBJ_DIR)/%.o: $(SERVER_SRC_DIR)/%.cpp
	@mkdir -p $(SERVER_OBJ_DIR)
	g++ -I$(SFML_INC) -I$(FN_INC) -c $< -o $@

# Rule to link the final executable
$(TARGET_BP): $(BP_OBJECTS)
	@mkdir -p $(BIN_DIR)
	g++ -o $@ $^ -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -L$(FN_LIB) -lFastNoise
	@if [ $$? -eq 0 ]; then \
		printf "\033[0;32mBlock Planet Build Success!\033[0m\n"; \
	else \
		printf "\033[0;31mBlock Planet Build Failed!\033[0m\n"; \
	fi

# Rule to link the final Server executable
$(TARGET_SERVER): $(SERVER_OBJECTS) $(SERVER_DEPS)
	@mkdir -p $(BIN_DIR)
	g++ -o $@ $^ -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -L$(FN_LIB) -lFastNoise
	@if [ $$? -eq 0 ]; then \
		printf "\033[0;32mServer Build Success!\033[0m\n"; \
	else \
		printf "\033[0;31mServer Build Failed!\033[0m\n"; \
	fi

# Rule to copy DLL files to the bin directory
copy-dlls:
	@mkdir -p $(BIN_DIR)
	cp $(SFML_DLL)/*.dll $(BIN_DIR)
	cp $(FN_LIB)/*.dll $(BIN_DIR)  # Copy FastNoise DLL

# Clean target to remove generated files
.PHONY: clean clean_bp
clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/* $(SERVER_OBJ_DIR)/*

clean_bp:
	rm -rf $(OBJ_DIR)/* $(TARGET_BP)

clean-server:
	rm -rf $(SERVER_OBJ_DIR)/* $(TARGET_SERVER)
