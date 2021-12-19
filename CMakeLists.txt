cmake_minimum_required(VERSION 3.0.0)
project(pincushion VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 11)

add_subdirectory(CSV)
add_executable(csv2json src/csv2json.cpp)
target_link_libraries(csv2json PUBLIC CSV)

target_include_directories(csv2json PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/CSV"
                          )

install(TARGETS csv2json DESTINATION bin)
