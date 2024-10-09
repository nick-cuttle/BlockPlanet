cmake_minimum_required(VERSION 3.10)
project(BlockPlanet)

#set cmake standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(BIN_DIR ${CMAKE_BINARY_DIR}/bin)
set(RESOUCES_DIR ${CMAKE_SOURCE_DIR}/resources)
set(SERVER_SRC_DIR ${CMAKE_SOURCE_DIR}/Server/src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# SFML
set(SFML_DIR ${LIB_DIR}/SFML)
set(SFML_INCLUDE_DIR ${SFML_DIR}/include)
set(SFML_LIBRARY_DIR ${SFML_DIR}/lib)
include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIBRARY_DIR})

# Find all source files
file(GLOB_RECURSE BP_SOURCES ${SRC_DIR}/*.cpp)
file(GLOB SERVER_SOURCES ${SERVER_SRC_DIR}/*.cpp)

#find dlls:
file(GLOB_RECURSE SFML_DLLS ${SFML_DIR}/*.dll)

# Create a list of shared source files
set(SHARED_SOURCES
    ${SRC_DIR}/Player.cpp
    ${SRC_DIR}/Entity.cpp
    # Add any other shared source files here
)

# Remove shared sources from BP_SOURCES
#list(REMOVE_ITEM BP_SOURCES ${SHARED_SOURCES})
list(APPEND SERVER_SOURCES ${SHARED_SOURCES})

# set(FNL_DIR ${LIB_DIR}/FastNoiseLite/Cpp)  # Correct path to include directory
# include_directories(${FNL_DIR})  # Include the FastNoiseLite include directory
add_library(FNL_Lib INTERFACE)
target_include_directories(FNL_Lib INTERFACE ${LIB_DIR}/FastNoiseLite/Cpp/include)


# Create executable targets
add_executable(BlockPlanet ${BP_SOURCES})
add_executable(Server ${SERVER_SOURCES})

#link libraries
target_link_libraries(BlockPlanet sfml-graphics sfml-window sfml-system sfml-network FNL_Lib)
target_link_libraries(Server sfml-graphics sfml-window sfml-system sfml-network FNL_Lib)

# Function to copy DLLs
function(copy_dlls target)
    if(WIN32)
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SFML_DLLS}
                $<TARGET_FILE_DIR:${target}>
            COMMENT "Copying SFML DLLs for ${target}"
        )
    endif()
endfunction()

copy_dlls(BlockPlanet)

