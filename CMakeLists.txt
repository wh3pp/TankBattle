cmake_minimum_required(VERSION 3.10)

project(TankBattle)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5 REQUIRED graphics window system)

include_directories(include)

file(GLOB_RECURSE TANK_GAME_SOURCES "src/*.cpp")
add_executable(TankBattle ${TANK_GAME_SOURCES})

target_link_libraries(TankBattle 
  sfml-graphics
  sfml-window
  sfml-system
)

add_custom_command(TARGET TankBattle POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:TankBattle>/resources
)
