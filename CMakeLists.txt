cmake_minimum_required(VERSION 3.24)

project(MidiToDesmos CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(MtD
    src/main.cpp
    src/MidiFile.cpp
    src/Note.cpp
    src/NoteStream.cpp
)