cmake_minimum_required(VERSION 3.10)

project(Chess VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Chess/Core/src)
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Chess/Core/include)

set(SOURCES 
    ${SRC_DIR}/Bitboard.cpp
    ${SRC_DIR}/Board.cpp
    ${SRC_DIR}/Game.cpp
    ${SRC_DIR}/LoadGame.cpp
    ${SRC_DIR}/MoveGeneration.cpp
    ${SRC_DIR}/MagicBitboard.cpp
    )

set(HEADERS 
    ${HEADER_DIR}/Bitboard.h
    ${HEADER_DIR}/Board.h
    ${HEADER_DIR}/ChessDefinitons.h
    ${HEADER_DIR}/LoadGame.h
    ${HEADER_DIR}/MoveGeneration.h
    ${HEADER_DIR}/MagicBitboard.h)

add_executable(Chess ${SOURCES} ${HEADERS})

target_include_directories(Chess PUBLIC ${HEADER_DIR})