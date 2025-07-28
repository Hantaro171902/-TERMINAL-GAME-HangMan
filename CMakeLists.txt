cmake_minimum_required(VERSION 3.10)

# Project name and version
project(TerminalHangman VERSION 1.0)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set source and header files
set(SOURCES
    src/main.cpp
    src/cursor_input.cpp
    src/game_logic.cpp
    src/menu.cpp
    src/words.cpp
    src/ultils.cpp
)

set(HEADERS
    src/headers/cursor_input.hpp
    src/headers/game_logic.hpp
    src/headers/menu.hpp
    src/headers/words.hpp
    src/headers/ultils.hpp
)

# Executable target
add_executable(Hangman ${SOURCES} ${HEADERS})

# Optional: copy asset folder into build dir
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
