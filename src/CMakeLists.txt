cmake_minimum_required(VERSION 3.10)
project(Sim2D)

include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp Simulation2D.cpp Fly2D.cpp Arena2D.cpp Wall.cpp Entrance.cpp Rectangle.cpp)
set(DRAW_2D_FILES DrawArena2D.cpp Simulation2D.cpp Fly2D.cpp Arena2D.cpp Wall.cpp  Entrance.cpp Utility.cpp Rectangle.cpp)
set(TEST_DRAW_FILES TestDraw.cpp Simulation2D.cpp Fly2D.cpp Arena2D.cpp Wall.cpp Entrance.cpp Utility.cpp Rectangle.cpp)
set(PROJECT2 "DrawArena2d")
set(TEST_DRAW "TestDraw")

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_executable(DrawArena2d ${DRAW_2D_FILES})
add_executable(${TEST_DRAW} ${TEST_DRAW_FILES})
#target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(DrawArena2d PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(${TEST_DRAW} PUBLIC ${SDL2_INCLUDE_DIRS})

#target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(DrawArena2d ${SDL2_LIBRARIES})
target_link_libraries(${TEST_DRAW} ${SDL2_LIBRARIES})

