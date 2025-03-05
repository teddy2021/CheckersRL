cmake_minimum_required(VERSION 3.26)
set (CMAKE_CXX_STANDARD 23)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
set( CMAKE_C_COMPILER "/usr/bin/clang" )
set( CMAKE_CXX_COMPILER "/usr/bin/clang++" )
set( CMAKE_BUILD_TYPE RelWithDebInfo )
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
project(Checkers)

add_executable(tests
	piece.cpp piece.hpp
	tree.hpp 
	board.cpp board.hpp
	player.cpp player.hpp
	ai.cpp ai.hpp
	game.cpp game.hpp
	tests.cpp
)

add_executable(main
	piece.cpp piece.hpp
	tree.hpp 
	board.cpp board.hpp
	player.cpp player.hpp
	ai.cpp ai.hpp
	game.cpp game.hpp
	main.cpp)

find_package(Catch2 3 REQUIRED)
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(main ${CURSES_LIBRARY})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain ${CURSES_LIBRARY})
