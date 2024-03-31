find_package(SDL2 REQUIRED)

add_executable(example main.cpp)

target_include_directories(example PRIVATE ${SDL2_INCLUDE_DIRS})

target_link_libraries(example ${SDL2_LIBRARIES})