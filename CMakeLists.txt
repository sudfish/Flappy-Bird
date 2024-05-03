cmake_minimum_required( VERSION 3.10 )
project(Flappy-Bird)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
find_package(SFML COMPONENTS window audio graphics network)

file(GLOB SOURCE_FILES "src/*.cpp")
file(GLOB HEADER_FILES "include/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-audio sfml-network)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
