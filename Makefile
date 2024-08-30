# Directories
SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib
BIN_DIR := bin
SFML_INC := $(LIB_DIR)/SFML/include
SFML_LIB := $(LIB_DIR)/SFML/lib
SFML_DLL := $(LIB_DIR)/SFML
SERVER_SRC_DIR := Server/src
SERVER_OBJ_DIR := Server/obj

# Source and object files
BP_SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
BP_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(BP_SOURCES))

# Source and object files for Server
SERVER_SOURCES := $(wildcard $(SERVER_SRC_DIR)/*.cpp)
SERVER_OBJECTS := $(patsubst $(SERVER_SRC_DIR)/%.cpp,$(SERVER_OBJ_DIR)/%.o,$(SERVER_SOURCES))
SERVER_DEPS := $(OBJ_DIR)/Player.o $(OBJ_DIR)/Entity.o



# Targets
TARGET_BP := $(BIN_DIR)/BlockPlanet.exe
TARGET_SERVER := $(BIN_DIR)/Server.exe

# Default target
all: $(TARGET_BP) $(TARGET_SERVER) copy-dlls

bp: $(TARGET_BP) copy-dlls

server: $(TARGET_SERVER) copy-dlls

# Rule to build object files from source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	g++ -I$(SFML_INC) -c $< -o $@


# Rule to build object files for Server from source files
$(SERVER_OBJ_DIR)/%.o: $(SERVER_SRC_DIR)/%.cpp
	@mkdir -p $(SERVER_OBJ_DIR)
	g++ -I$(SFML_INC) -c $< -o $@

# Rule to link the final executable
$(TARGET_BP): $(BP_OBJECTS)
	@mkdir -p $(BIN_DIR)
	g++ -o $@ $^ -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

# Rule to link the final Server executable
$(TARGET_SERVER): $(SERVER_OBJECTS) $(SERVER_DEPS)
	@mkdir -p $(BIN_DIR)
	g++ -o $@ $^ -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

# Rule to copy DLL files to the bin directory
copy-dlls:
	@mkdir -p $(BIN_DIR)
	cp $(SFML_DLL)/*.dll $(BIN_DIR)

# Clean target to remove generated files
.PHONY: clean clean_bp
clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/* $(SERVER_OBJ_DIR)/*

clean_bp:
	rm -rf $(OBJ_DIR)/* $(TARGET_BP)

clean-server:
	rm -rf $(SERVER_OBJ_DIR)/* $(TARGET_SERVER)
